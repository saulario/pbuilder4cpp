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
#include <iomanip>

#include "pbuilder.h"
#include "pbuilder_render.h"

using namespace pbuilder::render::tntdb;

log4cxx::LoggerPtr Render::logger = log4cxx::Logger::getLogger("pbuilder::render::tntdb::Render");

Render::Render(pbuilder::render::Render * parent_) : parent(parent_) {
    dateInitialization = "tntdb::Date()";
    if (!parent->pbuilder->unit.dateInitialization.empty()) {
        dateInitialization = parent->pbuilder->unit.dateInitialization;
    }
    datetimeInitialization = "tntdb::Datetime()";
    if (!parent->pbuilder->unit.datetimeInitialization.empty()) {
        datetimeInitialization = parent->pbuilder->unit.datetimeInitialization;
    }
    timeInitialization = "tntdb::Time()";
    if (!parent->pbuilder->unit.timeInitialization.empty()) {
        timeInitialization = parent->pbuilder->unit.timeInitialization;
    }
}

std::string Render::asText(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "asText -----> begin");
    std::string value = "";
    switch (column_.type) {
        case SMALLINT:
            value = std::string((column_.isUnsigned ? "unsigned " : "")) + "short";
            break;
        case MEDIUMINT:
            value = std::string((column_.isUnsigned ? "unsigned " : "")) + "int";
            break;
        case INTEGER:
            value = std::string((column_.isUnsigned ? "unsigned " : "")) + "int";
            break;
        case BIGINT:
            value = std::string((column_.isUnsigned ? "unsigned " : "")) + "long";
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

std::string Render::defaultValue(const pbuilder::Column & column_) {
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
            value = dateInitialization;
            break;
        case TIME:
            value = timeInitialization;
            break;
        case DATETIME:
        case TIMESTAMP:
            value = datetimeInitialization;
            break;
        default:
            value = "\"\"";
    }
    LOG4CXX_TRACE(logger, "defaultValue <----- end");
    return value;
}

void Render::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");

    ArtifactDeclaration adec(this);
    ArtifactDefinition adef(this);
    EntityDeclaration edec(this);
    EntityDefinition edef(this);

    adec.notify();
    adef.notify();
    edec.notify();
    edef.notify();

    LOG4CXX_TRACE(logger, "notify <----- end");
}

std::string Render::rowGet(const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "rowGet -----> begin");
    std::string value = "row.get";
    switch (column_.type) {
        case SMALLINT:
            if (column_.isUnsigned) {
                value += "Unsigned";
            } else {
                value += "Int";
            }
            break;
        case MEDIUMINT:
            if (column_.isUnsigned) {
                value += "Unsigned";
            } else {
                value += "Int";
            }
            break;
        case INTEGER:
            if (column_.isUnsigned) {
                value += "Unsigned";
            } else {
                value += "Int";
            }
            break;
        case BIGINT:
            if (column_.isUnsigned) {
                value += "Unsigned64";
            } else {
                value += "Int64";
            }
            break;
        case FLOAT:
            value += "Decimal";
            break;
        case DOUBLE:
            value += "Decimal";
            break;
        case STRING:
        case CLOB:
            value += "String";
            break;
        case BLOB:
            value += "Blob";
            break;
        case DATE:
            value += "Date";
            break;
        case TIME:
            value += "Time";
            break;
        case DATETIME:
        case TIMESTAMP:
            value += "Datetime";
            break;
        default:
            value = "String";
    }
    value += "(index++)";

    switch (column_.type) {
        case FLOAT:
            value += ".getFloat()";
            break;
        case DOUBLE:
            value += ".getDouble()";
            break;
    }

    LOG4CXX_TRACE(logger, "rowGet <----- end");
    return value;
}

std::string Render::stmtSet(const pbuilder::Column & column_, const bool & nullable_) {
    LOG4CXX_TRACE(logger, "stmtSet -----> begin");
    std::string value = "stmt.set";
    std::string suffix = "";
    switch (column_.type) {
        case SMALLINT:
            if (column_.isUnsigned) {
                value += "Unsigned";
            } else {
                value += "Int";
            }
            break;
        case MEDIUMINT:
            if (column_.isUnsigned) {
                value += "Unsigned";
            } else {
                value += "Int";
            }
            break;
        case INTEGER:
            if (column_.isUnsigned) {
                value += "Unsigned";
            } else {
                value += "Int";
            }
            break;
        case BIGINT:
            if (column_.isUnsigned) {
                value += "Unsigned64";
            } else {
                value += "Int64";
            }
            break;
        case FLOAT:
            value += "Float";
            break;
        case DOUBLE:
            value += "Double";
            break;
        case STRING:
        case CLOB:
            value += "String";
            break;
        case BLOB:
            value += "Blob";
            break;
        case DATE:
            value += "Date";
            break;
        case TIME:
            value += "Time";
            break;
        case DATETIME:
        case TIMESTAMP:
            value += "";
            suffix = ".getIso()";
            break;
        default:
            value = "String";
    }
    if (!nullable_) {
        value += "(\"" + column_.name + "\", e->" + column_.name + suffix + ");";
    } else {
        value += "(\"" + column_.name + "\", e->get" + parent->toUpper(column_.name) + "());";
    }

    LOG4CXX_TRACE(logger, "stmtSet <----- end");
    return value;
}