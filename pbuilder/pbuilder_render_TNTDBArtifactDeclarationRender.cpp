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
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include "pbuilder.h"
#include "pbuilder_render.h"

using namespace pbuilder::render;

log4cxx::LoggerPtr TNTDBArtifactDeclarationRender::logger =
        log4cxx::Logger::getLogger("pbuilder::render::TNTDBArtifactDeclarationRender");

TNTDBArtifactDeclarationRender::TNTDBArtifactDeclarationRender(TNTDBRender * render_) : render(render_) {
    LOG4CXX_TRACE(logger, "TNTDBArtifactDeclarationRender -----> begin");
    render->parent->files[Render::FD_ARTIFACT_H]
            << "#ifndef " << boost::algorithm::to_upper_copy(render_->parent->pbuilder->unit.ns) << "_DAO_H" << std::endl
            << "#define " << boost::algorithm::to_upper_copy(render_->parent->pbuilder->unit.ns) << "_DAO_H" << std::endl
            << "#include <boost/thread/mutex.hpp>" << std::endl
            << "#include <boost/thread/thread.hpp>" << std::endl
            << "#include <tntdb/connection.h>" << std::endl
            << "#include <tntdb/statement.h>" << std::endl
            << "#include \"" << render_->parent->pbuilder->unit.ns << "_entity.h\"" << std::endl
            << "namespace " << render->parent->pbuilder->unit.ns << " {" << std::endl
            << std::string(2, ' ') << "namespace dao {" << std::endl;
    static const char * common = R"(        
class CommonDAO {
private:
    std::string insertQuery;
    std::string readQuery;
    std::string removeQuery;
    std::string updateQuery;
protected:
    std::string table;
    std::string keyColumns;
    std::string columns;
    void createQueries(void);
public:
    std::string getInsertQuery(void);
    std::string getReadQuery(void);
    std::string getRemoveQuery(void);
    std::string getUpdateQuery(void);
    std::string getColumns(void);
    std::string getTable(void);
};    
)";
    render->parent->files[Render::FD_ARTIFACT_H]
            << common
            << std::endl;
    LOG4CXX_TRACE(logger, "TNTDBArtifactDeclarationRender <----- end");
}

TNTDBArtifactDeclarationRender::~TNTDBArtifactDeclarationRender() {
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDeclarationRender -----> begin");
    render->parent->files[Render::FD_ARTIFACT_H]
            << std::string(2, ' ') << "}" << std::endl
            << "}" << std::endl
            << "#endif" << std::endl;
    LOG4CXX_TRACE(logger, "~TNTDBArtifactDeclarationRender <----- end");
}

void TNTDBArtifactDeclarationRender::notify(void) {
    LOG4CXX_TRACE(logger, "notify -----> begin");
    for (std::pair<std::string, pbuilder::Table> p : render->parent->pbuilder->model.tables) {
        table(p.second);
    }
    LOG4CXX_TRACE(logger, "notify <----- end");
}

void TNTDBArtifactDeclarationRender::table(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "table -----> begin");

    static const char * cdn = R"(
class TABLEDAO : public CommonDAO {
private:
    static TABLEDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, NAMESPACE::TABLE *);
    void setColumns(tntdb::Statement &, const NAMESPACE::TABLE *);
public:
    TABLEDAO();
    ~TABLEDAO();
    static TABLEDAO * getInstance(void);
    NAMESPACE::TABLE * insert(tntdb::Connection &, NAMESPACE::TABLE *);
    std::list<NAMESPACE::TABLE *> query(tntdb::Connection &, tntdb::Statement &);)";
    std::string str = cdn;
    boost::replace_all(str, "TABLE", pbuilder::render::Render::toUpper(table_.name));
    boost::replace_all(str, "NAMESPACE", render->parent->pbuilder->unit.ns + "::entity");
    render->parent->files[Render::FD_ARTIFACT_H]
            << str
            << std::endl;

    if (table_.pkColumns.size() > 0) {
        tableExtended(table_);
    }

    render->parent->files[Render::FD_ARTIFACT_H]
            << "};"
            << std::endl;

    LOG4CXX_TRACE(logger, "table <----- end");
}

void TNTDBArtifactDeclarationRender::tableExtended(const pbuilder::Table & table_) {
    LOG4CXX_TRACE(logger, "tableExtended -----> begin");

    static const char * cdn = R"(    NAMESPACE::TABLE * read(tntdb::Connection &, const KEYTYPE &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const KEYTYPE &);
    NAMESPACE::TABLE * update(tntdb::Connection &, NAMESPACE::TABLE *);)";
    std::string str = cdn;
    boost::replace_all(str, "TABLE", pbuilder::render::Render::toUpper(table_.name));
    boost::replace_all(str, "NAMESPACE", render->parent->pbuilder->unit.ns + "::entity");
    std::string keytype = "UNDEFINED";
    if (table_.pkColumns.size() > 1) {
        keytype = render->parent->pbuilder->unit.ns + "::entity::" + render->parent->toUpper(table_.name) + "Id";
    } else if (table_.pkColumns.size() == 1) {
        keytype = render->asText(table_.pkColumns.front());
    }
    boost::replace_all(str, "KEYTYPE", keytype);

    render->parent->files[Render::FD_ARTIFACT_H]
            << str
            << std::endl;
    LOG4CXX_TRACE(logger, "tableExtended <----- end");
}