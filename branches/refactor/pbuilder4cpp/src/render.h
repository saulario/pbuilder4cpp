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
#ifndef PBUILDER_RENDER_H
#define	PBUILDER_RENDER_H

#include <fstream>
#include "pbuilder4cpp.h"

namespace pbuilder4cpp {
    namespace render {

        class AbstractRender {
        public:
            virtual std::string asText(const pbuilder4cpp::Column & column_) = 0;
            virtual std::string defaultValue(const pbuilder4cpp::Column & column_) = 0;
            virtual void notify(void) = 0;
        };

        class Render {
        public:
            static const unsigned int FD_ENTITY_H = 0;
            static const unsigned int FD_ENTITY_CPP = 1;
            static const unsigned int FD_ARTIFACT_H = 2;
            static const unsigned int FD_ARTIFACT_CPP = 3;
            Render(pbuilder4cpp::PersistenceBuilder * pbuilder_);
            ~Render();
            void render(void);
            static std::string toUpper(const std::string & str_);
            std::ofstream files[4];
            pbuilder4cpp::PersistenceBuilder * pbuilder;
        private:
            static log4cxx::LoggerPtr logger;
            AbstractRender * implementation;
        };

    }
}

namespace pbuilder4cpp {
    namespace render {
        namespace tntdb {

            class Render : public pbuilder4cpp::render::AbstractRender {
            public:
                Render(pbuilder4cpp::render::Render *);
                std::string asText(const pbuilder4cpp::Column &);
                std::string defaultValue(const pbuilder4cpp::Column &);
                std::string rowGet(const pbuilder4cpp::Column &);
                std::string stmtSet(const pbuilder4cpp::Column &, const bool & = false);
                void notify(void);
                pbuilder4cpp::render::Render * parent;
            private:
                static log4cxx::LoggerPtr logger;
                std::string dateInitialization;
                std::string datetimeInitialization;
                std::string timeInitialization;
            };

            class ArtifactDeclaration {
            public:
                ArtifactDeclaration(Render *);
                ~ArtifactDeclaration();
                void notify(void);
            private:
                static log4cxx::LoggerPtr logger;
                Render * render;
                void table(const pbuilder4cpp::Table &);
                void tableExtended(const pbuilder4cpp::Table &);
            };

            class ArtifactDefinition {
            public:
                ArtifactDefinition(Render *);
                ~ArtifactDefinition();
                void notify(void);
            private:
                static log4cxx::LoggerPtr logger;
                Render * render;
                void constructor(const pbuilder4cpp::Table &);
                void destructor(const pbuilder4cpp::Table &);
                void getInstance(const pbuilder4cpp::Table &);
                void insert(const pbuilder4cpp::Table &);
                void keyInMethodSignature(const pbuilder4cpp::Table &);
                void keyInStatement(const pbuilder4cpp::Table &);
                void keyInUpdateStatement(const pbuilder4cpp::Table &);
                void loadColumn(const pbuilder4cpp::Table &, const pbuilder4cpp::Column &);
                void loadColumns(const pbuilder4cpp::Table &);
                void query(const pbuilder4cpp::Table &);
                void read(const pbuilder4cpp::Table &);
                void remove(const pbuilder4cpp::Table &);
                void update(const pbuilder4cpp::Table &);
                void setColumn(const pbuilder4cpp::Table &, const pbuilder4cpp::Column &);
                void setColumns(const pbuilder4cpp::Table &);
                void staticDefinition(const pbuilder4cpp::Table &);
            };

            class EntityDeclaration {
            public:
                EntityDeclaration(Render *);
                ~EntityDeclaration();
                void notify(void);
            private:
                static log4cxx::LoggerPtr logger;
                Render * render;
                void constructor(const pbuilder4cpp::Table &);
                void destructor(const pbuilder4cpp::Table &);
                void getter(const pbuilder4cpp::Column &);
                void isNull(const pbuilder4cpp::Column &);
                void operatorEquals(const pbuilder4cpp::Table &);
                void privateBlock(const pbuilder4cpp::Table &);
                void privateMember(const pbuilder4cpp::Column &);
                void privateMembers(const pbuilder4cpp::Table &);
                void publicBlock(const pbuilder4cpp::Table &);
                void publicMember(const pbuilder4cpp::Column &);
                void setter(const pbuilder4cpp::Column &);
                void setNull(const pbuilder4cpp::Column &);
                void table(const pbuilder4cpp::Table &);
                void tableId(const pbuilder4cpp::Table &);
            };

            class EntityDefinition {
            public:
                EntityDefinition(Render * render_);
                void notify(void);
            private:
                static log4cxx::LoggerPtr logger;
                Render * render;
                void constructor(const pbuilder4cpp::Table &);
                void destructor(const pbuilder4cpp::Table &);
                void getter(const pbuilder4cpp::Column &, const pbuilder4cpp::Table &);
                void isNull(const pbuilder4cpp::Column &, const pbuilder4cpp::Table &);
                void operatorEquals(const pbuilder4cpp::Table &);
                void privateMembers(const pbuilder4cpp::Table &);
                void setter(const pbuilder4cpp::Column &, const pbuilder4cpp::Table &);
                void setNull(const pbuilder4cpp::Column &, const pbuilder4cpp::Table &);
            };

        }
    }
}

#endif	/* PBUILDER_RENDER_H */

