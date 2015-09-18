#ifndef EX1_DAO_H
#define EX1_DAO_H
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <tntdb/connection.h>
#include <tntdb/statement.h>
#include "ex1_entity.h"
namespace ex1 {
  namespace dao {
        
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


class CountryDAO : public CommonDAO {
private:
    static CountryDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, ex1::entity::Country *);
    void setColumns(tntdb::Statement &, const ex1::entity::Country *);
public:
    ~CountryDAO();
    static CountryDAO * getInstance(void);
    ex1::entity::Country * insert(tntdb::Connection &, ex1::entity::Country *);
    std::list<ex1::entity::Country *> query(tntdb::Connection &, tntdb::Statement &);
    ex1::entity::Country * read(tntdb::Connection &, const std::string &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const std::string &);
    ex1::entity::Country * update(tntdb::Connection &, ex1::entity::Country *);
};

class MyCompoundDAO : public CommonDAO {
private:
    static MyCompoundDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, ex1::entity::MyCompound *);
    void setColumns(tntdb::Statement &, const ex1::entity::MyCompound *);
public:
    ~MyCompoundDAO();
    static MyCompoundDAO * getInstance(void);
    ex1::entity::MyCompound * insert(tntdb::Connection &, ex1::entity::MyCompound *);
    std::list<ex1::entity::MyCompound *> query(tntdb::Connection &, tntdb::Statement &);
    ex1::entity::MyCompound * read(tntdb::Connection &, const ex1::entity::MyCompoundId &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const ex1::entity::MyCompoundId &);
    ex1::entity::MyCompound * update(tntdb::Connection &, ex1::entity::MyCompound *);
};

class MyCustomerDAO : public CommonDAO {
private:
    static MyCustomerDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, ex1::entity::MyCustomer *);
    void setColumns(tntdb::Statement &, const ex1::entity::MyCustomer *);
public:
    ~MyCustomerDAO();
    static MyCustomerDAO * getInstance(void);
    ex1::entity::MyCustomer * insert(tntdb::Connection &, ex1::entity::MyCustomer *);
    std::list<ex1::entity::MyCustomer *> query(tntdb::Connection &, tntdb::Statement &);
    ex1::entity::MyCustomer * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    ex1::entity::MyCustomer * update(tntdb::Connection &, ex1::entity::MyCustomer *);
};

class SomethingDAO : public CommonDAO {
private:
    static SomethingDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, ex1::entity::Something *);
    void setColumns(tntdb::Statement &, const ex1::entity::Something *);
public:
    ~SomethingDAO();
    static SomethingDAO * getInstance(void);
    ex1::entity::Something * insert(tntdb::Connection &, ex1::entity::Something *);
    std::list<ex1::entity::Something *> query(tntdb::Connection &, tntdb::Statement &);
    ex1::entity::Something * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    ex1::entity::Something * update(tntdb::Connection &, ex1::entity::Something *);
};
  }
}
#endif
