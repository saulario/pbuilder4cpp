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
    struct MyCompound {
    public:
      long myCustomerId; /* my_customer */
      std::string countryId; /* Country */
      std::string name; /* Name */
      MyCompound();
      ~MyCompound();
      bool operator == (const MyCompound &);
    private:
    };
    struct MyCompoundId {
    public:
      long myCustomerId; /* my_customer */
      std::string countryId; /* Country */
    };
    struct MyCustomer {
    public:
      long id; /* Id */
      std::string name; /* Name */
      tntdb::Date creationDate; /* Creation date */
      MyCustomer();
      ~MyCustomer();
      std::string getCountryId(void) const;
      void setCountryId(const std::string & country_id);
      bool isNullCountryId(void) const;
      void setNullCountryId(void);
      bool operator == (const MyCustomer &);
    private:
      std::string * countryId; /* Country */
    };
    struct Something {
    public:
      long id; /* Id */
      std::string name; /* Name */
      long myCustomerId; /* my_customer */
      std::string countryId; /* Country */
      Something();
      ~Something();
      bool operator == (const Something &);
    private:
    };
  }
}
#endif
