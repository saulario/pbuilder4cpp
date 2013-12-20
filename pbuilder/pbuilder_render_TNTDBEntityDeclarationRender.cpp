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

log4cxx::LoggerPtr TNTDBEntityDeclarationRender::logger =
        log4cxx::Logger::getLogger("pbuilder::render::TNTDBEntityDeclarationRender");

TNTDBEntityDeclarationRender::TNTDBEntityDeclarationRender(TNTDBRender * render_) : render(render_) {
    LOG4CXX_TRACE(logger, "TNTDBEntityDeclarationRender -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << "#ifndef " << boost::algorithm::to_upper_copy(render_->parent->pbuilder->unit.ns) << "_ENTITY_H" << std::endl
            << "#define " << boost::algorithm::to_upper_copy(render_->parent->pbuilder->unit.ns) << "_ENTITY_H" << std::endl
            << "#include <tntdb/blob.h>" << std::endl
            << "#include <tntdb/date.h>" << std::endl
            << "#include <tntdb/datetime.h>" << std::endl
            << "#include <tntdb/time.h>" << std::endl
            << "namespace " << render->parent->pbuilder->unit.ns << " {" << std::endl
            << std::string(2, ' ') << "namespace entity {" << std::endl;
    LOG4CXX_TRACE(logger, "TNTDBEntityDeclarationRender <----- end");
}

TNTDBEntityDeclarationRender::~TNTDBEntityDeclarationRender() {
    LOG4CXX_TRACE(logger, "~TNTDBEntityDeclarationRender -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(2, ' ') << "}" << std::endl
            << "}" << std::endl
            << "#endif" << std::endl;
    LOG4CXX_TRACE(logger, "~TNTDBEntityDeclarationRender <----- end");
}

void TNTDBEntityDeclarationRender::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder::Table> p : render->parent->pbuilder->model.tables) {
        table(p.second);
        tableId(p.second);
    }
    LOG4CXX_TRACE(logger, "notify <----- end");
}

void TNTDBEntityDeclarationRender::constructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "constructor -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ')
            << pbuilder::render::Render::toUpper(table_.name) << "();"
            << std::endl;
    LOG4CXX_TRACE(logger, "constructor <----- end");
}

void TNTDBEntityDeclarationRender::destructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "destructor -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ')
            << "~" << pbuilder::render::Render::toUpper(table_.name) << "();"
            << std::endl;
    LOG4CXX_TRACE(logger, "destructor <----- end");
}

void TNTDBEntityDeclarationRender::getter(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "getter -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ') << render->asText(column_)
            << " get" << pbuilder::render::Render::toUpper(column_.name)
            << "(void) const;"
            << std::endl;
    LOG4CXX_TRACE(logger, "getter <----- end");
}

void TNTDBEntityDeclarationRender::operatorEquals(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "operatorEquals -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ') 
            << "bool operator == (const " 
            << pbuilder::render::Render::toUpper(table_.name)
            << " *);"
            << std::endl;
    LOG4CXX_TRACE(logger, "operatorEquals <----- end");
}

void TNTDBEntityDeclarationRender::isNull(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "isNull -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ') 
            << "bool isNull" << pbuilder::render::Render::toUpper(column_.name)
            << "(void) const;"
            << std::endl;
    LOG4CXX_TRACE(logger, "isNull <----- end");
}

void TNTDBEntityDeclarationRender::privateBlock(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "privateBlock -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(4, ' ') << "private:" << std::endl;
    for (pbuilder::Column column : table_.columns) {
        privateMember(column);
    }
    LOG4CXX_TRACE(logger, "privateBlock <----- end");
}

void TNTDBEntityDeclarationRender::privateMember(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "privateMember -----> begin");
    if (!column_.isNullable) {
        LOG4CXX_TRACE(logger, "privateMember <----- exiting");
        return;
    }
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ') << render->asText(column_)
            << " * " << column_.name << ";"
            << " /* " << column_.comment << " */"
            << std::endl;
    LOG4CXX_TRACE(logger, "privateMember <----- end");
}

void TNTDBEntityDeclarationRender::privateMembers(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "privateMembers -----> begin");
    for (pbuilder::Column column : table_.columns) {
        if (column.isNullable) {
            getter(column);
            setter(column);
            isNull(column);
            setNull(column);
        }
    }
    LOG4CXX_TRACE(logger, "privateMembers <----- end");
}

void TNTDBEntityDeclarationRender::publicBlock(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "publicBlock -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(4, ' ') << "public:" << std::endl;
    for (pbuilder::Column column : table_.columns) {
        publicMember(column);
    }
    constructor(table_);
    destructor(table_);
    privateMembers(table_);
    operatorEquals(table_);
    LOG4CXX_TRACE(logger, "publicBlock <----- end");
}

void TNTDBEntityDeclarationRender::publicMember(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "publicMember -----> begin");
    if (column_.isNullable) {
        LOG4CXX_TRACE(logger, "publicMember <----- exiting");
        return;
    }
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ') << render->asText(column_)
            << " " << column_.name << ";"
            << " /* " << column_.comment << " */" 
            << std::endl;
    LOG4CXX_TRACE(logger, "publicMember <----- end");
}

void TNTDBEntityDeclarationRender::setter(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "setter -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ') << "void set"
            << pbuilder::render::Render::toUpper(column_.name) << "(const "
            << render->asText(column_)
            << " & " << column_.name << ");"
            << std::endl;
    LOG4CXX_TRACE(logger, "setter <----- end");
}

void TNTDBEntityDeclarationRender::setNull(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "setNull -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(6, ' ') 
            << "void setNull" << pbuilder::render::Render::toUpper(column_.name)
            << "(void);"
            << std::endl;
    LOG4CXX_TRACE(logger, "setNull <----- end");
}

void TNTDBEntityDeclarationRender::table(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "table -----> begin");
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(4, ' ') << "struct " << pbuilder::render::Render::toUpper(table_.name) << " {" << std::endl;
    publicBlock(table_);
    privateBlock(table_);
    render->parent->files[Render::FD_ENTITY_H]
            << std::string(4, ' ') << "};" << std::endl;
    LOG4CXX_TRACE(logger, "table <----- end");
}

void TNTDBEntityDeclarationRender::tableId(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "tableId -----> begin");
    if (table_.pkColumns.size() <= 1) {
        LOG4CXX_TRACE(logger, "tableId <----- exiting");
        return;
    }
    pbuilder::Table t(table_.name + "Id");
    t.columns = table_.pkColumns;
    table(t);
    LOG4CXX_TRACE(logger, "tableId <----- end");
}