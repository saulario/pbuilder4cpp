#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <tntdb/error.h>
#include "ex1_dao.h"
using namespace ex1::dao;

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


CompoundDAO * CompoundDAO::dao = NULL;
boost::mutex CompoundDAO::mtx;

CompoundDAO::~CompoundDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

CompoundDAO * CompoundDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new CompoundDAO();
        dao->table = "compound";
        dao->keyColumns = "customerId,countryId";
        dao->columns = "customerId,countryId,name";
        dao->createQueries();
    }
    return dao;
}

ex1::entity::Compound * CompoundDAO::insert(tntdb::Connection & con, ex1::entity::Compound * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<ex1::entity::Compound *> CompoundDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ex1::entity::Compound *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ex1::entity::Compound * e = new ex1::entity::Compound;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

ex1::entity::Compound * CompoundDAO::read(tntdb::Connection & con, const ex1::entity::CompoundId & id) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    ex1::entity::Compound * e = NULL;
    try {
        stmt.set("customerIdPK", id.customerId);
        stmt.set("countryIdPK", id.countryId);
        tntdb::Row row = stmt.selectRow();
        e = new ex1::entity::Compound;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type CompoundDAO::remove(tntdb::Connection & con, const ex1::entity::CompoundId & id) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("customerIdPK", id.customerId);
    stmt.set("countryIdPK", id.countryId);
    return stmt.execute();
}

ex1::entity::Compound * CompoundDAO::update(tntdb::Connection & con, ex1::entity::Compound * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("customerIdPK", e->customerId);
    stmt.set("countryIdPK", e->countryId);
    stmt.execute();
    return e;
}

void CompoundDAO::loadColumns(tntdb::Row & row, ex1::entity::Compound * e) {
    int index = 0;
    e->customerId = row.getInt64(index++);
    e->countryId = row.getString(index++);
    e->name = row.getString(index++);
}

void CompoundDAO::setColumns(tntdb::Statement & stmt, const ex1::entity::Compound * e) {
    stmt.setInt64("customerId", e->customerId);
    stmt.setString("countryId", e->countryId);
    stmt.setString("name", e->name);
}


CountryDAO * CountryDAO::dao = NULL;
boost::mutex CountryDAO::mtx;

CountryDAO::~CountryDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

CountryDAO * CountryDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new CountryDAO();
        dao->table = "country";
        dao->keyColumns = "id";
        dao->columns = "id,name";
        dao->createQueries();
    }
    return dao;
}

ex1::entity::Country * CountryDAO::insert(tntdb::Connection & con, ex1::entity::Country * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<ex1::entity::Country *> CountryDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ex1::entity::Country *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ex1::entity::Country * e = new ex1::entity::Country;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

ex1::entity::Country * CountryDAO::read(tntdb::Connection & con, const std::string & id) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    ex1::entity::Country * e = NULL;
    try {
        stmt.set("idPK", id);
        tntdb::Row row = stmt.selectRow();
        e = new ex1::entity::Country;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type CountryDAO::remove(tntdb::Connection & con, const std::string & id) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("idPK", id);
    return stmt.execute();
}

ex1::entity::Country * CountryDAO::update(tntdb::Connection & con, ex1::entity::Country * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("idPK", e->id);
    stmt.execute();
    return e;
}

void CountryDAO::loadColumns(tntdb::Row & row, ex1::entity::Country * e) {
    int index = 0;
    e->id = row.getString(index++);
    e->name = row.getString(index++);
}

void CountryDAO::setColumns(tntdb::Statement & stmt, const ex1::entity::Country * e) {
    stmt.setString("id", e->id);
    stmt.setString("name", e->name);
}


CustomerDAO * CustomerDAO::dao = NULL;
boost::mutex CustomerDAO::mtx;

CustomerDAO::~CustomerDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

CustomerDAO * CustomerDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new CustomerDAO();
        dao->table = "customer";
        dao->keyColumns = "id";
        dao->columns = "id,name,countryId,creationDate";
        dao->createQueries();
    }
    return dao;
}

ex1::entity::Customer * CustomerDAO::insert(tntdb::Connection & con, ex1::entity::Customer * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<ex1::entity::Customer *> CustomerDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ex1::entity::Customer *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ex1::entity::Customer * e = new ex1::entity::Customer;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

ex1::entity::Customer * CustomerDAO::read(tntdb::Connection & con, const long & id) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    ex1::entity::Customer * e = NULL;
    try {
        stmt.set("idPK", id);
        tntdb::Row row = stmt.selectRow();
        e = new ex1::entity::Customer;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type CustomerDAO::remove(tntdb::Connection & con, const long & id) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("idPK", id);
    return stmt.execute();
}

ex1::entity::Customer * CustomerDAO::update(tntdb::Connection & con, ex1::entity::Customer * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("idPK", e->id);
    stmt.execute();
    return e;
}

void CustomerDAO::loadColumns(tntdb::Row & row, ex1::entity::Customer * e) {
    int index = 0;
    e->id = row.getInt64(index++);
    e->name = row.getString(index++);
    try {
        e->setCountryId(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullCountryId();
    }
    e->creationDate = row.getDate(index++);
}

void CustomerDAO::setColumns(tntdb::Statement & stmt, const ex1::entity::Customer * e) {
    stmt.setInt64("id", e->id);
    stmt.setString("name", e->name);
    if (e->isNullCountryId()) {
        stmt.setNull("countryId");
    } else {
        stmt.setString("countryId", e->getCountryId());
    }
    stmt.setDate("creationDate", e->creationDate);
}


SomethingDAO * SomethingDAO::dao = NULL;
boost::mutex SomethingDAO::mtx;

SomethingDAO::~SomethingDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

SomethingDAO * SomethingDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new SomethingDAO();
        dao->table = "something";
        dao->keyColumns = "id";
        dao->columns = "id,name,customerId,countryId";
        dao->createQueries();
    }
    return dao;
}

ex1::entity::Something * SomethingDAO::insert(tntdb::Connection & con, ex1::entity::Something * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<ex1::entity::Something *> SomethingDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ex1::entity::Something *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ex1::entity::Something * e = new ex1::entity::Something;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

ex1::entity::Something * SomethingDAO::read(tntdb::Connection & con, const long & id) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    ex1::entity::Something * e = NULL;
    try {
        stmt.set("idPK", id);
        tntdb::Row row = stmt.selectRow();
        e = new ex1::entity::Something;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type SomethingDAO::remove(tntdb::Connection & con, const long & id) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("idPK", id);
    return stmt.execute();
}

ex1::entity::Something * SomethingDAO::update(tntdb::Connection & con, ex1::entity::Something * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("idPK", e->id);
    stmt.execute();
    return e;
}

void SomethingDAO::loadColumns(tntdb::Row & row, ex1::entity::Something * e) {
    int index = 0;
    e->id = row.getInt64(index++);
    e->name = row.getString(index++);
    e->customerId = row.getInt64(index++);
    e->countryId = row.getString(index++);
}

void SomethingDAO::setColumns(tntdb::Statement & stmt, const ex1::entity::Something * e) {
    stmt.setInt64("id", e->id);
    stmt.setString("name", e->name);
    stmt.setInt64("customerId", e->customerId);
    stmt.setString("countryId", e->countryId);
}

