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
#include <iomanip>

#include "pbuilder.h"
#include "pbuilder_render.h"

using namespace pbuilder::render;

log4cxx::LoggerPtr TNTDBRender::logger = log4cxx::Logger::getLogger("pbuilder::render::TNTDBRender");

std::string TNTDBRender::asText(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "asText -----> begin");
    std::string value = "";
    switch (column_.type) {
        case SMALLINT:
            value = "short";
            break;
        case INTEGER:
            value = "int";
            break;
        case BIGINT:
            value = "long";
            break;
        case FLOAT:
            value = "float";
            break;
        case DOUBLE:
            value = "double";
            break;
        default:
            value = "std::string";
    }
    LOG4CXX_TRACE(logger, "asText <----- end");
    return value;
}

void TNTDBRender::notify(void) {
    LOG4CXX_TRACE(logger, "doRender -----> begin");    

    TNTDBArtifactDeclarationRender adec(this);
    TNTDBArtifactDefinitionRender adef(this);
    TNTDBEntityDeclarationRender edec(this);
    TNTDBEntityDefinitionRender edef(this);
    
    edec.notify();
    
    LOG4CXX_TRACE(logger, "doRender <----- end");    
}

//void TNTDBRender::renderEntityHeader(std::ofstream& file) {
//    LOG4CXX_TRACE(logger, "renderEntityHeader -----> begin");
//    file
//            << "namespace " << pbuilder->unit.ns << " {" << std::endl
//            << std::string(2, ' ') << "namespace entity {" << std::endl;
//    for (std::pair<std::string, pbuilder::Table> p : pbuilder->model.tables) {
//        renderEntityHeaderTable(file, p.second);
//    }
//    file
//            << std::string(2, ' ') << "}" << std::endl
//            << "}" << std::endl;
//    LOG4CXX_TRACE(logger, "renderEntityHeader <----- end");
//}

//void TNTDBRender::renderEntityHeaderTable(std::ofstream& file, pbuilder::Table & table) {
//    file
//            << std::string(4, ' ') << "struct " << table.name << " {" << std::endl
//            << std::string(4, ' ') << "public:" << std::endl;
//    for (pbuilder::Column column : table.columns) {
//        file
//                << std::string(6, ' ') << column.name << " ;" << std::endl
//                ;
//    }
//    file
//            << std::string(4, ' ') << "private:" << std::endl;
//    file
//            << std::string(4, ' ') << "}" << std::endl;
//}

//void TNTDBRender::renderEntityCode(std::ofstream& file) {
//    LOG4CXX_TRACE(logger, "renderEntityCode -----> begin");
//
//    LOG4CXX_TRACE(logger, "renderEntityCode <----- end");
//}

//void TNTDBRender::renderDAOHeader(std::ofstream& file) {
//    LOG4CXX_TRACE(logger, "renderDAOHeader -----> begin");
//
//    LOG4CXX_TRACE(logger, "renderDAOHeader <----- end");
//}

//void TNTDBRender::renderDAOCode(std::ofstream& file) {
//    LOG4CXX_TRACE(logger, "renderDAOCode -----> begin");
//
//    LOG4CXX_TRACE(logger, "renderDAOCode <----- end");
//}
