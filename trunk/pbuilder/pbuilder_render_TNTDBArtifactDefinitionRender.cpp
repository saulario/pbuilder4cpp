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
            << "using namespace " << render->parent->pbuilder->unit.ns << "::dao;" << std::endl;;
    
    const char * common = R"DELIM(        
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