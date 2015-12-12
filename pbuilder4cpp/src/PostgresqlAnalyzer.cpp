/*
 * Persistence Builder (pbuilder4cpp)
 * Copyright (C) 2013..  Saul Correas Subias 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include <tntdb/connect.h>
#include <tntdb/result.h>
#include <tntdb/error.h>

#include "pbuilder_analyzer.h"

using namespace pbuilder::analyzer;

log4cxx::LoggerPtr PostgresqlAnalyzer::logger = log4cxx::Logger::getLogger("pbuilder::analyzer::PostgresqlAnalyzer");

void PostgresqlAnalyzer::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");

    connection = tntdb::connect(pbuilder->unit.url);

    //    tntdb::Result tables = connection.prepare("SELECT * FROM "
    //            "       INFORMATION_SCHEMA.TABLES"
    //            "   WHERE "
    //            "     TABLE_SCHEMA = :schema"
    //            " AND TABLE_NAME LIKE :table"
    //            " ORDER BY TABLE_NAME").
    //            setString("schema", "public").
    //            setString("table", pbuilder->table).
    //            select()
    //            ;

    tntdb::Result tables = connection.prepare(
            "SELECT c.oid, c.* "
            "   FROM pg_class as c "
            "       JOIN pg_namespace n ON n.oid = c.relnamespace AND n.nspname = :nspname "
            "   WHERE "
            "       c.relkind = :relkind"
            "   ORDER BY relname"
            )
            .setString("nspname", pbuilder->unit.database)
            .setString("relkind", "r").
            select();

    for (tntdb::Row row : tables) {
        pbuilder::Table table(row.getString("relname"));

        //        tntdb::Result columns = connection.prepare("SELECT * FROM "
        //                "       INFORMATION_SCHEMA.COLUMNS "
        //                "   WHERE "
        //                "     TABLE_SCHEMA = :schema "
        //                " AND TABLE_NAME = :table"
        //                " ORDER BY ORDINAL_POSITION").
        //                setString("schema", "public").
        //                setString("table", table.name).
        //                select()
        //                ;
        unsigned long oid = row.getUnsignedLong("oid");

        tntdb::Result columns = connection.prepare(
                "SELECT att.attname, att.attnum, att.attnotnull, typ.oid, typ.typname, des.description, ad.adsrc "
                "   FROM pg_attribute att "
                "       JOIN pg_type typ ON typ.oid = att.atttypid "
                "       LEFT JOIN pg_description des ON des.objoid = att.attrelid AND des.objsubid = att.attnum "
                "       LEFT JOIN pg_attrdef ad ON ad.adrelid = att.attrelid AND ad.adnum = att.attnum "
                "   WHERE "
                "           att.attrelid = :attrelid "
                "       AND att.attnum > :attnum "
                "   ORDER BY attnum"
                )
                .setUnsignedLong("attrelid", oid)
                .setShort(0)
                .select();
                ;
        for (tntdb::Row row1 : columns) {
            pbuilder::Column column(row1.getString("attname"));
            column.position = row1.getShort("attnum");
            column.isNullable =  !row.getBool("attnotnull");
            column.schemaType = row1.getString("typename");
            if (!supportedType(column)) {
                continue;
            }
            column.type = getModelType(column.schemaType);
//            try {
//                column.charMaxLength = row1.getUnsigned64("CHARACTER_MAXIMUM_LENGTH");
//            } catch (tntdb::NullValue nv) {
//            }
//            try {
//                column.numericPrecision = row1.getUnsigned64("NUMERIC_PRECISION");
//            } catch (tntdb::NullValue nv) {
//            }
//            try {
//                column.numericScale = row1.getUnsigned64("NUMERIC_SCALE");
//            } catch (tntdb::NullValue nv) {
//            }
//            try {
//                column.defaultValue = row1.getString("COLUMN_DEFAULT");
//            } catch (tntdb::NullValue nv) {
//            }
            column.isUnsigned = false;
            column.comment = row1.getString("description");
            table.columns.push_back(column);
        }

        tntdb::Result pkColumns = connection.prepare(
                "SELECT KCU.ORDINAL_POSITION, COL.* "
                " FROM "
                "     INFORMATION_SCHEMA.COLUMNS COL"
                "   , INFORMATION_SCHEMA.KEY_COLUMN_USAGE KCU "
                " WHERE "
                "     COL.TABLE_SCHEMA = :schema "
                " AND COL.TABLE_NAME = :table "
                " AND KCU.CONSTRAINT_NAME = :name "
                " AND KCU.TABLE_SCHEMA = COL.TABLE_SCHEMA "
                " AND KCU.TABLE_NAME = COL.TABLE_NAME "
                " AND KCU.COLUMN_NAME = COL.COLUMN_NAME "
                " ORDER BY KCU.ORDINAL_POSITION").
                setString("schema", pbuilder->unit.name).
                setString("table", table.name).
                setString("name", "PRIMARY").
                select()
                ;
        for (tntdb::Row row1 : pkColumns) {
            pbuilder::Column column(row1.getString("COLUMN_NAME"));
            column.position = row1.getUnsigned64("ORDINAL_POSITION");
            column.isNullable = (row1.getString("IS_NULLABLE").compare("YES") == 0);
            column.schemaType = row1.getString("DATA_TYPE");
            column.type = getModelType(column.schemaType);
            try {
                column.charMaxLength = row1.getUnsigned64("CHARACTER_MAXIMUM_LENGTH");
            } catch (tntdb::NullValue) {
            }
            try {
                column.numericPrecision = row1.getUnsigned64("NUMERIC_PRECISION");
            } catch (tntdb::NullValue) {
            }
            try {
                column.numericScale = row1.getUnsigned64("NUMERIC_SCALE");
            } catch (tntdb::NullValue) {
            }
            try {
                column.defaultValue = row1.getString("COLUMN_DEFAULT");
            } catch (tntdb::NullValue) {
            }
            std::string columnType = row1.getString("COLUMN_TYPE");
            column.isUnsigned = (columnType.find("unsigned") != std::string::npos);
            column.comment = row1.getString("COLUMN_COMMENT");
            table.pkColumns.push_back(column);
        }

        pbuilder->model.tables.insert(std::pair<std::string, pbuilder::Table>(table.name, table));
    }

    connection.close();

    LOG4CXX_TRACE(logger, "notify <----- end");
}

pbuilder::MODEL_TYPE PostgresqlAnalyzer::getModelType(const std::string & ptype) {

    if (ptype.compare("int2") == 0) {
        return SMALLINT;
    } else if (ptype.compare("int4") == 0) {
        return INTEGER;
    } else if (ptype.compare("int8") == 0) {
        return BIGINT;
    } else if (ptype.compare("numeric") == 0) {
        return DOUBLE;
    } else if (ptype.compare("money") == 0) {
        return DOUBLE;        
    } else if (ptype.compare("float4") == 0) {
        return FLOAT;
    } else if (ptype.compare("float8") == 0) {
        return DOUBLE;        
    } else if (ptype.compare("bpchar") == 0) {
        return STRING;
    } else if (ptype.compare("varchar") == 0) {
        return STRING;
    } else if (ptype.compare("text") == 0) {
        return STRING;
    } else if (ptype.compare("date") == 0) {
        return DATE;
    } else if (ptype.compare("time") == 0) {
        return TIME;
//    } else if (ptype.compare("timetz") == 0) {
//        return TIME;
    } else if (ptype.compare("timestamp") == 0) {
        return DATETIME;
//    } else if (ptype.compare("timestamptz") == 0) {
//        return DATETIME;
    } else if (ptype.compare("bool") == 0) {
        return BOOLEAN;
    } else if (ptype.compare("bytea") == 0) {
        return BLOB;        
    } else if (ptype.compare("point") == 0) {
        return POINT;                
    } else if (ptype.compare("line") == 0) {
        return LINE;                        
    } else if (ptype.compare("box") == 0) {
        return BOX;                                
    } else if (ptype.compare("polygon") == 0) {
        return POLYGON;                                        
    } else if (ptype.compare("circle") == 0) {
        return CIRCLE;                                        
    }

    return STRING;
}

bool PostgresqlAnalyzer::supportedType(const pbuilder::Column & column_) {
    if (pbuilder->unit.geometry) {
        return true;
    }
    
    bool supported = true;
    if ("point" == column_.schemaType) {
        supported = false;
    } else if ("line" == column_.schemaType) {
        supported = false;
    } else if ("box" == column_.schemaType) {
        supported = false;        
    } else if ("polygon" == column_.schemaType) {
        supported = false;        
    } else if ("circle" == column_.schemaType) {
        supported = false;        
    }
    return supported;
}
