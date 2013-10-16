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

void TNTDBRender::renderEntityHeader(std::ofstream& file) {
    LOG4CXX_TRACE(logger, "renderEntityHeader -----> begin");
    
    file 
            << "namespace " << pbuilder->unit.ns << " {" << std::endl
            << std::string(2, ' ') << "namespace entity {" << std::endl;
    
    for (std::pair<std::string, pbuilder::Table> p : pbuilder->model.tables) {
        renderEntityHeaderTable(file, p.second);
    }
    
    file
//            << std::string(2, ' ') << "}" << std::endl
            << "}" << std::endl;

    LOG4CXX_TRACE(logger, "renderEntityHeader <----- end");
}

void TNTDBRender::renderEntityHeaderTable(std::ofstream& file, pbuilder::Table & table) {

    file 
            << std::string(4, ' ') << "struct " << table.name  << " {" << std::endl;
    

    file 
            << std::string(4, ' ') << " }" << std::endl;
    
 }

void TNTDBRender::renderEntityCode(std::ofstream& file) {
    LOG4CXX_TRACE(logger, "renderEntityCode -----> begin");

    LOG4CXX_TRACE(logger, "renderEntityCode <----- end");
}

void TNTDBRender::renderDAOHeader(std::ofstream& file) {
    LOG4CXX_TRACE(logger, "renderDAOHeader -----> begin");

    LOG4CXX_TRACE(logger, "renderDAOHeader <----- end");
}

void TNTDBRender::renderDAOCode(std::ofstream& file) {
    LOG4CXX_TRACE(logger, "renderDAOCode -----> begin");

    LOG4CXX_TRACE(logger, "renderDAOCode <----- end");
}
