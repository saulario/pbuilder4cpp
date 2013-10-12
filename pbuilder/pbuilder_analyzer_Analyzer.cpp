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
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "pbuilder_analyzer.h"

using namespace pbuilder::analyzer;

log4cxx::LoggerPtr Analyzer::logger = log4cxx::Logger::getLogger("pbuilder::analyzer::Analyzer");

Analyzer::Analyzer(pbuilder::PersistenceBuilder & pb) : pbuilder(pb), implementation(0) {
    LOG4CXX_TRACE(logger, "Analyzer -----> begin");
    
    std::string::size_type n = pbuilder.unit.url.find(":");
    if (n == std::string::npos) {
        throw std::runtime_error("Invalid url");
    }
    
    std::string driver = pbuilder.unit.url.substr(0, n);
    if (driver.compare("mysql") == 0) {
        implementation = static_cast<AbstractAnalyzer *> (new MysqlAnalyzer(pbuilder));
//    } else if (driver.compare("postgresql")) {
//        implementation = static_cast<AbstractAnalyzer *> (new PostgresqlAnalyzer(pbuilder));
//    } else if (driver.compare("oracle")) {
//        implementation = static_cast<AbstractAnalyzer *> (new OracleAnalyzer(pbuilder));
//    } else if (driver.compare("sqlite")) {
//        implementation = static_cast<AbstractAnalyzer *> (new SqliteAnalyzer(pbuilder));
    } else {
        throw std::runtime_error("Invalid driver");
    }

    LOG4CXX_TRACE(logger, "Analyzer <----- end");
}

void Analyzer::analyze(void) {
    LOG4CXX_TRACE(logger, "analyze -----> begin");
    implementation->analyze();
    LOG4CXX_TRACE(logger, "analyze <----- end");
}