/*
 * Persistence Builder (pbuilder)
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

log4cxx::LoggerPtr MysqlAnalyzer::logger = log4cxx::Logger::getLogger("pbuilder::analyzer::MysqlAnalyzer");

void MysqlAnalyzer::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");

    connection = tntdb::connect(pbuilder->unit.url);

    tntdb::Result tables = connection.prepare("SELECT * FROM TABLES WHERE "
            "     TABLE_SCHEMA = :schema"
            " AND TABLE_NAME LIKE :table"
            " ORDER BY TABLE_NAME").
            setString("schema", pbuilder->unit.database).
            setString("table", pbuilder->table).
            select()
            ;

    for (tntdb::Row row : tables) {
        pbuilder::Table table(row.getString("TABLE_NAME"));
        
        tntdb::Result columns = connection.prepare("SELECT * FROM COLUMNS WHERE "
                "     TABLE_SCHEMA = :schema "
                " AND TABLE_NAME = :table"
                " ORDER BY ORDINAL_POSITION").
                setString("schema", pbuilder->unit.database).
                setString("table", table.name).
                select()
                ;
        for (tntdb::Row row1 : columns) {
            pbuilder::Column column;
            column.name = row1.getString("COLUMN_NAME");
            column.position = row1.getUnsigned64("ORDINAL_POSITION");
            column.isNullable = (row1.getString("IS_NULLABLE").compare("YES") == 0);
            column.schemaType = row1.getString("DATA_TYPE");
            if (!supportedType(column)) {
                continue;
            }            
            column.type = getModelType(column.schemaType);
            try {
                column.charMaxLength = row1.getUnsigned64("CHARACTER_MAXIMUM_LENGTH");
            } catch (tntdb::NullValue nv) {
            }
            try {
                column.numericPrecision = row1.getUnsigned64("NUMERIC_PRECISION");
            } catch (tntdb::NullValue nv) {
            }
            try {
                column.numericScale = row1.getUnsigned64("NUMERIC_SCALE");
            } catch (tntdb::NullValue nv) {
            }
            try {
                column.defaultValue = row1.getString("COLUMN_DEFAULT");
            } catch (tntdb::NullValue nv) {
            }
            std::string columnType = row1.getString("COLUMN_TYPE");
            column.isUnsigned = (columnType.find("unsigned") != std::string::npos);            
            column.comment = row1.getString("COLUMN_COMMENT");
            table.columns.push_back(column);
        }

        tntdb::Result pkColumns = connection.prepare(
                "SELECT KCU.ORDINAL_POSITION, COL.* "
                " FROM COLUMNS COL, KEY_COLUMN_USAGE KCU  WHERE "
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
            pbuilder::Column column;
            column.name = row1.getString("COLUMN_NAME");
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

pbuilder::MODEL_TYPE MysqlAnalyzer::getModelType(const std::string & ptype) {

    if (ptype.compare("smallint") == 0) {
        return SMALLINT;
    } else if (ptype.compare("mediumint") == 0) {
        return MEDIUMINT;        
    } else if (ptype.compare("int") == 0) {
        return INTEGER;
    } else if (ptype.compare("bigint") == 0) {
        return BIGINT;
    } else if (ptype.compare("decimal") == 0) {
        return DOUBLE;
    } else if (ptype.compare("char") == 0) {
        return STRING;
    } else if (ptype.compare("varchar") == 0) {
        return STRING;
    } else if (ptype.compare("text") == 0) {
        return STRING;
    } else if (ptype.compare("longtext") == 0) {
        return STRING;
    } else if (ptype.compare("date") == 0) {
        return DATE;
    } else if (ptype.compare("time") == 0) {
        return TIME;
    } else if (ptype.compare("datetime") == 0) {
        return DATETIME;
    } else if (ptype.compare("timestamp") == 0) {
        return TIMESTAMP;
    } else if (ptype.compare("blob") == 0) {
        return BLOB;
    } else if (ptype.compare("longblob") == 0) {
        return BLOB;
    } else if (ptype.compare("point") == 0) {
        return POINT;
    } else if (ptype.compare("polygon") == 0) {
        return POLYGON;
    }

    return STRING;
}

bool MysqlAnalyzer::supportedType(const pbuilder::Column & column_) {
    if (pbuilder->unit.geometry) {
        return true;
    }
    bool supported = true;
    if ("point" == column_.schemaType) {
        supported = false;
    } else if ("polygon" == column_.schemaType) {
        supported = false;
    }
    return supported;
}