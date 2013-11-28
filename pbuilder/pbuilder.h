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
#ifndef PBUILDER_H
#define	PBUILDER_H

#include <iostream>
#include <list>
#include <log4cxx/logger.h>
#include <map>

namespace pbuilder {

    enum MODEL_TYPE {
        SMALLINT,
        INTEGER,
        BIGINT,
        FLOAT,
        DOUBLE,
        STRING,
        CLOB,
        DATE,
        TIME,
        DATETIME,
        TIMESTAMP,
        BIT,
        BLOB,
        POINT,
        LINE,
        BOX,
        POLYGON,
        CIRCLE
    };

    struct Unit {
    public:
        std::string name;
        std::string database;
        std::string url;
        std::string ns;

        Unit() : name(""), database(""), url(""), ns("") {
        };

    };

    struct Column {
    public:
        std::string name;
        int position;
        bool isNullable;
        std::string schemaType;
        MODEL_TYPE type;
        long charMaxLength;
        long numericPrecision;
        long numericScale;
        bool isUnsigned;
        std::string defaultValue;
        std::string comment;

        Column() : name(""), position(0), isNullable(false), schemaType("")
        , type(STRING), charMaxLength(0L), numericPrecision(0L), numericScale(0L)
        , isUnsigned(false), defaultValue(""), comment("") {
        };
    };

    struct Table {
    public:
        std::string name;
        std::list<Column> columns;
        std::list<Column> pkColumns;

        Table(const std::string & pname) : name(pname) {
        }

    };

    struct Model {
    public:
        std::string name;
        std::map<std::string, Table> tables;

        Model() : name("") {
        }
    };

    class PersistenceBuilder {
    private:
        static log4cxx::LoggerPtr logger;

        std::string configFile;

        void analyze(void);
        void checkConfiguration(void);
        void evaluateParameters(int argc, char ** argv);
        void render(void);

    public:
        Unit unit;
        Model model;
        std::string table;

        PersistenceBuilder() : table(""), configFile("") {
        }
        int main(int argc, char ** argv);

    };

}

#endif	/* PBUILDER_H */