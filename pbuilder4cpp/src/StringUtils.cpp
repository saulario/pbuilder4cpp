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

using namespace pbuilder;

log4cxx::LoggerPtr StringUtils::logger = log4cxx::Logger::getLogger("pbuilder::StringUtils");

std::string StringUtils::toCamelCase(const std::string & str_) {
    LOG4CXX_TRACE(logger, "toCamelCase -----> begin");

    std::stringstream ss;
    std::vector<std::string> strs;
    boost::split(strs, str_, boost::is_any_of("\t_ "));

    bool firstOne = true;
    for (auto & s1 : strs) {
        if (s1.empty()) {
            continue;
        }
        if (firstOne) {
            s1[0] = tolower(s1[0]);
            firstOne = false;
        } else {
            s1[0] = toupper(s1[0]);
        }
        ss << s1;
    }

    LOG4CXX_TRACE(logger, "toCamelCase <----- end");
    return ss.str();    
}

std::string StringUtils::toUpper(const std::string & str_) {
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
