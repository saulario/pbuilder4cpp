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

#include "pbuilder_analyzer.h"

using namespace pbuilder::analyzer;

log4cxx::LoggerPtr MysqlAnalyzer::logger = log4cxx::Logger::getLogger("pbuilder::analyzer::MysqlAnalyzer");

void MysqlAnalyzer::analyze(void) {
    LOG4CXX_TRACE(logger, "analyze -----> begin");

    connection = tntdb::connect(pbuilder->unit.url);

    tntdb::Result tables = connection.prepare("SELECT * FROM TABLES WHERE "
            "     TABLE_SCHEMA = :schema"
            " AND TABLE_NAME LIKE :table").
            setString("schema", pbuilder->unit.name).
            setString("table", pbuilder->table).
            select()
            ;

    for (tntdb::Row row : tables) {
        pbuilder::Table table(row.getString("TABLE_NAME"));

        tntdb::Result columns = connection.prepare("SELECT * FROM COLUMNS WHERE "
                "     TABLE_SCHEMA = :schema "
                " AND TABLE_NAME = :table"
                " ORDER BY ORDINAL_POSITION").
                setString("schema", pbuilder->unit.name).
                setString("table", table.name).
                select()
                ;
        for (tntdb::Row row1 : columns) {
            pbuilder::Column column;
            column.name = row1.getString("COLUMN_NAME");
            table.columns.insert(std::pair<std::string, pbuilder::Column>(column.name, column));
        }

        tntdb::Result pkColumns = connection.prepare("SELECT * FROM KEY_COLUMN_USAGE WHERE "
                "     TABLE_SCHEMA = :schema "
                " AND TABLE_NAME = :table "
                " AND CONSTRAINT_NAME = :name "
                " ORDER BY ORDINAL_POSITION").
                setString("schema", pbuilder->unit.name).
                setString("table", table.name).
                setString("name", "PRIMARY").
                select()
                ;
        for (tntdb::Row row1 : pkColumns) {
            table.pkColumns.push_back(row1.getString("COLUMN_NAME"));
        }

        //        for (tntdb::Row column : columns) {
        //            std::string name = column.getString("COLUMN_NAME");
        //            pbuilder::Column c;
        //            t.columns.insert(
        //                    std::pair<std::string, pbuilder::Column>(name, c));
        //        }

        pbuilder->model.tables.insert(std::pair<std::string, pbuilder::Table>(table.name, table));

    }

    for (std::pair<std::string, pbuilder::Table> p : pbuilder->model.tables) {
        pbuilder::Table table = p.second;
        if (table.name.compare("toc") == 0) {
            std::cerr << table.name << std::endl;
            for (std::pair<std::string, pbuilder::Column> p1 : table.columns) {
                pbuilder::Column column = p1.second;
                std::cerr << column.name << std::endl;
            }
            std::cerr << " ahora la clave" << std::endl;
            for (std::string column : table.pkColumns) {
                std::cerr << column << std::endl;
            }
        }
    }


    connection.close();

    LOG4CXX_TRACE(logger, "analyze <----- end");
}
