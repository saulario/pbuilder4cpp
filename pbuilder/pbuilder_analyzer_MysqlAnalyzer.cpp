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

    connection = tntdb::connect(pbuilder->unit->url);

    tntdb::Result tables = connection.prepare("SELECT * FROM TABLES WHERE "
            "     TABLE_SCHEMA = :schema"
            " AND TABLE_NAME LIKE :table").
            setString("schema", pbuilder->unit->name).
            setString("table", pbuilder->table).
            select()
            ;

    for (tntdb::Row table : tables) {
        pbuilder::Table * t = new pbuilder::Table(table.getString("TABLE_NAME"));
        pbuilder->model->tables->insert(
                std::pair<std::string, pbuilder::Table *>(t->name, t));

        std::cerr << t->name << std::endl;

        tntdb::Result columns = connection.prepare("SELECT * FROM COLUMNS WHERE "
                "     TABLE_SCHEMA = :schema "
                " AND TABLE_NAME = :table"
                " ORDER BY ORDINAL_POSITION").
                setString("schema", pbuilder->unit->name).
                setString("table", t->name).
                select()
                ;
        for (tntdb::Row column : columns) {
            pbuilder::Column * c = new pbuilder::Column();
            c->name = column.getString("COLUMN_NAME");
            t->columns->insert(
                    std::pair<std::string, pbuilder::Column*>(c->name, c));
        }

        tntdb::Result pkColumns = connection.prepare("SELECT * FROM KEY_COLUMN_USAGE WHERE "
                "     TABLE_SCHEMA = :schema "
                " AND TABLE_NAME = :table "
                " AND CONSTRAINT_NAME = :name "
                " ORDER BY ORDINAL_POSITION").
                setString("schema", pbuilder->unit->name).
                setString("table", t->name).
                setString("name", "PRIMARY").
                select()
                ;
        for (tntdb::Row columns : pkColumns) {
            
        }

        //        for (tntdb::Row column : columns) {
        //            std::string name = column.getString("COLUMN_NAME");
        //            pbuilder::Column c;
        //            t.columns.insert(
        //                    std::pair<std::string, pbuilder::Column>(name, c));
        //        }


    }

    pbuilder::Table * toc = pbuilder->model->tables->find("toc")->second;
    std::map<std::string, pbuilder::Column *>::iterator it;
    for (it = toc->columns->begin(); it != toc->columns->end(); ++it) {
        Column * c = (*it).second;
        std::cerr << c->name << std::endl;
    }




    connection.close();

    LOG4CXX_TRACE(logger, "analyze <----- end");
}
