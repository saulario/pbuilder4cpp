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
#include <boost/algorithm/string.hpp>
#include "pbuilder.h"
#include "pbuilder_render.h"

using namespace pbuilder::render;

log4cxx::LoggerPtr TNTDBArtifactDefinitionRender::logger =
        log4cxx::Logger::getLogger("pbuilder::render::TNTDBArtifactDefinitionRender");

TNTDBArtifactDefinitionRender::TNTDBArtifactDefinitionRender(TNTDBRender * render_) : render(render_) {
    LOG4CXX_TRACE(logger, "TNTDBArtifactDefinitionRender -----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << "#include <boost/algorithm/string/split.hpp>" << std::endl
            << "#include <boost/algorithm/string/predicate.hpp>" << std::endl
            << "#include <boost/algorithm/string/classification.hpp>" << std::endl
            << "#include <tntdb/error.h>" << std::endl
            << "#include \"" << render->parent->pbuilder->unit.ns << "_dao.h\"" << std::endl
            << "using namespace " << render->parent->pbuilder->unit.ns << "::dao;" << std::endl;
    ;

    static const char * common = R"DELIM(        
void CommonDAO::createQueries(void) {
    insertQuery = "insert into " + table + "(" + columns + ")"
            " values("
            ;
    std::vector<std::string> fields;
    bool first = true;
    boost::algorithm::split(fields, columns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            insertQuery += ",";
        }
        first = false;
        insertQuery += ":" + f;
    }
    insertQuery += ")";
    readQuery = "select " + columns + " from " + table + " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            readQuery += " and ";
        }
        first = false;
        readQuery += f + "=:" + f;
    }
    removeQuery = "delete from " + table + " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            removeQuery += " and ";
        }
        first = false;
        removeQuery += f + "=:" + f;
    }
    updateQuery = "update " + table + " set ";
    first = true;
    boost::algorithm::split(fields, columns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            updateQuery += ",";
        }
        first = false;
        updateQuery += f + "=:" + f;
    }
    updateQuery += " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            updateQuery += " and ";
        }
        first = false;
        updateQuery += f + "=:" + f + "PK";
    }
}
std::string CommonDAO::getInsertQuery(void) {
    return insertQuery;
}
std::string CommonDAO::getReadQuery(void) {
    return readQuery;
}
std::string CommonDAO::getRemoveQuery(void) {
    return removeQuery;
}
std::string CommonDAO::getUpdateQuery(void) {
    return updateQuery;
}
std::string CommonDAO::getColumns(void) {
    return columns;
}
std::string CommonDAO::getTable(void) {
    return table;
}
)DELIM";
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << common
            << std::endl;
    LOG4CXX_TRACE(logger, "TNTDBArtifactDefinitionRender <----- end");
}

TNTDBArtifactDefinitionRender::~TNTDBArtifactDefinitionRender() {
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDefinitionRender -----> begin");
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDefinitionRender <----- end");
}

void TNTDBArtifactDefinitionRender::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder::Table> p : render->parent->pbuilder->model.tables) {
        staticDefinition(p.second);
        constructor(p.second);
        destructor(p.second);
        getInstance(p.second);
    }
    LOG4CXX_TRACE(logger, "notify <----- end");
}

void TNTDBArtifactDefinitionRender::constructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "constructor -----> begin");
    LOG4CXX_TRACE(logger, "constructor <----- end");
}

void TNTDBArtifactDefinitionRender::destructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "destructor -----> begin");
    static const char * cdn = R"DELIM(        
OBJECT::~OBJECT() {
    if (dao != NULL) {
        delete dao;
    }
}
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "OBJECT", pbuilder::render::Render::toUpper(table_.name) + "DAO");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "destructor <----- end");
}

void TNTDBArtifactDefinitionRender::getInstance(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "getInstance -----> begin");
    static const char * cdn = R"DELIM(        
OBJECT * OBJECT::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new OBJECT();
        dao->table = "TABLE";
        dao->keyColumns = "KCOLS";
        dao->columns = "COLS";
        dao->createQueries();
    }
    return dao;
}
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "OBJECT", pbuilder::render::Render::toUpper(table_.name) + "DAO");
    boost::replace_all(str, "TABLE", table_.name);
    std::string cols = "";
    bool first = true;
    for (pbuilder::Column c : table_.pkColumns) {
        if (!first) {
            cols += ",";
        }
        first = false;
        cols += c.name;
    }
    boost::replace_all(str, "KCOLS", cols);
    cols = "";
    first = true;
    int count = 0;
    for (pbuilder::Column c : table_.columns) {
        count++;
        if (!first) {
            if (!(count % 5)) {
                cols += "\"";
                cols += '\n';
                cols += "\"";
            }
            cols += ",";
        }
        first = false;
        cols += c.name;
    }
    boost::replace_all(str, "COLS", cols);
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "getInstance <----- end");
}

void TNTDBArtifactDefinitionRender::staticDefinition(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "staticDefinition -----> begin");
    static const char * cdn = R"DELIM(        
OBJECT * OBJECT::dao = NULL;
boost::mutex OBJECT::mtx;
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "OBJECT", pbuilder::render::Render::toUpper(table_.name) + "DAO");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "staticDefinition <----- end");
}