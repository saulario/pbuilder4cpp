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
#ifndef PBUILDER_ANALYZER_H
#define	PBUILDER_ANALYZER_H

#include <tntdb/connection.h>
#include "pbuilder.h"

namespace pbuilder {
    namespace analyzer {

        class AbstractAnalyzer {
        public:
            virtual void analyze(void) = 0;

        private:
            virtual pbuilder::MODEL_TYPE getModelType(const std::string &) = 0;
        };

        class Analyzer {
        public:
            Analyzer(pbuilder::PersistenceBuilder & pbuilder);
            void analyze(void);

        private:
            static log4cxx::LoggerPtr logger;
            pbuilder::PersistenceBuilder pbuilder;
            AbstractAnalyzer * implementation;
        };

        class TNTDBAnalyzer {
        protected:
            tntdb::Connection connection;

        };

        class MysqlAnalyzer : public AbstractAnalyzer, public TNTDBAnalyzer {
        public:

            MysqlAnalyzer(pbuilder::PersistenceBuilder & p) : pbuilder(p) {
            };
            void analyze(void);

        private:
            static log4cxx::LoggerPtr logger;
            pbuilder::PersistenceBuilder & pbuilder;

            pbuilder::MODEL_TYPE getModelType(const std::string & ptype);
        };


    }
}

#endif	/* PBUILDER_ANALYZER_H */

