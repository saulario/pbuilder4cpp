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


Test1DAO * Test1DAO::dao = NULL;
boost::mutex Test1DAO::mtx;

Test1DAO::~Test1DAO() {
    if (dao != NULL) {
        delete dao;
    }
}

Test1DAO * Test1DAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new Test1DAO();
        dao->table = "test1";
        dao->keyColumns = "tkey";
        dao->columns = "tkey,tsmallint,tsmallintUnsigned,tmediumint"
                ",tmediumintUnsigned,tinteger,tintegerUnsigned,tbigint,tbigintUnsigned"
                ",tdecimal,tdecimalUnsigned,tdec,tdecUnsigned,tfixed"
                ",tfixedUnsigned,tfloat,tfloatUnsigned,tdouble,tdoubleUnsigned"
                ",tdate,tdatetime,ttimestamp,ttime,tchar"
                ",tvarchar,ttext,tblob";
        dao->createQueries();
    }
    return dao;
}

ex1::entity::Test1 * Test1DAO::insert(tntdb::Connection & con, ex1::entity::Test1 * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<ex1::entity::Test1 *> Test1DAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ex1::entity::Test1 *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ex1::entity::Test1 * e = new ex1::entity::Test1;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

ex1::entity::Test1 * Test1DAO::read(tntdb::Connection & con, const int & tkey) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    ex1::entity::Test1 * e = NULL;
    try {
        stmt.set("tkeyPK", tkey);
        tntdb::Row row = stmt.selectRow();
        e = new ex1::entity::Test1;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type Test1DAO::remove(tntdb::Connection & con, const int & tkey) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("tkeyPK", tkey);
    return stmt.execute();
}

ex1::entity::Test1 * Test1DAO::update(tntdb::Connection & con, ex1::entity::Test1 * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("tkeyPK", e->tkey);
    stmt.execute();
    return e;
}

void Test1DAO::loadColumns(tntdb::Row & row, ex1::entity::Test1 * e) {
    int index = 0;
    e->tkey = row.getInt(index++);
    e->tsmallint = row.getInt(index++);
    e->tsmallintUnsigned = row.getUnsigned(index++);
    e->tmediumint = row.getInt(index++);
    e->tmediumintUnsigned = row.getUnsigned(index++);
    e->tinteger = row.getInt(index++);
    e->tintegerUnsigned = row.getUnsigned(index++);
    e->tbigint = row.getInt64(index++);
    e->tbigintUnsigned = row.getUnsigned64(index++);
    e->tdecimal = row.getDecimal(index++).getDouble();
    e->tdecimalUnsigned = row.getDecimal(index++).getDouble();
    e->tdec = row.getDecimal(index++).getDouble();
    e->tdecUnsigned = row.getDecimal(index++).getDouble();
    e->tfixed = row.getDecimal(index++).getDouble();
    e->tfixedUnsigned = row.getDecimal(index++).getDouble();
    e->tfloat = row.getDecimal(index++).getDouble();
    e->tfloatUnsigned = row.getDecimal(index++).getDouble();
    e->tdouble = row.getDecimal(index++).getDouble();
    e->tdoubleUnsigned = row.getDecimal(index++).getDouble();
    e->tdate = row.getDate(index++);
    e->tdatetime = row.getDatetime(index++);
    e->ttimestamp = row.getDatetime(index++);
    e->ttime = row.getTime(index++);
    e->tchar = row.getString(index++);
    e->tvarchar = row.getString(index++);
    try {
        e->setTtext(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTtext();
    }
    try {
        e->setTblob(row.getBlob(index++));
    } catch (tntdb::NullValue) {
        e->setNullTblob();
    }
}

void Test1DAO::setColumns(tntdb::Statement & stmt, const ex1::entity::Test1 * e) {
    stmt.setInt("tkey", e->tkey);
    stmt.setInt("tsmallint", e->tsmallint);
    stmt.setUnsigned("tsmallintUnsigned", e->tsmallintUnsigned);
    stmt.setInt("tmediumint", e->tmediumint);
    stmt.setUnsigned("tmediumintUnsigned", e->tmediumintUnsigned);
    stmt.setInt("tinteger", e->tinteger);
    stmt.setUnsigned("tintegerUnsigned", e->tintegerUnsigned);
    stmt.setInt64("tbigint", e->tbigint);
    stmt.setUnsigned64("tbigintUnsigned", e->tbigintUnsigned);
    stmt.setDouble("tdecimal", e->tdecimal);
    stmt.setDouble("tdecimalUnsigned", e->tdecimalUnsigned);
    stmt.setDouble("tdec", e->tdec);
    stmt.setDouble("tdecUnsigned", e->tdecUnsigned);
    stmt.setDouble("tfixed", e->tfixed);
    stmt.setDouble("tfixedUnsigned", e->tfixedUnsigned);
    stmt.setDouble("tfloat", e->tfloat);
    stmt.setDouble("tfloatUnsigned", e->tfloatUnsigned);
    stmt.setDouble("tdouble", e->tdouble);
    stmt.setDouble("tdoubleUnsigned", e->tdoubleUnsigned);
    stmt.setDate("tdate", e->tdate);
    stmt.set("tdatetime", e->tdatetime.getIso());
    stmt.set("ttimestamp", e->ttimestamp.getIso());
    stmt.setTime("ttime", e->ttime);
    stmt.setString("tchar", e->tchar);
    stmt.setString("tvarchar", e->tvarchar);
    if (e->isNullTtext()) {
        stmt.setNull("ttext");
    } else {
        stmt.setString("ttext", e->getTtext());
    }
    if (e->isNullTblob()) {
        stmt.setNull("tblob");
    } else {
        stmt.setBlob("tblob", e->getTblob());
    }
}


Test2DAO * Test2DAO::dao = NULL;
boost::mutex Test2DAO::mtx;

Test2DAO::~Test2DAO() {
    if (dao != NULL) {
        delete dao;
    }
}

Test2DAO * Test2DAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new Test2DAO();
        dao->table = "test2";
        dao->keyColumns = "tkey1,tkey2";
        dao->columns = "tkey1,tkey2,tsmallint,tsmallintUnsigned"
                ",tmediumint,tmediumintUnsigned,tinteger,tintegerUnsigned,tbigint"
                ",tbigintUnsigned,tdecimal,tdecimalUnsigned,tdec,tdecUnsigned"
                ",tfixed,tfixedUnsigned,tfloat,tfloatUnsigned,tdouble"
                ",tdoubleUnsigned,tdate,tdatetime,ttimestamp,ttime"
                ",tchar,tvarchar,ttext,tblob";
        dao->createQueries();
    }
    return dao;
}

ex1::entity::Test2 * Test2DAO::insert(tntdb::Connection & con, ex1::entity::Test2 * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<ex1::entity::Test2 *> Test2DAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ex1::entity::Test2 *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ex1::entity::Test2 * e = new ex1::entity::Test2;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

ex1::entity::Test2 * Test2DAO::read(tntdb::Connection & con, const ex1::entity::Test2Id & id) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    ex1::entity::Test2 * e = NULL;
    try {
        stmt.set("tkey1PK", id.tkey1);
        stmt.set("tkey2PK", id.tkey2);
        tntdb::Row row = stmt.selectRow();
        e = new ex1::entity::Test2;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type Test2DAO::remove(tntdb::Connection & con, const ex1::entity::Test2Id & id) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("tkey1PK", id.tkey1);
    stmt.set("tkey2PK", id.tkey2);
    return stmt.execute();
}

ex1::entity::Test2 * Test2DAO::update(tntdb::Connection & con, ex1::entity::Test2 * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("tkey1PK", e->tkey1);
    stmt.set("tkey2PK", e->tkey2);
    stmt.execute();
    return e;
}

void Test2DAO::loadColumns(tntdb::Row & row, ex1::entity::Test2 * e) {
    int index = 0;
    e->tkey1 = row.getInt(index++);
    e->tkey2 = row.getInt(index++);
    try {
        e->setTsmallint(row.getInt(index++));
    } catch (tntdb::NullValue) {
        e->setNullTsmallint();
    }
    try {
        e->setTsmallintUnsigned(row.getUnsigned(index++));
    } catch (tntdb::NullValue) {
        e->setNullTsmallintUnsigned();
    }
    try {
        e->setTmediumint(row.getInt(index++));
    } catch (tntdb::NullValue) {
        e->setNullTmediumint();
    }
    try {
        e->setTmediumintUnsigned(row.getUnsigned(index++));
    } catch (tntdb::NullValue) {
        e->setNullTmediumintUnsigned();
    }
    try {
        e->setTinteger(row.getInt(index++));
    } catch (tntdb::NullValue) {
        e->setNullTinteger();
    }
    try {
        e->setTintegerUnsigned(row.getUnsigned(index++));
    } catch (tntdb::NullValue) {
        e->setNullTintegerUnsigned();
    }
    try {
        e->setTbigint(row.getInt64(index++));
    } catch (tntdb::NullValue) {
        e->setNullTbigint();
    }
    try {
        e->setTbigintUnsigned(row.getUnsigned64(index++));
    } catch (tntdb::NullValue) {
        e->setNullTbigintUnsigned();
    }
    try {
        e->setTdecimal(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdecimal();
    }
    try {
        e->setTdecimalUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdecimalUnsigned();
    }
    try {
        e->setTdec(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdec();
    }
    try {
        e->setTdecUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdecUnsigned();
    }
    try {
        e->setTfixed(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfixed();
    }
    try {
        e->setTfixedUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfixedUnsigned();
    }
    try {
        e->setTfloat(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfloat();
    }
    try {
        e->setTfloatUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfloatUnsigned();
    }
    try {
        e->setTdouble(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdouble();
    }
    try {
        e->setTdoubleUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdoubleUnsigned();
    }
    try {
        e->setTdate(row.getDate(index++));
    } catch (tntdb::NullValue) {
        e->setNullTdate();
    }
    try {
        e->setTdatetime(row.getDatetime(index++));
    } catch (tntdb::NullValue) {
        e->setNullTdatetime();
    }
    e->ttimestamp = row.getDatetime(index++);
    try {
        e->setTtime(row.getTime(index++));
    } catch (tntdb::NullValue) {
        e->setNullTtime();
    }
    try {
        e->setTchar(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTchar();
    }
    try {
        e->setTvarchar(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTvarchar();
    }
    try {
        e->setTtext(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTtext();
    }
    try {
        e->setTblob(row.getBlob(index++));
    } catch (tntdb::NullValue) {
        e->setNullTblob();
    }
}

void Test2DAO::setColumns(tntdb::Statement & stmt, const ex1::entity::Test2 * e) {
    stmt.setInt("tkey1", e->tkey1);
    stmt.setInt("tkey2", e->tkey2);
    if (e->isNullTsmallint()) {
        stmt.setNull("tsmallint");
    } else {
        stmt.setInt("tsmallint", e->getTsmallint());
    }
    if (e->isNullTsmallintUnsigned()) {
        stmt.setNull("tsmallintUnsigned");
    } else {
        stmt.setUnsigned("tsmallintUnsigned", e->getTsmallintUnsigned());
    }
    if (e->isNullTmediumint()) {
        stmt.setNull("tmediumint");
    } else {
        stmt.setInt("tmediumint", e->getTmediumint());
    }
    if (e->isNullTmediumintUnsigned()) {
        stmt.setNull("tmediumintUnsigned");
    } else {
        stmt.setUnsigned("tmediumintUnsigned", e->getTmediumintUnsigned());
    }
    if (e->isNullTinteger()) {
        stmt.setNull("tinteger");
    } else {
        stmt.setInt("tinteger", e->getTinteger());
    }
    if (e->isNullTintegerUnsigned()) {
        stmt.setNull("tintegerUnsigned");
    } else {
        stmt.setUnsigned("tintegerUnsigned", e->getTintegerUnsigned());
    }
    if (e->isNullTbigint()) {
        stmt.setNull("tbigint");
    } else {
        stmt.setInt64("tbigint", e->getTbigint());
    }
    if (e->isNullTbigintUnsigned()) {
        stmt.setNull("tbigintUnsigned");
    } else {
        stmt.setUnsigned64("tbigintUnsigned", e->getTbigintUnsigned());
    }
    if (e->isNullTdecimal()) {
        stmt.setNull("tdecimal");
    } else {
        stmt.setDouble("tdecimal", e->getTdecimal());
    }
    if (e->isNullTdecimalUnsigned()) {
        stmt.setNull("tdecimalUnsigned");
    } else {
        stmt.setDouble("tdecimalUnsigned", e->getTdecimalUnsigned());
    }
    if (e->isNullTdec()) {
        stmt.setNull("tdec");
    } else {
        stmt.setDouble("tdec", e->getTdec());
    }
    if (e->isNullTdecUnsigned()) {
        stmt.setNull("tdecUnsigned");
    } else {
        stmt.setDouble("tdecUnsigned", e->getTdecUnsigned());
    }
    if (e->isNullTfixed()) {
        stmt.setNull("tfixed");
    } else {
        stmt.setDouble("tfixed", e->getTfixed());
    }
    if (e->isNullTfixedUnsigned()) {
        stmt.setNull("tfixedUnsigned");
    } else {
        stmt.setDouble("tfixedUnsigned", e->getTfixedUnsigned());
    }
    if (e->isNullTfloat()) {
        stmt.setNull("tfloat");
    } else {
        stmt.setDouble("tfloat", e->getTfloat());
    }
    if (e->isNullTfloatUnsigned()) {
        stmt.setNull("tfloatUnsigned");
    } else {
        stmt.setDouble("tfloatUnsigned", e->getTfloatUnsigned());
    }
    if (e->isNullTdouble()) {
        stmt.setNull("tdouble");
    } else {
        stmt.setDouble("tdouble", e->getTdouble());
    }
    if (e->isNullTdoubleUnsigned()) {
        stmt.setNull("tdoubleUnsigned");
    } else {
        stmt.setDouble("tdoubleUnsigned", e->getTdoubleUnsigned());
    }
    if (e->isNullTdate()) {
        stmt.setNull("tdate");
    } else {
        stmt.setDate("tdate", e->getTdate());
    }
    if (e->isNullTdatetime()) {
        stmt.setNull("tdatetime");
    } else {
        stmt.set("tdatetime", e->getTdatetime());
    }
    stmt.set("ttimestamp", e->ttimestamp.getIso());
    if (e->isNullTtime()) {
        stmt.setNull("ttime");
    } else {
        stmt.setTime("ttime", e->getTtime());
    }
    if (e->isNullTchar()) {
        stmt.setNull("tchar");
    } else {
        stmt.setString("tchar", e->getTchar());
    }
    if (e->isNullTvarchar()) {
        stmt.setNull("tvarchar");
    } else {
        stmt.setString("tvarchar", e->getTvarchar());
    }
    if (e->isNullTtext()) {
        stmt.setNull("ttext");
    } else {
        stmt.setString("ttext", e->getTtext());
    }
    if (e->isNullTblob()) {
        stmt.setNull("tblob");
    } else {
        stmt.setBlob("tblob", e->getTblob());
    }
}


Test3DAO * Test3DAO::dao = NULL;
boost::mutex Test3DAO::mtx;

Test3DAO::~Test3DAO() {
    if (dao != NULL) {
        delete dao;
    }
}

Test3DAO * Test3DAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new Test3DAO();
        dao->table = "test3";
        dao->keyColumns = "";
        dao->columns = "tkey1,tkey2,tsmallint,tsmallintUnsigned"
                ",tmediumint,tmediumintUnsigned,tinteger,tintegerUnsigned,tbigint"
                ",tbigintUnsigned,tdecimal,tdecimalUnsigned,tdec,tdecUnsigned"
                ",tfixed,tfixedUnsigned,tfloat,tfloatUnsigned,tdouble"
                ",tdoubleUnsigned,tdate,tdatetime,ttimestamp,ttime"
                ",tchar,tvarchar,ttext,tblob";
        dao->createQueries();
    }
    return dao;
}

ex1::entity::Test3 * Test3DAO::insert(tntdb::Connection & con, ex1::entity::Test3 * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<ex1::entity::Test3 *> Test3DAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<ex1::entity::Test3 *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        ex1::entity::Test3 * e = new ex1::entity::Test3;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

void Test3DAO::loadColumns(tntdb::Row & row, ex1::entity::Test3 * e) {
    int index = 0;
    e->tkey1 = row.getInt(index++);
    e->tkey2 = row.getInt(index++);
    try {
        e->setTsmallint(row.getInt(index++));
    } catch (tntdb::NullValue) {
        e->setNullTsmallint();
    }
    try {
        e->setTsmallintUnsigned(row.getUnsigned(index++));
    } catch (tntdb::NullValue) {
        e->setNullTsmallintUnsigned();
    }
    try {
        e->setTmediumint(row.getInt(index++));
    } catch (tntdb::NullValue) {
        e->setNullTmediumint();
    }
    try {
        e->setTmediumintUnsigned(row.getUnsigned(index++));
    } catch (tntdb::NullValue) {
        e->setNullTmediumintUnsigned();
    }
    try {
        e->setTinteger(row.getInt(index++));
    } catch (tntdb::NullValue) {
        e->setNullTinteger();
    }
    try {
        e->setTintegerUnsigned(row.getUnsigned(index++));
    } catch (tntdb::NullValue) {
        e->setNullTintegerUnsigned();
    }
    try {
        e->setTbigint(row.getInt64(index++));
    } catch (tntdb::NullValue) {
        e->setNullTbigint();
    }
    try {
        e->setTbigintUnsigned(row.getUnsigned64(index++));
    } catch (tntdb::NullValue) {
        e->setNullTbigintUnsigned();
    }
    try {
        e->setTdecimal(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdecimal();
    }
    try {
        e->setTdecimalUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdecimalUnsigned();
    }
    try {
        e->setTdec(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdec();
    }
    try {
        e->setTdecUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdecUnsigned();
    }
    try {
        e->setTfixed(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfixed();
    }
    try {
        e->setTfixedUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfixedUnsigned();
    }
    try {
        e->setTfloat(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfloat();
    }
    try {
        e->setTfloatUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTfloatUnsigned();
    }
    try {
        e->setTdouble(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdouble();
    }
    try {
        e->setTdoubleUnsigned(row.getDecimal(index++).getDouble());
    } catch (tntdb::NullValue) {
        e->setNullTdoubleUnsigned();
    }
    try {
        e->setTdate(row.getDate(index++));
    } catch (tntdb::NullValue) {
        e->setNullTdate();
    }
    try {
        e->setTdatetime(row.getDatetime(index++));
    } catch (tntdb::NullValue) {
        e->setNullTdatetime();
    }
    e->ttimestamp = row.getDatetime(index++);
    try {
        e->setTtime(row.getTime(index++));
    } catch (tntdb::NullValue) {
        e->setNullTtime();
    }
    try {
        e->setTchar(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTchar();
    }
    try {
        e->setTvarchar(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTvarchar();
    }
    try {
        e->setTtext(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTtext();
    }
    try {
        e->setTblob(row.getBlob(index++));
    } catch (tntdb::NullValue) {
        e->setNullTblob();
    }
}

void Test3DAO::setColumns(tntdb::Statement & stmt, const ex1::entity::Test3 * e) {
    stmt.setInt("tkey1", e->tkey1);
    stmt.setInt("tkey2", e->tkey2);
    if (e->isNullTsmallint()) {
        stmt.setNull("tsmallint");
    } else {
        stmt.setInt("tsmallint", e->getTsmallint());
    }
    if (e->isNullTsmallintUnsigned()) {
        stmt.setNull("tsmallintUnsigned");
    } else {
        stmt.setUnsigned("tsmallintUnsigned", e->getTsmallintUnsigned());
    }
    if (e->isNullTmediumint()) {
        stmt.setNull("tmediumint");
    } else {
        stmt.setInt("tmediumint", e->getTmediumint());
    }
    if (e->isNullTmediumintUnsigned()) {
        stmt.setNull("tmediumintUnsigned");
    } else {
        stmt.setUnsigned("tmediumintUnsigned", e->getTmediumintUnsigned());
    }
    if (e->isNullTinteger()) {
        stmt.setNull("tinteger");
    } else {
        stmt.setInt("tinteger", e->getTinteger());
    }
    if (e->isNullTintegerUnsigned()) {
        stmt.setNull("tintegerUnsigned");
    } else {
        stmt.setUnsigned("tintegerUnsigned", e->getTintegerUnsigned());
    }
    if (e->isNullTbigint()) {
        stmt.setNull("tbigint");
    } else {
        stmt.setInt64("tbigint", e->getTbigint());
    }
    if (e->isNullTbigintUnsigned()) {
        stmt.setNull("tbigintUnsigned");
    } else {
        stmt.setUnsigned64("tbigintUnsigned", e->getTbigintUnsigned());
    }
    if (e->isNullTdecimal()) {
        stmt.setNull("tdecimal");
    } else {
        stmt.setDouble("tdecimal", e->getTdecimal());
    }
    if (e->isNullTdecimalUnsigned()) {
        stmt.setNull("tdecimalUnsigned");
    } else {
        stmt.setDouble("tdecimalUnsigned", e->getTdecimalUnsigned());
    }
    if (e->isNullTdec()) {
        stmt.setNull("tdec");
    } else {
        stmt.setDouble("tdec", e->getTdec());
    }
    if (e->isNullTdecUnsigned()) {
        stmt.setNull("tdecUnsigned");
    } else {
        stmt.setDouble("tdecUnsigned", e->getTdecUnsigned());
    }
    if (e->isNullTfixed()) {
        stmt.setNull("tfixed");
    } else {
        stmt.setDouble("tfixed", e->getTfixed());
    }
    if (e->isNullTfixedUnsigned()) {
        stmt.setNull("tfixedUnsigned");
    } else {
        stmt.setDouble("tfixedUnsigned", e->getTfixedUnsigned());
    }
    if (e->isNullTfloat()) {
        stmt.setNull("tfloat");
    } else {
        stmt.setDouble("tfloat", e->getTfloat());
    }
    if (e->isNullTfloatUnsigned()) {
        stmt.setNull("tfloatUnsigned");
    } else {
        stmt.setDouble("tfloatUnsigned", e->getTfloatUnsigned());
    }
    if (e->isNullTdouble()) {
        stmt.setNull("tdouble");
    } else {
        stmt.setDouble("tdouble", e->getTdouble());
    }
    if (e->isNullTdoubleUnsigned()) {
        stmt.setNull("tdoubleUnsigned");
    } else {
        stmt.setDouble("tdoubleUnsigned", e->getTdoubleUnsigned());
    }
    if (e->isNullTdate()) {
        stmt.setNull("tdate");
    } else {
        stmt.setDate("tdate", e->getTdate());
    }
    if (e->isNullTdatetime()) {
        stmt.setNull("tdatetime");
    } else {
        stmt.set("tdatetime", e->getTdatetime());
    }
    stmt.set("ttimestamp", e->ttimestamp.getIso());
    if (e->isNullTtime()) {
        stmt.setNull("ttime");
    } else {
        stmt.setTime("ttime", e->getTtime());
    }
    if (e->isNullTchar()) {
        stmt.setNull("tchar");
    } else {
        stmt.setString("tchar", e->getTchar());
    }
    if (e->isNullTvarchar()) {
        stmt.setNull("tvarchar");
    } else {
        stmt.setString("tvarchar", e->getTvarchar());
    }
    if (e->isNullTtext()) {
        stmt.setNull("ttext");
    } else {
        stmt.setString("ttext", e->getTtext());
    }
    if (e->isNullTblob()) {
        stmt.setNull("tblob");
    } else {
        stmt.setBlob("tblob", e->getTblob());
    }
}

