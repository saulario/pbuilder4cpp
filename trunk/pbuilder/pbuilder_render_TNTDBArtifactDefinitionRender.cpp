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

log4cxx::LoggerPtr TNTDBArtifactDefinitionRender::logger =
        log4cxx::Logger::getLogger("pbuilder::render::TNTDBArtifactDefinitionRender");

TNTDBArtifactDefinitionRender::TNTDBArtifactDefinitionRender(TNTDBRender * render_) : render(render_) {
    LOG4CXX_TRACE(logger, "TNTDBArtifactDefinitionRender -----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << "#ifndef " << boost::algorithm::to_upper_copy(render_->parent->pbuilder->unit.ns) << "_DAO_H" << std::endl
            << "#define " << boost::algorithm::to_upper_copy(render_->parent->pbuilder->unit.ns) << "_DAO_H" << std::endl
            << "#include <boost/thread/mutex.hpp>" << std::endl
            << "#include <boost/thread/thread.hpp>" << std::endl
            << "#include <tntdb/datetime.h>" << std::endl
            << "#include <tntdb/time.h>" << std::endl
            << "namespace " << render->parent->pbuilder->unit.ns << " {" << std::endl
            << std::string(2, ' ') << "namespace entity {" << std::endl;
    LOG4CXX_TRACE(logger, "TNTDBArtifactDefinitionRender <----- end");
}

TNTDBArtifactDefinitionRender::~TNTDBArtifactDefinitionRender() {
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDefinitionRender -----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << std::string(2, ' ') << "}" << std::endl
            << "}" << std::endl
            << "#endif" << std::endl;
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDefinitionRender <----- end");
}