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
#ifndef PBUILDER_RENDER_H
#define	PBUILDER_RENDER_H

#include <fstream>
#include "pbuilder.h"

namespace pbuilder {
    namespace render {

        class AbstractRender {
        public:
            virtual std::string asText(const pbuilder::Column & column_) = 0;
            virtual void notify(void) = 0;
        };

        class Render {
        public:
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

        class TNTDBRender : public AbstractRender {
        public:

            TNTDBRender(Render * parent_) : parent(parent_) {
            };
            std::string asText(const pbuilder::Column & column_);
            void notify(void);
            Render * parent;
        private:
            static log4cxx::LoggerPtr logger;
        };

        class TNTDBArtifactDeclarationRender {
        public:

            TNTDBArtifactDeclarationRender(TNTDBRender * render_) : render(render_) {
            };
            void notify(void);
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
        };

        class TNTDBArtifactDefinitionRender {
        public:

            TNTDBArtifactDefinitionRender(TNTDBRender * render_) : render(render_) {
            };
            void notify(void);
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
        };

        class TNTDBEntityDeclarationRender {
        public:
            TNTDBEntityDeclarationRender(TNTDBRender * render_);
            ~TNTDBEntityDeclarationRender();
            void notify(void);
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
            void constructor(const pbuilder::Table & table_);
            void destructor(const pbuilder::Table & table_);
            void privateBlock(const pbuilder::Table & table_);
            void privateMember(const pbuilder::Column & column_);
            void publicBlock(const pbuilder::Table & table_);
            void publicMember(const pbuilder::Column & column_);
            void table(const pbuilder::Table & table_);
            void tableId(const pbuilder::Table & table_);
        };

        class TNTDBEntityDefinitionRender {
        public:
            TNTDBEntityDefinitionRender(TNTDBRender * render_);
            void notify(void);
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
            void constructor(const pbuilder::Table & table_);
            void destructor(const pbuilder::Table & table_);            
        };

    }
}

#endif	/* PBUILDER_RENDER_H */

