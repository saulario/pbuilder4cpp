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
#include "pbuilder.h"
#include "pbuilder_render.h"

using namespace pbuilder::render;

log4cxx::LoggerPtr TNTDBEntityDeclarationRender::logger =
        log4cxx::Logger::getLogger("pbuilder::render::TNTDBEntityDeclarationRender");

TNTDBEntityDeclarationRender::TNTDBEntityDeclarationRender(TNTDBRender * render_) : render(render_) {
    LOG4CXX_TRACE(logger, "TNTDBEntityDeclarationRender -----> begin");
    render->parent->files[0]
            << "namespace " << render->parent->pbuilder->unit.ns << " {" << std::endl
            << std::string(2, ' ') << "namespace entity {" << std::endl;
    LOG4CXX_TRACE(logger, "TNTDBEntityDeclarationRender <----- end");
}

TNTDBEntityDeclarationRender::~TNTDBEntityDeclarationRender() {
    LOG4CXX_TRACE(logger, "~TNTDBEntityDeclarationRender -----> begin");
    render->parent->files[0]
            << std::string(2, ' ') << "}" << std::endl
            << "}" << std::endl;
    LOG4CXX_TRACE(logger, "~TNTDBEntityDeclarationRender <----- end");
}

void TNTDBEntityDeclarationRender::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder::Table> p : render->parent->pbuilder->model.tables) {
        table(p.second);
    }    
    LOG4CXX_TRACE(logger, "notify <----- end");
}

void TNTDBEntityDeclarationRender::table(const pbuilder::Table & table) {
    LOG4CXX_TRACE(logger, "table -----> begin");
    render->parent->files[0]
            << std::string(4, ' ') << "struct " << table.name << " {" << std::endl;
    publicBlock(table);
    privateBlock(table);
    render->parent->files[0]
            << std::string(4, ' ') << "}" << std::endl;    
    LOG4CXX_TRACE(logger, "table <----- end");
}

void TNTDBEntityDeclarationRender::privateBlock(const pbuilder::Table & table) {
    LOG4CXX_TRACE(logger, "privateBlock -----> begin");
    render->parent->files[0]
            << std::string(4, ' ') << "private:" << std::endl;
    for (pbuilder::Column column : table.columns) {
        privateMember(column);
    }
    LOG4CXX_TRACE(logger, "privateBlock <----- end");
}

void TNTDBEntityDeclarationRender::privateMember(const pbuilder::Column & column) {
    LOG4CXX_TRACE(logger, "privateMembers -----> begin");
    if (!column.nullable) {
        return;
    }
    render->parent->files[0]
            << std::string(6, ' ') << render->asText(column) << " * " << column.name << ";" << std::endl;
    LOG4CXX_TRACE(logger, "privateMembers <----- end");
}

void TNTDBEntityDeclarationRender::publicBlock(const pbuilder::Table & table) {
    LOG4CXX_TRACE(logger, "publicBlock -----> begin");
    render->parent->files[0]
            << std::string(4, ' ') << "public:" << std::endl;
    for (pbuilder::Column column : table.columns) {
        publicMember(column);
    }
    LOG4CXX_TRACE(logger, "publicMembers <----- end");
}

void TNTDBEntityDeclarationRender::publicMember(const pbuilder::Column & column) {
    LOG4CXX_TRACE(logger, "publicMembers -----> begin");
    if (column.nullable) {
        return;
    }
    render->parent->files[0]
            << std::string(6, ' ') << render->asText(column) << " " << column.name << ";" << std::endl;
    LOG4CXX_TRACE(logger, "publicMembers <----- end");
}