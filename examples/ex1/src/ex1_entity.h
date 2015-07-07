#ifndef EX1_ENTITY_H
#define EX1_ENTITY_H
#include <tntdb/blob.h>
#include <tntdb/date.h>
#include <tntdb/datetime.h>
#include <tntdb/time.h>
namespace ex1 {
  namespace entity {
    struct Country {
    public:
      std::string id; /* Id */
      std::string name; /* Name */
      Country();
      ~Country();
      bool operator == (const Country &);
    private:
    };
    struct Customer {
    public:
      long id; /* Id */
      std::string name; /* Name */
      tntdb::Date creationDate; /* Creation date */
      Customer();
      ~Customer();
      std::string getCountryId(void) const;
      void setCountryId(const std::string & countryId);
      bool isNullCountryId(void) const;
      void setNullCountryId(void);
      bool operator == (const Customer &);
    private:
      std::string * countryId; /* Country */
    };
    struct Something {
    public:
      long id; /* Id */
      std::string name; /* Name */
      long customerId; /* Customer */
      std::string countryId; /* Country */
      Something();
      ~Something();
      bool operator == (const Something &);
    private:
    };
  }
}
#endif
