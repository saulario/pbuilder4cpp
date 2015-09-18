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

log4cxx::LoggerPtr TNTDBEntityDefinitionRender::logger =
        log4cxx::Logger::getLogger("pbuilder::render::TNTDBEntityDefinitionRender");

TNTDBEntityDefinitionRender::TNTDBEntityDefinitionRender(TNTDBRender * render_) : render(render_) {
    LOG4CXX_TRACE(logger, "TNTDBEntityDefinitionRender -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << "#include \""
            << render_->parent->pbuilder->unit.ns << "_entity.h\"" << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << "using namespace "
            << render_->parent->pbuilder->unit.ns << "::entity;" << std::endl;

    LOG4CXX_TRACE(logger, "TNTDBEntityDefinitionRender <----- end");
}

void TNTDBEntityDefinitionRender::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder::Table> p : render->parent->pbuilder->model.tables) {
        constructor(p.second);
        destructor(p.second);
        privateMembers(p.second);
        operatorEquals(p.second);
    }
    LOG4CXX_TRACE(logger, "notify <----- end");
}

void TNTDBEntityDefinitionRender::constructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "constructor -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << pbuilder::StringUtils::toUpper(table_.applicationName) << "::"
            << pbuilder::StringUtils::toUpper(table_.applicationName) << "() {"
            << std::endl;
    for (pbuilder::Column column : table_.columns) {
        if (column.isNullable) {
            render->parent->files[Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << column.applicationName << " = NULL;"
                    << std::endl;
        } else {
            render->parent->files[Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << column.applicationName << " = "
                    << render->defaultValue(column)
                    << ";" << std::endl;
        }
    }
    render->parent->files[Render::FD_ENTITY_CPP] << "}" << std::endl;
    LOG4CXX_TRACE(logger, "constructor <----- end");
}

void TNTDBEntityDefinitionRender::destructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "destructor -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << pbuilder::StringUtils::toUpper(table_.applicationName) << "::"
            << "~" << pbuilder::StringUtils::toUpper(table_.applicationName) << "() {"
            << std::endl;
    for (pbuilder::Column column : table_.columns) {
        if (column.isNullable) {
            render->parent->files[Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << "if (" << column.applicationName << " != NULL) {"
                    << std::endl;
            render->parent->files[Render::FD_ENTITY_CPP]
                    << std::string(4, ' ')
                    << "delete " << column.applicationName << ";"
                    << std::endl;
            render->parent->files[Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << "}"
                    << std::endl;
        }
    }
    render->parent->files[Render::FD_ENTITY_CPP] << "}" << std::endl;
    LOG4CXX_TRACE(logger, "destructor <----- end");
}

void TNTDBEntityDefinitionRender::getter(const pbuilder::Column & column_, const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "getter -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << render->asText(column_)
            << " " << pbuilder::StringUtils::toUpper(table_.applicationName) << "::"
            << "get" << pbuilder::StringUtils::toUpper(column_.applicationName)
            << "(void) const {"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "return ("
            << column_.applicationName << " != NULL ? * " << column_.applicationName
            << " : " << render->defaultValue(column_) << ");"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "getter <----- end");
}

void TNTDBEntityDefinitionRender::isNull(const pbuilder::Column & column_, const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "isNull -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << "bool " << pbuilder::StringUtils::toUpper(table_.applicationName) << "::"
            << "isNull" << pbuilder::StringUtils::toUpper(column_.applicationName)
            << "(void) const {"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "return (" << column_.applicationName << " == NULL);"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "isNull <----- end");
}

void TNTDBEntityDefinitionRender::operatorEquals(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "operatorEquals -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << "bool "
            << pbuilder::StringUtils::toUpper(table_.applicationName) << "::"
            << "operator == (const "
            << pbuilder::StringUtils::toUpper(table_.applicationName)
            << " & other) {"
            << std::endl;
    for (pbuilder::Column column : table_.columns) {
        render->parent->files[Render::FD_ENTITY_CPP]
                << std::string(2, ' ')
                << "if (this->"
                << column.applicationName
                << " != other."
                << column.applicationName
                << ") return false;"
                << std::endl;
    }
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "return true;"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP] << "}" << std::endl;
    LOG4CXX_TRACE(logger, "operatorEquals <----- end");
}

void TNTDBEntityDefinitionRender::privateMembers(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "privateMember -----> begin");
    for (pbuilder::Column column : table_.columns) {
        if (column.isNullable) {
            getter(column, table_);
            setter(column, table_);
            isNull(column, table_);
            setNull(column, table_);
        }
    }
    LOG4CXX_TRACE(logger, "privateMember <----- end");
}

void TNTDBEntityDefinitionRender::setter(const pbuilder::Column & column_, const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "setter -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << "void " << pbuilder::StringUtils::toUpper(table_.applicationName) << "::"
            << "set" << pbuilder::StringUtils::toUpper(column_.applicationName) << "(const "
            << render->asText(column_)
            << " & " << column_.applicationName << "_) {"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "if (" << column_.applicationName << " != NULL) {"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(4, ' ')
            << "delete " << column_.applicationName << ";"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "}"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << column_.applicationName << " = new "
            << render->asText(column_)
            << "(" << column_.applicationName << "_);"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "setter <----- end");
}

void TNTDBEntityDefinitionRender::setNull(const pbuilder::Column & column_, const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "setNull -----> begin");
    render->parent->files[Render::FD_ENTITY_CPP]
            << "void " << pbuilder::StringUtils::toUpper(table_.applicationName) << "::"
            << "setNull" << pbuilder::StringUtils::toUpper(column_.applicationName)
            << "(void) {"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ') << "if ("
            << column_.applicationName << " != NULL) {"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(4, ' ')
            << "delete " << column_.applicationName << ";"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ') << "}"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << column_.applicationName << " = NULL;"
            << std::endl;
    render->parent->files[Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "setNull <----- end");
}
