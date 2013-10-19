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
            virtual void renderEntityHeader(std::ofstream & file) = 0;
            virtual void renderEntityCode(std::ofstream & file) = 0;
            virtual void renderDAOHeader(std::ofstream & file) = 0;
            virtual void renderDAOCode(std::ofstream & file) = 0;
        };

        class Render {
        public:
            Render(pbuilder::PersistenceBuilder * pbuilder_);
            ~Render();
            void render(void);
            std::ofstream files[4];

        private:
            static log4cxx::LoggerPtr logger;
            pbuilder::PersistenceBuilder * pbuilder;
            AbstractRender * implementation;
        };

        class TNTDBRender : public AbstractRender {
        public:

            TNTDBRender(pbuilder::PersistenceBuilder * pbuilder_) : pbuilder(pbuilder_) {
            };
            void renderEntityHeader(std::ofstream & file);
            void renderEntityCode(std::ofstream & file);
            void renderDAOHeader(std::ofstream & file);
            void renderDAOCode(std::ofstream & file);

        private:
            static log4cxx::LoggerPtr logger;
            pbuilder::PersistenceBuilder * pbuilder;

            void renderEntityHeaderTable(std::ofstream & file, pbuilder::Table & table);
        };

        class TNTDBArtifactDeclarationRender {
        public:

            TNTDBArtifactDeclarationRender(TNTDBRender * render_) : render(render_) {
            };
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
        };

        class TNTDBArtifactDefinitionRender {
        public:

            TNTDBArtifactDefinitionRender(TNTDBRender * render_) : render(render_) {
            };
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
        };

        class TNTDBEntityDeclarationRender {
        public:

            TNTDBEntityDeclarationRender(TNTDBRender * render_) : render(render_) {
            };
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
        };

        class TNTDBEntityDefinitionRender {
        public:

            TNTDBEntityDefinitionRender(TNTDBRender * render_) : render(render_) {
            };
        private:
            static log4cxx::LoggerPtr logger;
            TNTDBRender * render;
        };

    }
}

#endif	/* PBUILDER_RENDER_H */
