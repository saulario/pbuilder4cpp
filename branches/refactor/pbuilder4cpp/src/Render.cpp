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
#include <boost/algorithm/string.hpp>
#include "render.h"

using namespace pbuilder4cpp::render;

log4cxx::LoggerPtr Render::logger = log4cxx::Logger::getLogger("pbuilder4cpp::render::Render");

Render::Render(pbuilder4cpp::PersistenceBuilder * pbuilder_) : pbuilder(pbuilder_), implementation(0) {
    LOG4CXX_TRACE(logger, "Render -----> begin");
    implementation = static_cast<AbstractRender *> (new pbuilder4cpp::render::tntdb::Render(this));
    LOG4CXX_TRACE(logger, "Render <----- end");
}

Render::~Render() {
    LOG4CXX_TRACE(logger, "~Render -----> begin");
    delete implementation;
    LOG4CXX_TRACE(logger, "~Render <----- end");
}

void Render::render(void) {
    LOG4CXX_TRACE(logger, "render -----> begin");

    std::string basename(getenv("HOME"));
    //basename += "/" + pbuilder->unit.ns;
    basename = pbuilder->unit.ns;

    files[FD_ENTITY_H].open(basename + "_entity.h", std::ios::trunc);
    files[FD_ENTITY_CPP].open(basename + "_entity.cpp", std::ios::trunc);
    files[FD_ARTIFACT_H].open(basename + "_dao.h", std::ios::trunc);
    files[FD_ARTIFACT_CPP].open(basename + "_dao.cpp", std::ios::trunc);

    implementation->notify();

    files[FD_ARTIFACT_CPP].close();
    files[FD_ARTIFACT_H].close();
    files[FD_ENTITY_CPP].close();
    files[FD_ENTITY_H].close();

    LOG4CXX_TRACE(logger, "render <----- end");
}

std::string Render::toUpper(const std::string & str_) {
    LOG4CXX_TRACE(logger, "toUpper -----> begin");
    std::string str = "";
    
    if (!str_.empty()) {
        str = boost::algorithm::to_upper_copy(str_.substr(0, 1));
        if (str_.length() > 1) {
            str += str_.substr(1);
        }
    }
    
    LOG4CXX_TRACE(logger, "toUpper <----- end");
    return str;
}