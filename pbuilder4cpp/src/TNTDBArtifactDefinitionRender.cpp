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
            << "#include <boost/algorithm/string/split.hpp>" << std::endl
            << "#include <boost/algorithm/string/predicate.hpp>" << std::endl
            << "#include <boost/algorithm/string/classification.hpp>" << std::endl
            << "#include <tntdb/error.h>" << std::endl
            << "#include \"" << render->parent->pbuilder->unit.ns << "_dao.h\"" << std::endl
            << "using namespace " << render->parent->pbuilder->unit.ns << "::dao;" << std::endl;
    ;

    static const char * common = R"DELIM(        
void CommonDAO::createQueries(void) {
    insertQuery = "insert into " + table + "(" + columns + ")"
            " values("
            ;
    std::vector<std::string> fields;
    bool first = true;
    boost::algorithm::split(fields, columns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            insertQuery += ",";
        }
        first = false;
        insertQuery += ":" + f;
    }
    insertQuery += ")";
    readQuery = "select " + columns + " from " + table + " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            readQuery += " and ";
        }
        first = false;
        readQuery += f + "=:" + f + "PK";
    }
    removeQuery = "delete from " + table + " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            removeQuery += " and ";
        }
        first = false;
        removeQuery += f + "=:" + f + "PK";
    }
    updateQuery = "update " + table + " set ";
    first = true;
    boost::algorithm::split(fields, columns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            updateQuery += ",";
        }
        first = false;
        updateQuery += f + "=:" + f;
    }
    updateQuery += " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            updateQuery += " and ";
        }
        first = false;
        updateQuery += f + "=:" + f + "PK";
    }
}
std::string CommonDAO::getInsertQuery(void) {
    return insertQuery;
}
std::string CommonDAO::getReadQuery(void) {
    return readQuery;
}
std::string CommonDAO::getRemoveQuery(void) {
    return removeQuery;
}
std::string CommonDAO::getUpdateQuery(void) {
    return updateQuery;
}
std::string CommonDAO::getColumns(void) {
    return columns;
}
std::string CommonDAO::getTable(void) {
    return table;
}
)DELIM";
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << common
            << std::endl;
    LOG4CXX_TRACE(logger, "TNTDBArtifactDefinitionRender <----- end");
}

TNTDBArtifactDefinitionRender::~TNTDBArtifactDefinitionRender() {
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDefinitionRender -----> begin");
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDefinitionRender <----- end");
}

void TNTDBArtifactDefinitionRender::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder::Table> p : render->parent->pbuilder->model.tables) {
        staticDefinition(p.second);
        constructor(p.second);
        destructor(p.second);
        getInstance(p.second);
        insert(p.second);
        query(p.second);
        if (p.second.pkColumns.size() > 0) {
            read(p.second);
            remove(p.second);
            update(p.second);
        }
        loadColumns(p.second);
        setColumns(p.second);
    }
    LOG4CXX_TRACE(logger, "notify <----- end");
}

void TNTDBArtifactDefinitionRender::constructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "constructor -----> begin");
    LOG4CXX_TRACE(logger, "constructor <----- end");
}

void TNTDBArtifactDefinitionRender::destructor(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "destructor -----> begin");
    static const char * cdn = R"DELIM(        
OBJECT::~OBJECT() {
    if (dao != NULL) {
        delete dao;
    }
}
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "OBJECT", pbuilder::StringUtils::toUpper(table_.applicationName) + "DAO");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "destructor <----- end");
}

void TNTDBArtifactDefinitionRender::getInstance(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "getInstance -----> begin");
    static const char * cdn = R"DELIM(        
OBJECT * OBJECT::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new OBJECT();
        dao->table = "TABLE";
        dao->keyColumns = "KCOLS";
        dao->columns = "COLS";
        dao->createQueries();
    }
    return dao;
}
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "OBJECT", pbuilder::StringUtils::toUpper(table_.applicationName) + "DAO");
    boost::replace_all(str, "TABLE", table_.name);
    std::string cols = "";
    bool first = true;
    for (pbuilder::Column c : table_.pkColumns) {
        if (!first) {
            cols += ",";
        }
        first = false;
        cols += c.name;
    }
    boost::replace_all(str, "KCOLS", cols);
    cols = "";
    first = true;
    int count = 0;
    for (pbuilder::Column c : table_.columns) {
        count++;
        if (!first) {
            if (!(count % 5)) {
                cols += "\"";
                cols += '\n';
                cols += "\"";
            }
            cols += ",";
        }
        first = false;
        cols += c.name;
    }
    boost::replace_all(str, "COLS", cols);
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "getInstance <----- end");
}

void TNTDBArtifactDefinitionRender::keyInMethodSignature(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "keyInMethodSignature -----> begin");
    if (table_.pkColumns.size() == 1) {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << " " << render->asText(table_.pkColumns.front())
                << " & " << table_.pkColumns.front().applicationName;
    } else {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << " " << render->parent->pbuilder->unit.ns
                << "::entity::"
                << pbuilder::StringUtils::toUpper(table_.applicationName) << "Id & id";
    }
    LOG4CXX_TRACE(logger, "keyInMethodSignature <----- end");
}

void TNTDBArtifactDefinitionRender::keyInStatement(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "keyInStatement -----> begin");
    std::string prefix = (table_.pkColumns.size() > 1 ? "id." : "");
    for (pbuilder::Column c : table_.pkColumns) {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << std::string(8, ' ')
                << "stmt.set(\"" << c.name << "PK\", "
                << prefix << c.applicationName << ");"
                << std::endl;
    }
    LOG4CXX_TRACE(logger, "keyInStatement <----- end");
}

void TNTDBArtifactDefinitionRender::keyInUpdateStatement(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "keyInStatement -----> begin");
    for (pbuilder::Column c : table_.pkColumns) {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << std::string(4, ' ')
                << "stmt.set(\"" << c.name << "PK\", "
                << "e->" << c.applicationName << ");"
                << std::endl;
    }
    LOG4CXX_TRACE(logger, "keyInStatement <----- end");
}

void TNTDBArtifactDefinitionRender::insert(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "insert -----> begin");
    static const char * cdn = R"DELIM(        
ENTITY * OBJECT::insert(tntdb::Connection & con, ENTITY * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "ENTITY", render->parent->pbuilder->unit.ns + "::entity::"
            + pbuilder::StringUtils::toUpper(table_.applicationName));
    boost::replace_all(str, "OBJECT", pbuilder::StringUtils::toUpper(table_.applicationName) + "DAO");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "insert <----- end");
}

void TNTDBArtifactDefinitionRender::loadColumn(const pbuilder::Table & table_, const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "loadColumn-----> begin");
    if (column_.isNullable) {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << std::string(4, ' ') << "try {" << std::endl
                << std::string(8, ' ')
                << "e->set" << pbuilder::StringUtils::toUpper(column_.applicationName) << "("
                << render->rowGet(column_)
                << ");" << std::endl
                << std::string(4, ' ') << "} catch(tntdb::NullValue) {" << std::endl
                << std::string(8, ' ')
                << "e->setNull" << pbuilder::StringUtils::toUpper(column_.applicationName) << "();" << std::endl
                << std::string(4, ' ') << "}"
                << std::endl;
    } else {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << std::string(4, ' ')
                << "e->" << column_.applicationName << " = " << render->rowGet(column_) << ";"
                << std::endl;
    }
    LOG4CXX_TRACE(logger, "loadColumn <----- end");
}

void TNTDBArtifactDefinitionRender::loadColumns(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "loadColumns-----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << "void " << pbuilder::StringUtils::toUpper(table_.applicationName) << "DAO"
            << "::loadColumns(tntdb::Row & row, "
            << render->parent->pbuilder->unit.ns << "::entity::"
            << pbuilder::StringUtils::toUpper(table_.applicationName)
            << " * e) {"
            << std::endl;
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << std::string(4, ' ')
            << "int index = 0;"
            << std::endl;
    for (pbuilder::Column c : table_.columns) {
        loadColumn(table_, c);
    }
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << "}"
            << std::endl << std::endl;
    LOG4CXX_TRACE(logger, "loadColumns <----- end");
}

void TNTDBArtifactDefinitionRender::query(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "query -----> begin");
    static const char * cdn = R"DELIM(        
std::list<ENTITY *> OBJECT::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ENTITY *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ENTITY * e = new ENTITY;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "ENTITY", render->parent->pbuilder->unit.ns + "::entity::"
            + pbuilder::StringUtils::toUpper(table_.applicationName));
    boost::replace_all(str, "OBJECT", pbuilder::StringUtils::toUpper(table_.applicationName) + "DAO");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "query <----- end");
}

void TNTDBArtifactDefinitionRender::read(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "read -----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << render->parent->pbuilder->unit.ns << "::entity::"
            << pbuilder::StringUtils::toUpper(table_.applicationName)
            << " * " << pbuilder::StringUtils::toUpper(table_.applicationName) << "DAO"
            << "::read(tntdb::Connection & con, const";
    keyInMethodSignature(table_);
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << ") {" << std::endl
            << std::string(4, ' ') << "tntdb::Statement stmt = con.prepare(getReadQuery());" << std::endl
            << std::string(4, ' ')
            << render->parent->pbuilder->unit.ns << "::entity::"
            << pbuilder::StringUtils::toUpper(table_.applicationName)
            << " * e = NULL;" << std::endl
            << std::string(4, ' ') << "try {" << std::endl;
    keyInStatement(table_);
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << std::string(8, ' ')
            << "tntdb::Row row = stmt.selectRow();" << std::endl
            << std::string(8, ' ')
            << "e = new "
            << render->parent->pbuilder->unit.ns << "::entity::"
            << pbuilder::StringUtils::toUpper(table_.applicationName) << ";"
            << std::endl
            << std::string(8, ' ') << "loadColumns(row, e);" << std::endl
            << std::string(4, ' ') << "} catch(tntdb::NotFound) {" << std::endl
            << std::string(4, ' ') << "}" << std::endl
            << std::string(4, ' ') << "return e;" << std::endl
            << "}" << std::endl
            ;
    LOG4CXX_TRACE(logger, "read <----- end");
}

void TNTDBArtifactDefinitionRender::remove(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "remove -----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << "tntdb::Statement::size_type "
            << pbuilder::StringUtils::toUpper(table_.applicationName) << "DAO"
            << "::remove(tntdb::Connection & con, const";
    keyInMethodSignature(table_);
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << ") {" << std::endl
            << std::string(4, ' ') << "tntdb::Statement stmt = con.prepare(getRemoveQuery());" << std::endl;
    keyInStatement(table_);
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << std::string(4, ' ') << "return stmt.execute();" << std::endl
            << "}"
            << std::endl << std::endl;
    LOG4CXX_TRACE(logger, "remove <----- end");
}

void TNTDBArtifactDefinitionRender::update(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "update-----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << render->parent->pbuilder->unit.ns << "::entity::"
            << pbuilder::StringUtils::toUpper(table_.applicationName)
            << " * " << pbuilder::StringUtils::toUpper(table_.applicationName) << "DAO"
            << "::update(tntdb::Connection & con, "
            << render->parent->pbuilder->unit.ns << "::entity::"
            << pbuilder::StringUtils::toUpper(table_.applicationName)
            << " * e) {"
            << std::endl;
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << std::string(4, ' ') << "tntdb::Statement stmt = con.prepare(getUpdateQuery());" << std::endl
            << std::string(4, ' ') << "setColumns(stmt, e);" << std::endl;
    keyInUpdateStatement(table_);
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << std::string(4, ' ') << "stmt.execute();" << std::endl
            << std::string(4, ' ') << "return e;" << std::endl
            << "}"
            << std::endl << std::endl;
    LOG4CXX_TRACE(logger, "update <----- end");
}

void TNTDBArtifactDefinitionRender::setColumn(const pbuilder::Table & table_, const pbuilder::Column & column_) {
    LOG4CXX_TRACE(logger, "setColumn-----> begin");
    if (column_.isNullable) {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << std::string(4, ' ')
                << "if (e->isNull"
                << pbuilder::StringUtils::toUpper(column_.applicationName)
                << "()) {"
                << std::endl
                << std::string(8, ' ')
                << "stmt.setNull(\"" << column_.name << "\");"
                << std::endl
                << std::string(4, ' ') << "} else { "
                << std::endl
                << std::string(8, ' ')
                << render->stmtSet(column_, true)
                << std::endl
                << std::string(4, ' ')
                << "}"
                << std::endl;
    } else {
        render->parent->files[Render::FD_ARTIFACT_CPP]
                << std::string(4, ' ')
                << render->stmtSet(column_)
                << std::endl;
    }
    LOG4CXX_TRACE(logger, "setColumn <----- end");
}

void TNTDBArtifactDefinitionRender::setColumns(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "setColumns-----> begin");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << "void " << pbuilder::StringUtils::toUpper(table_.applicationName) << "DAO"
            << "::setColumns(tntdb::Statement & stmt, const "
            << render->parent->pbuilder->unit.ns << "::entity::"
            << pbuilder::StringUtils::toUpper(table_.applicationName)
            << " * e) {"
            << std::endl;
    for (pbuilder::Column c : table_.columns) {
        setColumn(table_, c);
    }
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << "}"
            << std::endl << std::endl;
    LOG4CXX_TRACE(logger, "setColumns <----- end");
}

void TNTDBArtifactDefinitionRender::staticDefinition(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "staticDefinition -----> begin");
    static const char * cdn = R"DELIM(        
OBJECT * OBJECT::dao = NULL;
boost::mutex OBJECT::mtx;
)DELIM";
    std::string str = cdn;
    boost::replace_all(str, "OBJECT", pbuilder::StringUtils::toUpper(table_.applicationName) + "DAO");
    render->parent->files[Render::FD_ARTIFACT_CPP]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "staticDefinition <----- end");
}