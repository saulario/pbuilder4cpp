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
#include "pbuilder.h"

namespace pbuilder {
    namespace render {

        class AbstractRender {
        public:
            virtual std::string asText(const pbuilder::Column & column_) = 0;
            virtual std::string defaultValue(const pbuilder::Column & column_) = 0;
            virtual void notify(void) = 0;
        };

        class Render {
        public:
            static const unsigned int FD_ENTITY_H = 0;
            static const unsigned int FD_ENTITY_CPP = 1;
            static const unsigned int FD_ARTIFACT_H = 2;
            static const unsigned int FD_ARTIFACT_CPP = 3;
            Render(pbuilder::PersistenceBuilder * pbuilder_);
            ~Render();
            void render(void);
            static std::string toUpper(const std::string & str_);
            std::ofstream files[4];
            pbuilder::PersistenceBuilder * pbuilder;
        private:
            static log4cxx::LoggerPtr logger;
            AbstractRender * implementation;
        };

    }
}

namespace pbuilder {
    namespace render {
        namespace tntdb {

            class Render : public AbstractRender {
            public:
                Render(pbuilder::render::Render *);
                std::string asText(const pbuilder::Column &);
                std::string defaultValue(const pbuilder::Column &);
                std::string rowGet(const pbuilder::Column &);
                std::string stmtSet(const pbuilder::Column &, const bool & = false);
                void notify(void);
                pbuilder::render::Render * parent;
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
                void table(const pbuilder::Table &);
                void tableExtended(const pbuilder::Table &);
            };

            class ArtifactDefinition {
            public:
                ArtifactDefinition(Render *);
                ~ArtifactDefinition();
                void notify(void);
            private:
                static log4cxx::LoggerPtr logger;
                Render * render;
                void constructor(const pbuilder::Table &);
                void destructor(const pbuilder::Table &);
                void getInstance(const pbuilder::Table &);
                void insert(const pbuilder::Table &);
                void keyInMethodSignature(const pbuilder::Table &);
                void keyInStatement(const pbuilder::Table &);
                void keyInUpdateStatement(const pbuilder::Table &);
                void loadColumn(const pbuilder::Table &, const pbuilder::Column &);
                void loadColumns(const pbuilder::Table &);
                void query(const pbuilder::Table &);
                void read(const pbuilder::Table &);
                void remove(const pbuilder::Table &);
                void update(const pbuilder::Table &);
                void setColumn(const pbuilder::Table &, const pbuilder::Column &);
                void setColumns(const pbuilder::Table &);
                void staticDefinition(const pbuilder::Table &);
            };

            class EntityDeclaration {
            public:
                EntityDeclaration(Render *);
                ~EntityDeclaration();
                void notify(void);
            private:
                static log4cxx::LoggerPtr logger;
                Render * render;
                void constructor(const pbuilder::Table &);
                void destructor(const pbuilder::Table &);
                void getter(const pbuilder::Column &);
                void isNull(const pbuilder::Column &);
                void operatorEquals(const pbuilder::Table &);
                void privateBlock(const pbuilder::Table &);
                void privateMember(const pbuilder::Column &);
                void privateMembers(const pbuilder::Table &);
                void publicBlock(const pbuilder::Table &);
                void publicMember(const pbuilder::Column &);
                void setter(const pbuilder::Column &);
                void setNull(const pbuilder::Column &);
                void table(const pbuilder::Table &);
                void tableId(const pbuilder::Table &);
            };

            class EntityDefinition {
            public:
                EntityDefinition(Render * render_);
                void notify(void);
            private:
                static log4cxx::LoggerPtr logger;
                Render * render;
                void constructor(const pbuilder::Table &);
                void destructor(const pbuilder::Table &);
                void getter(const pbuilder::Column &, const pbuilder::Table &);
                void isNull(const pbuilder::Column &, const pbuilder::Table &);
                void operatorEquals(const pbuilder::Table &);
                void privateMembers(const pbuilder::Table &);
                void setter(const pbuilder::Column &, const pbuilder::Table &);
                void setNull(const pbuilder::Column &, const pbuilder::Table &);
            };

        }
    }
}

#endif	/* PBUILDER_RENDER_H */

