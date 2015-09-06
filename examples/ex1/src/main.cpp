#include <cstdlib>
#include <list>
#include <string>
#include <tntdb/connect.h>
#include <tntdb/connection.h>
#include <tntdb/transaction.h>
#include <boost/lexical_cast.hpp>

#include "ex1_dao.h"
#include "ex1_entity.h"

int main(int, char **);

/*
 * type definition example. Future versions will contain these defintions
 */
void typeDefinition(tntdb::Connection & con) {

    typedef std::pair<std::string, ex1::entity::Country *> CountryPair;
    typedef std::map<std::string, ex1::entity::Country *> CountryMap;
    typedef std::list<ex1::entity::Country *> CountryList;

    std::string cdn = "select " + ex1::dao::CountryDAO::getInstance()->getColumns()
            + " from country where "
            + " name like :name";
    tntdb::Statement stmt = con.prepare(cdn)
            .setString("name", "U%");

    CountryMap map;
    CountryList countries = ex1::dao::CountryDAO::getInstance()->query(con, stmt);
    for (auto country : countries) {
        std::cerr << country->name << std::endl;
        map.insert(CountryPair(country->id, country));
    }

    for (auto pair : map) {
        std::cerr << pair.second->name << std::endl;
    }

    for (auto country : countries) {
        delete country;
    }

}

/*
 * 
 */
void workingWithRows(tntdb::Connection & con) {

    con.beginTransaction();
    con.prepare("delete from compound").execute();
    con.prepare("delete from something").execute();
    con.prepare("delete from customer").execute();
    con.commitTransaction();

    con.beginTransaction();
    unsigned long somethingId = 0;
    for (unsigned int i = 1; i < 1000; i++) {
        ex1::entity::Customer * customer = new ex1::entity::Customer();
        customer->id = i;
        customer->name = "Customer #" + boost::lexical_cast<std::string, unsigned int>(i);
        customer->creation_date = tntdb::Date::localtime();
        if ((i % 3) == 0) {
            customer->setCountry_id("ES");
        } else if ((i % 7) == 0) {
            customer->setCountry_id("UK");
        }
        ex1::dao::CustomerDAO::getInstance()->insert(con, customer);
        if ((i % 3) == 0) {
            for (int j = 0; j <= 10; j++) {
                ex1::entity::Something * something = new ex1::entity::Something();
                something->id = ++somethingId;
                something->customer_id = customer->id;
                something->name = "Something #" + boost::lexical_cast<std::string, unsigned int>(somethingId);
                something->country_id = customer->getCountry_id();
                ex1::dao::SomethingDAO::getInstance()->insert(con, something);
                delete something;
            }
        }
        delete customer;
    }
    ex1::entity::Compound * c1 = new ex1::entity::Compound();
    c1->customer_id = 1;
    c1->country_id = "FR";
    c1->name = "Something in french";
    ex1::dao::CompoundDAO::getInstance()->insert(con, c1);
    ex1::entity::CompoundId compoundId;
    compoundId.customer_id = 1;
    compoundId.country_id = "FR";
    ex1::entity::Compound * c2 = ex1::dao::CompoundDAO::getInstance()->read(con, compoundId);
    if (*c1 == *c2) {
        std::cerr << "It's all right" << std::endl;
    } else {
        std::cerr << "Uh, uh!" << std::endl;
    }
    delete c1, c2;
    
    con.commitTransaction();

}

void mysql(void) {
    tntdb::Connection con = tntdb::connect("mysql:db=ex1;user=ex1user;password=passwd");
    typeDefinition(con);
    workingWithRows(con);
    con.close();
}

void postgresql(void) {
    tntdb::Connection con = tntdb::connect("postgresql: host=localhost dbname=ex1 user=ex1user password=passwd");
    typeDefinition(con);
    workingWithRows(con);
    con.close();
}

int main(int argc, char ** argv) {
    mysql();
    postgresql();
    return EXIT_SUCCESS;
}
