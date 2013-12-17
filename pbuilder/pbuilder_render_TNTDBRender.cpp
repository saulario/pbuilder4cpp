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
        case MEDIUMINT:
            value = "int";
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
        case BLOB:            
            value = "tntdb::Blob";
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

std::string TNTDBRender::defaultValue(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "defaultValue -----> begin");
    std::string value = "";
    switch (column_.type) {
        case SMALLINT:
            value = "0";
            break;
        case MEDIUMINT:
            value = "0";
            break;            
        case INTEGER:
            value = "0";
            break;
        case BIGINT:
            value = "0L";
            break;
        case FLOAT:
            value = "0.0";
            break;
        case DOUBLE:
            value = "0.0";
            break;
        case STRING:
        case CLOB:            
            value = "\"\"";
            break;
        case BLOB:            
            value = "tntdb::Blob()";
            break;    
        case DATE:            
            value = "tntdb::Date()";
            break;
        case TIME:            
            value = "tntdb::Time()";
            break;
        case DATETIME:            
        case TIMESTAMP:                        
            value = "tntdb::Datetime()";
            break;
        default:
            value = "\"\"";
    }
    LOG4CXX_TRACE(logger, "defaultValue <----- end");
    return value;
}

std::string TNTDBRender::isUnsigned(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "isUnsigned -----> begin");
    std::string value = "";
    if (!column_.isUnsigned) {
        return value;
    }
    switch (column_.type) {
        case SMALLINT:
        case MEDIUMINT:            
        case INTEGER:            
        case BIGINT:            
            value = "unsigned ";
            break;
        default:
            value = "";
    }
    LOG4CXX_TRACE(logger, "isUnsigned <----- end");
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