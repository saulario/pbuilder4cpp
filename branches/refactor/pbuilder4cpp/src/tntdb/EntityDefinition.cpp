/*
 * Persistence Builder (pbuilder4cpp)
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
#include "pbuilder4cpp.h"
#include "render.h"

using namespace pbuilder4cpp::render::tntdb;

log4cxx::LoggerPtr EntityDefinition::logger =
        log4cxx::Logger::getLogger("pbuilder4cpp::render::tntdb::EntityDefinition");

EntityDefinition::EntityDefinition(Render * render_) : render(render_) {
    LOG4CXX_TRACE(logger, "EntityDefinition -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "#include \""
            << render_->parent->pbuilder->unit.ns << "_entity.h\"" << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "using namespace "
            << render_->parent->pbuilder->unit.ns << "::entity;" << std::endl;

    LOG4CXX_TRACE(logger, "EntityDefinition <----- end");
}

void EntityDefinition::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder4cpp::Table> p : render->parent->pbuilder->model.tables) {
        constructor(p.second);
        destructor(p.second);
        privateMembers(p.second);
        operatorEquals(p.second);
    }
    LOG4CXX_TRACE(logger, "notify <----- end");
}

void EntityDefinition::constructor(const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "constructor -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << pbuilder4cpp::render::Render::toUpper(table_.name) << "::"
            << pbuilder4cpp::render::Render::toUpper(table_.name) << "() {"
            << std::endl;
    for (pbuilder4cpp::Column column : table_.columns) {
        if (column.isNullable) {
            render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << column.name << " = NULL;"
                    << std::endl;
        } else {
            render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << column.name << " = "
                    << render->defaultValue(column)
                    << ";" << std::endl;
        }
    }
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP] << "}" << std::endl;
    LOG4CXX_TRACE(logger, "constructor <----- end");
}

void EntityDefinition::destructor(const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "destructor -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << pbuilder4cpp::render::Render::toUpper(table_.name) << "::"
            << "~" << pbuilder4cpp::render::Render::toUpper(table_.name) << "() {"
            << std::endl;
    for (pbuilder4cpp::Column column : table_.columns) {
        if (column.isNullable) {
            render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << "if (" << column.name << " != NULL) {"
                    << std::endl;
            render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
                    << std::string(4, ' ')
                    << "delete " << column.name << ";"
                    << std::endl;
            render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
                    << std::string(2, ' ')
                    << "}"
                    << std::endl;
        }
    }
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP] << "}" << std::endl;
    LOG4CXX_TRACE(logger, "destructor <----- end");
}

void EntityDefinition::getter(const pbuilder4cpp::Column & column_, const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "getter -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << render->asText(column_)
            << " " << pbuilder4cpp::render::Render::toUpper(table_.name) << "::"
            << "get" << pbuilder4cpp::render::Render::toUpper(column_.name)
            << "(void) const {"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "return ("
            << column_.name << " != NULL ? * " << column_.name
            << " : " << render->defaultValue(column_) << ");"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "getter <----- end");
}

void EntityDefinition::isNull(const pbuilder4cpp::Column & column_, const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "isNull -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "bool " << pbuilder4cpp::render::Render::toUpper(table_.name) << "::"
            << "isNull" << pbuilder4cpp::render::Render::toUpper(column_.name)
            << "(void) const {"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "return (" << column_.name << " == NULL);"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "isNull <----- end");
}

void EntityDefinition::operatorEquals(const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "operatorEquals -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "bool "
            << pbuilder4cpp::render::Render::toUpper(table_.name) << "::"
            << "operator == (const "
            << pbuilder4cpp::render::Render::toUpper(table_.name)
            << " & other) {"
            << std::endl;
    for (pbuilder4cpp::Column column : table_.columns) {
        render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
                << std::string(2, ' ')
                << "if (this->"
                << column.name
                << " != other."
                << column.name
                << ") return false;"
                << std::endl;
    }
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "return true;"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP] << "}" << std::endl;
    LOG4CXX_TRACE(logger, "operatorEquals <----- end");
}

void EntityDefinition::privateMembers(const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "privateMember -----> begin");
    for (pbuilder4cpp::Column column : table_.columns) {
        if (column.isNullable) {
            getter(column, table_);
            setter(column, table_);
            isNull(column, table_);
            setNull(column, table_);
        }
    }
    LOG4CXX_TRACE(logger, "privateMember <----- end");
}

void EntityDefinition::setter(const pbuilder4cpp::Column & column_, const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "setter -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "void " << pbuilder4cpp::render::Render::toUpper(table_.name) << "::"
            << "set" << pbuilder4cpp::render::Render::toUpper(column_.name) << "(const "
            << render->asText(column_)
            << " & " << column_.name << "_) {"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "if (" << column_.name << " != NULL) {"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(4, ' ')
            << "delete " << column_.name << ";"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << "}"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << column_.name << " = new "
            << render->asText(column_)
            << "(" << column_.name << "_);"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "setter <----- end");
}

void EntityDefinition::setNull(const pbuilder4cpp::Column & column_, const pbuilder4cpp::Table & table_) {
    LOG4CXX_TRACE(logger, "setNull -----> begin");
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "void " << pbuilder4cpp::render::Render::toUpper(table_.name) << "::"
            << "setNull" << pbuilder4cpp::render::Render::toUpper(column_.name)
            << "(void) {"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ') << "if ("
            << column_.name << " != NULL) {"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(4, ' ')
            << "delete " << column_.name << ";"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ') << "}"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << std::string(2, ' ')
            << column_.name << " = NULL;"
            << std::endl;
    render->parent->files[pbuilder4cpp::render::Render::FD_ENTITY_CPP]
            << "}"
            << std::endl;
    LOG4CXX_TRACE(logger, "setNull <----- end");
}
