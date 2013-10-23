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
        case STRING:
        case CLOB:            
            value = "std::string";
            break;
        case DATE:            
            value = "tntdb::Date";
            break;
        case TIME:            
            value = "tntdb::Time";
            break;
        case DATETIME:            
        case TIMESTAMP:                        
            value = "tntdb::Datetime";
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
    edef.notify();
    
    LOG4CXX_TRACE(logger, "doRender <----- end");    
}