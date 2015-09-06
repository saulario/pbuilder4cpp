#ifndef EX1_ENTITY_H
#define EX1_ENTITY_H
#include <tntdb/blob.h>
#include <tntdb/date.h>
#include <tntdb/datetime.h>
#include <tntdb/time.h>
namespace ex1 {
    namespace entity {

        struct Compound {
        public:
            long customer_id; /* Customer */
            std::string country_id; /* Country */
            std::string name; /* Name */
            Compound();
            ~Compound();
            bool operator==(const Compound &);
        private:
        };

        struct CompoundId {
        public:
            long customer_id; /* Customer */
            std::string country_id; /* Country */
        };

        struct Country {
        public:
            std::string id; /* Id */
            std::string name; /* Name */
            Country();
            ~Country();
            bool operator==(const Country &);
        private:
        };

        struct Customer {
        public:
            long id; /* Id */
            std::string name; /* Name */
            tntdb::Date creation_date; /* Creation date */
            Customer();
            ~Customer();
            std::string getCountry_id(void) const;
            void setCountry_id(const std::string & country_id);
            bool isNullCountry_id(void) const;
            void setNullCountry_id(void);
            bool operator==(const Customer &);
        private:
            std::string * country_id; /* Country */
        };

        struct Something {
        public:
            long id; /* Id */
            std::string name; /* Name */
            long customer_id; /* Customer */
            std::string country_id; /* Country */
            Something();
            ~Something();
            bool operator==(const Something &);
        private:
        };
    }
}
#endif
