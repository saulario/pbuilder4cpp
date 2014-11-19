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
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/spi/configurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <boost/property_tree/ptree_fwd.hpp>

#include "pbuilder4cpp.h"
#include "analyzer.h"
#include "render.h"

using namespace pbuilder4cpp;

log4cxx::LoggerPtr PersistenceBuilder::logger = log4cxx::Logger::getLogger("pbuilder4cpp::PersistenceBuilder");

int PersistenceBuilder::main(int argc, char** argv) {

    int rv = EXIT_SUCCESS;

    checkConfiguration();
    std::string home(getenv("HOME"));
    log4cxx::PropertyConfigurator::configure(home + "/.pbuilder/etc/log4cxx.properties");

    LOG4CXX_INFO(logger, "main -----> begin")
    try {
        evaluateParameters(argc, argv);
        analyze();
        render();
    } catch (std::exception &e) {
        LOG4CXX_ERROR(logger, "*** exception report ***");
        LOG4CXX_ERROR(logger, std::string(e.what()));
        std::cerr << e.what() << std::endl;
        rv = EXIT_FAILURE;
    }
    LOG4CXX_INFO(logger, "main <----- end")
    return rv;
}

void PersistenceBuilder::analyze(void) {
    LOG4CXX_TRACE(logger, "analyze -----> begin");
    pbuilder4cpp::analyzer::Analyzer analyzer(this);
    analyzer.analyze();
    LOG4CXX_TRACE(logger, "analyze <----- end");
}

void PersistenceBuilder::checkConfiguration(void) {

    std::string pbDir(getenv("HOME"));
    pbDir.append("/.pbuilder");
    std::string confDir = pbDir + "/etc";
    std::string logDir = pbDir + "/log";

    struct stat sb;

    if (stat(pbDir.c_str(), &sb) == -1) {
        std::cerr << "Creating pbuilder directory structure" << std::endl;
        mkdir(pbDir.c_str(), 0755);
        mkdir(confDir.c_str(), 0755);
        mkdir(logDir.c_str(), 0755);
    }
    if (stat(confDir.c_str(), &sb) == -1) {
        std::cerr << "Creating pbuilder configuration directory" << std::endl;
        mkdir(confDir.c_str(), 0755);
    }
    if (stat(logDir.c_str(), &sb) == -1) {
        std::cerr << "Creating pbuilder log directory" << std::endl;
        mkdir(logDir.c_str(), 0755);
    }

    std::string f = confDir + "/log4cxx.properties";
    if (stat(f.c_str(), &sb) == -1) {
        std::cerr << "Creating pbuilder log4cxx configuration file" << std::endl;
        std::ofstream file;
        file.open(f.c_str(), std::ios::out);
        file
                << "log4j.rootLogger=INFO, pbuilder, stdout\n"
                << "log4j.appender.pbuilder=org.apache.log4j.RollingFileAppender\n"
                << "log4j.appender.pbuilder.File=" << logDir << "/pbuilder.log\n"
                << "log4j.appender.pbuilder.MaxFileSize=1024KB\n"
                << "log4j.appender.pbuilder.MaxBackupIndex=10\n"
                << "log4j.appender.pbuilder.layout=org.apache.log4j.PatternLayout\n"
                << "log4j.appender.pbuilder.layout.ConversionPattern=%d %p %c - %m%n\n"
                << "log4j.appender.stdout=org.apache.log4j.ConsoleAppender\n"
                << "log4j.appender.stdout.layout=org.apache.log4j.PatternLayout\n"
                ;
        file.close();
    }

    f = confDir + "/pbuilder.xml";
    if (stat(f.c_str(), &sb) == -1) {
        std::cerr << "Creating pbuilder configuration file" << std::endl;
        std::ofstream file;
        file.open(f.c_str(), std::ios::out);
        file
                << "<pbuilder>\n"
                << "\t<units>\n"
                << "\t\t<unit>\n"
                << "\t\t\t<name>test</name>\n"
                << "\t\t\t<database>test</database>\n"
                << "\t\t\t<url>mysql:db=information_schema</url>\n"
                << "\t\t\t<namespace>test</namespace>\n"
                << "\t\t\t<geometry>false</geometry>\n"
                << "\t\t</unit>\n"
                << "\t</units>\n"
                << "</pbuilder>\n"
                ;
        file.close();
    }
    configFile = f;
}

void PersistenceBuilder::evaluateParameters(int argc, char** argv) {
    LOG4CXX_TRACE(logger, "evaluateParameters -----> begin");

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("unit", boost::program_options::value<std::string>(), "configuration unit")
            ("table", boost::program_options::value<std::string>(), "pattern to select tables");

    boost::program_options::variables_map vm;
    boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc),
            vm
            );
    boost::program_options::notify(vm);

    if (!vm.count("unit")) {
        throw std::runtime_error("Parameter unit undefined");
    }
    std::string punit = vm["unit"].as<std::string>();
    model.name = punit;

    table = "%";
    if (vm.count("table")) {
        table = vm["table"].as<std::string>();
    }

    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(configFile, pt);
    std::map<std::string, Unit *>unitMap;

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            pt.get_child("pbuilder.units")) {
        Unit * unit = NULL;

        BOOST_FOREACH(boost::property_tree::ptree::value_type &v1,
                v.second.get_child("")) {
            std::string key(v1.first.data());
            std::string value(v1.second.data());
            if ("name" == key) {
                unit = new Unit();
                unitMap.insert(std::pair<std::string, Unit*>(value, unit));
            } else if (unit == NULL) {
                throw std::runtime_error("Malformed pbuilder.xml");
            }
            if ("name" == key) {
                unit->name = value;
                unit->database = value;
            } else if ("database" == key) {
                unit->database = value;
            } else if ("url" == key) {
                unit->url = value;
            } else if ("namespace" == key) {
                unit->ns = value;
            } else if ("geometry" == key) {
                std::istringstream(value) >> std::boolalpha >> unit->geometry;
            } else if ("dateInitialization" == key) {
                unit->dateInitialization = value;
            } else if ("datetimeInitialization" == key) {
                unit->datetimeInitialization = value;
            } else if ("timeInitialization" == key) {
                unit->timeInitialization = value;
            }
        }
    };

    if (unitMap.find(punit) == unitMap.end()) {
        throw std::runtime_error("Unconfigured unit");
    }
    Unit * ptr = unitMap.find(punit)->second;
    unit.name = ptr->name;
    unit.database = ptr->database;
    unit.url = ptr->url;
    unit.ns = ptr->ns;
    unit.geometry = ptr->geometry;
    unit.dateInitialization = ptr->dateInitialization;
    unit.datetimeInitialization = ptr->datetimeInitialization;
    unit.timeInitialization = ptr->timeInitialization;
    for (std::pair<std::string, Unit*> pair : unitMap) delete pair.second;

    LOG4CXX_TRACE(logger, "evaluateParameters <----- end");
}

void PersistenceBuilder::render(void) {
    LOG4CXX_TRACE(logger, "render -----> begin");
    pbuilder4cpp::render::Render render(this);
    render.render();
    LOG4CXX_TRACE(logger, "render <----- end");
}
