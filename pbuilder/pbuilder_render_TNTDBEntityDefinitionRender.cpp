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
    render->parent->files[1]
            << "#include \"" 
            << render_->parent->pbuilder->unit.ns << "_entity.h\"" << std::endl;
    LOG4CXX_TRACE(logger, "TNTDBEntityDefinitionRender <----- end");
}

void TNTDBEntityDefinitionRender::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder::Table> p : render->parent->pbuilder->model.tables) {
//        table(p.second);
//        tableId(p.second);
    }
    LOG4CXX_TRACE(logger, "notify <----- end");
}