#include <cstdlib>
#include <list>
#include <string>
#include <tntdb/connect.h>
#include <tntdb/connection.h>

#include "ex1_dao.h"
#include "ex1_entity.h"

int main(int, char **);

/*
 * type definition example. Future versions will contain these defintions
 */
void typeDefinition(tntdb::Connection & con) {
    
//    typedef std::pair<std::string, ex1::entity::Country *> CountryPair;
//    typedef std::map<std::string, ex1::entity::Country *> CountryMap;
    typedef std::list<ex1::entity::Country *> CountryList;
    
    std::string cdn = "select " + ex1::dao::CountryDAO::getInstance()->getColumns() 
            + " from country where "
            + " name like :name";
    std::cerr << cdn << std::endl;
    
    
    tntdb::Statement stmt = con.prepare(cdn)
            .setString("name", "%");
    
    
    CountryList countries = ex1::dao::CountryDAO::getInstance()->query(con, stmt);
    for (ex1::entity::Country * country : countries) {
        std::cerr << country->name << std::endl;
    }
    
    
    
    
    
}

int main(int argc, char ** argv) {
    
    tntdb::Connection con = tntdb::connect("mysql:db=ex1;user=user;password=passwd");
    
    typeDefinition(con);
    
    

    
    con.close();

    return EXIT_SUCCESS;
}
