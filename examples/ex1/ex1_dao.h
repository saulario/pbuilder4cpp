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

        class Test1DAO : public CommonDAO {
        private:
            static Test1DAO * dao;
            static boost::mutex mtx;
            void loadColumns(tntdb::Row &, ex1::entity::Test1 *);
            void setColumns(tntdb::Statement &, const ex1::entity::Test1 *);
        public:
            ~Test1DAO();
            static Test1DAO * getInstance(void);
            ex1::entity::Test1 * insert(tntdb::Connection &, ex1::entity::Test1 *);
            std::list<ex1::entity::Test1 *> query(tntdb::Connection &, tntdb::Statement &);
            ex1::entity::Test1 * read(tntdb::Connection &, const int &);
            tntdb::Statement::size_type remove(tntdb::Connection &, const int &);
            ex1::entity::Test1 * update(tntdb::Connection &, ex1::entity::Test1 *);
        };

        class Test2DAO : public CommonDAO {
        private:
            static Test2DAO * dao;
            static boost::mutex mtx;
            void loadColumns(tntdb::Row &, ex1::entity::Test2 *);
            void setColumns(tntdb::Statement &, const ex1::entity::Test2 *);
        public:
            ~Test2DAO();
            static Test2DAO * getInstance(void);
            ex1::entity::Test2 * insert(tntdb::Connection &, ex1::entity::Test2 *);
            std::list<ex1::entity::Test2 *> query(tntdb::Connection &, tntdb::Statement &);
            ex1::entity::Test2 * read(tntdb::Connection &, const ex1::entity::Test2Id &);
            tntdb::Statement::size_type remove(tntdb::Connection &, const ex1::entity::Test2Id &);
            ex1::entity::Test2 * update(tntdb::Connection &, ex1::entity::Test2 *);
        };

        class Test3DAO : public CommonDAO {
        private:
            static Test3DAO * dao;
            static boost::mutex mtx;
            void loadColumns(tntdb::Row &, ex1::entity::Test3 *);
            void setColumns(tntdb::Statement &, const ex1::entity::Test3 *);
        public:
            ~Test3DAO();
            static Test3DAO * getInstance(void);
            ex1::entity::Test3 * insert(tntdb::Connection &, ex1::entity::Test3 *);
            std::list<ex1::entity::Test3 *> query(tntdb::Connection &, tntdb::Statement &);
        };
    }
}
#endif
