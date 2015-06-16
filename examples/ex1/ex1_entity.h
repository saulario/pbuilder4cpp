#ifndef EX1_ENTITY_H
#define EX1_ENTITY_H
#include <tntdb/blob.h>
#include <tntdb/date.h>
#include <tntdb/datetime.h>
#include <tntdb/time.h>
namespace ex1 {
    namespace entity {

        struct Test1 {
        public:
            int tkey; /* Primary key */
            short tsmallint; /* Smallint */
            unsigned short tsmallintUnsigned; /* Smallint unsigned */
            int tmediumint; /* Mediumint */
            unsigned int tmediumintUnsigned; /* Mediumint unsigned */
            int tinteger; /* Integer */
            unsigned int tintegerUnsigned; /* Integer unsigned */
            long tbigint; /* Bigint */
            unsigned long tbigintUnsigned; /* Bigint unsigned */
            double tdecimal; /* Decimal */
            double tdecimalUnsigned; /* Decimal unsigned */
            double tdec; /* Dec */
            double tdecUnsigned; /* Dec unsigned */
            double tfixed; /* Fixed */
            double tfixedUnsigned; /* Fixed unsigned */
            double tfloat; /* Float */
            double tfloatUnsigned; /* Float unsigned */
            double tdouble; /* Double */
            double tdoubleUnsigned; /* Double unsigned */
            tntdb::Date tdate; /* Date */
            tntdb::Datetime tdatetime; /* Datetime */
            tntdb::Datetime ttimestamp; /* Timestamp */
            tntdb::Time ttime; /* Time */
            std::string tchar; /* Char(100) */
            std::string tvarchar; /* Varchar(100) */
            Test1();
            ~Test1();
            std::string getTtext(void) const;
            void setTtext(const std::string & ttext);
            bool isNullTtext(void) const;
            void setNullTtext(void);
            tntdb::Blob getTblob(void) const;
            void setTblob(const tntdb::Blob & tblob);
            bool isNullTblob(void) const;
            void setNullTblob(void);
            bool operator==(const Test1 &);
        private:
            std::string * ttext; /* Text */
            tntdb::Blob * tblob; /* Blob */
        };

        struct Test2 {
        public:
            int tkey1; /* Primary key 1 */
            int tkey2; /* Primary key 2 */
            tntdb::Datetime ttimestamp; /* Timestamp */
            Test2();
            ~Test2();
            short getTsmallint(void) const;
            void setTsmallint(const short & tsmallint);
            bool isNullTsmallint(void) const;
            void setNullTsmallint(void);
            unsigned short getTsmallintUnsigned(void) const;
            void setTsmallintUnsigned(const unsigned short & tsmallintUnsigned);
            bool isNullTsmallintUnsigned(void) const;
            void setNullTsmallintUnsigned(void);
            int getTmediumint(void) const;
            void setTmediumint(const int & tmediumint);
            bool isNullTmediumint(void) const;
            void setNullTmediumint(void);
            unsigned int getTmediumintUnsigned(void) const;
            void setTmediumintUnsigned(const unsigned int & tmediumintUnsigned);
            bool isNullTmediumintUnsigned(void) const;
            void setNullTmediumintUnsigned(void);
            int getTinteger(void) const;
            void setTinteger(const int & tinteger);
            bool isNullTinteger(void) const;
            void setNullTinteger(void);
            unsigned int getTintegerUnsigned(void) const;
            void setTintegerUnsigned(const unsigned int & tintegerUnsigned);
            bool isNullTintegerUnsigned(void) const;
            void setNullTintegerUnsigned(void);
            long getTbigint(void) const;
            void setTbigint(const long & tbigint);
            bool isNullTbigint(void) const;
            void setNullTbigint(void);
            unsigned long getTbigintUnsigned(void) const;
            void setTbigintUnsigned(const unsigned long & tbigintUnsigned);
            bool isNullTbigintUnsigned(void) const;
            void setNullTbigintUnsigned(void);
            double getTdecimal(void) const;
            void setTdecimal(const double & tdecimal);
            bool isNullTdecimal(void) const;
            void setNullTdecimal(void);
            double getTdecimalUnsigned(void) const;
            void setTdecimalUnsigned(const double & tdecimalUnsigned);
            bool isNullTdecimalUnsigned(void) const;
            void setNullTdecimalUnsigned(void);
            double getTdec(void) const;
            void setTdec(const double & tdec);
            bool isNullTdec(void) const;
            void setNullTdec(void);
            double getTdecUnsigned(void) const;
            void setTdecUnsigned(const double & tdecUnsigned);
            bool isNullTdecUnsigned(void) const;
            void setNullTdecUnsigned(void);
            double getTfixed(void) const;
            void setTfixed(const double & tfixed);
            bool isNullTfixed(void) const;
            void setNullTfixed(void);
            double getTfixedUnsigned(void) const;
            void setTfixedUnsigned(const double & tfixedUnsigned);
            bool isNullTfixedUnsigned(void) const;
            void setNullTfixedUnsigned(void);
            double getTfloat(void) const;
            void setTfloat(const double & tfloat);
            bool isNullTfloat(void) const;
            void setNullTfloat(void);
            double getTfloatUnsigned(void) const;
            void setTfloatUnsigned(const double & tfloatUnsigned);
            bool isNullTfloatUnsigned(void) const;
            void setNullTfloatUnsigned(void);
            double getTdouble(void) const;
            void setTdouble(const double & tdouble);
            bool isNullTdouble(void) const;
            void setNullTdouble(void);
            double getTdoubleUnsigned(void) const;
            void setTdoubleUnsigned(const double & tdoubleUnsigned);
            bool isNullTdoubleUnsigned(void) const;
            void setNullTdoubleUnsigned(void);
            tntdb::Date getTdate(void) const;
            void setTdate(const tntdb::Date & tdate);
            bool isNullTdate(void) const;
            void setNullTdate(void);
            tntdb::Datetime getTdatetime(void) const;
            void setTdatetime(const tntdb::Datetime & tdatetime);
            bool isNullTdatetime(void) const;
            void setNullTdatetime(void);
            tntdb::Time getTtime(void) const;
            void setTtime(const tntdb::Time & ttime);
            bool isNullTtime(void) const;
            void setNullTtime(void);
            std::string getTchar(void) const;
            void setTchar(const std::string & tchar);
            bool isNullTchar(void) const;
            void setNullTchar(void);
            std::string getTvarchar(void) const;
            void setTvarchar(const std::string & tvarchar);
            bool isNullTvarchar(void) const;
            void setNullTvarchar(void);
            std::string getTtext(void) const;
            void setTtext(const std::string & ttext);
            bool isNullTtext(void) const;
            void setNullTtext(void);
            tntdb::Blob getTblob(void) const;
            void setTblob(const tntdb::Blob & tblob);
            bool isNullTblob(void) const;
            void setNullTblob(void);
            bool operator==(const Test2 &);
        private:
            short * tsmallint; /* Smallint */
            unsigned short * tsmallintUnsigned; /* Smallint unsigned */
            int * tmediumint; /* Mediumint */
            unsigned int * tmediumintUnsigned; /* Mediumint unsigned */
            int * tinteger; /* Integer */
            unsigned int * tintegerUnsigned; /* Integer unsigned */
            long * tbigint; /* Bigint */
            unsigned long * tbigintUnsigned; /* Bigint unsigned */
            double * tdecimal; /* Decimal */
            double * tdecimalUnsigned; /* Decimal unsigned */
            double * tdec; /* Dec */
            double * tdecUnsigned; /* Dec unsigned */
            double * tfixed; /* Fixed */
            double * tfixedUnsigned; /* Fixed unsigned */
            double * tfloat; /* Float */
            double * tfloatUnsigned; /* Float unsigned */
            double * tdouble; /* Double */
            double * tdoubleUnsigned; /* Double unsigned */
            tntdb::Date * tdate; /* Date */
            tntdb::Datetime * tdatetime; /* Datetime */
            tntdb::Time * ttime; /* Time */
            std::string * tchar; /* Char(100) */
            std::string * tvarchar; /* Varchar(100) */
            std::string * ttext; /* Text */
            tntdb::Blob * tblob; /* Blob */
        };

        struct Test2Id {
        public:
            int tkey1; /* Primary key 1 */
            int tkey2; /* Primary key 2 */
        };

        struct Test3 {
        public:
            int tkey1; /* Primary key 1 */
            int tkey2; /* Primary key 2 */
            tntdb::Datetime ttimestamp; /* Timestamp */
            Test3();
            ~Test3();
            short getTsmallint(void) const;
            void setTsmallint(const short & tsmallint);
            bool isNullTsmallint(void) const;
            void setNullTsmallint(void);
            unsigned short getTsmallintUnsigned(void) const;
            void setTsmallintUnsigned(const unsigned short & tsmallintUnsigned);
            bool isNullTsmallintUnsigned(void) const;
            void setNullTsmallintUnsigned(void);
            int getTmediumint(void) const;
            void setTmediumint(const int & tmediumint);
            bool isNullTmediumint(void) const;
            void setNullTmediumint(void);
            unsigned int getTmediumintUnsigned(void) const;
            void setTmediumintUnsigned(const unsigned int & tmediumintUnsigned);
            bool isNullTmediumintUnsigned(void) const;
            void setNullTmediumintUnsigned(void);
            int getTinteger(void) const;
            void setTinteger(const int & tinteger);
            bool isNullTinteger(void) const;
            void setNullTinteger(void);
            unsigned int getTintegerUnsigned(void) const;
            void setTintegerUnsigned(const unsigned int & tintegerUnsigned);
            bool isNullTintegerUnsigned(void) const;
            void setNullTintegerUnsigned(void);
            long getTbigint(void) const;
            void setTbigint(const long & tbigint);
            bool isNullTbigint(void) const;
            void setNullTbigint(void);
            unsigned long getTbigintUnsigned(void) const;
            void setTbigintUnsigned(const unsigned long & tbigintUnsigned);
            bool isNullTbigintUnsigned(void) const;
            void setNullTbigintUnsigned(void);
            double getTdecimal(void) const;
            void setTdecimal(const double & tdecimal);
            bool isNullTdecimal(void) const;
            void setNullTdecimal(void);
            double getTdecimalUnsigned(void) const;
            void setTdecimalUnsigned(const double & tdecimalUnsigned);
            bool isNullTdecimalUnsigned(void) const;
            void setNullTdecimalUnsigned(void);
            double getTdec(void) const;
            void setTdec(const double & tdec);
            bool isNullTdec(void) const;
            void setNullTdec(void);
            double getTdecUnsigned(void) const;
            void setTdecUnsigned(const double & tdecUnsigned);
            bool isNullTdecUnsigned(void) const;
            void setNullTdecUnsigned(void);
            double getTfixed(void) const;
            void setTfixed(const double & tfixed);
            bool isNullTfixed(void) const;
            void setNullTfixed(void);
            double getTfixedUnsigned(void) const;
            void setTfixedUnsigned(const double & tfixedUnsigned);
            bool isNullTfixedUnsigned(void) const;
            void setNullTfixedUnsigned(void);
            double getTfloat(void) const;
            void setTfloat(const double & tfloat);
            bool isNullTfloat(void) const;
            void setNullTfloat(void);
            double getTfloatUnsigned(void) const;
            void setTfloatUnsigned(const double & tfloatUnsigned);
            bool isNullTfloatUnsigned(void) const;
            void setNullTfloatUnsigned(void);
            double getTdouble(void) const;
            void setTdouble(const double & tdouble);
            bool isNullTdouble(void) const;
            void setNullTdouble(void);
            double getTdoubleUnsigned(void) const;
            void setTdoubleUnsigned(const double & tdoubleUnsigned);
            bool isNullTdoubleUnsigned(void) const;
            void setNullTdoubleUnsigned(void);
            tntdb::Date getTdate(void) const;
            void setTdate(const tntdb::Date & tdate);
            bool isNullTdate(void) const;
            void setNullTdate(void);
            tntdb::Datetime getTdatetime(void) const;
            void setTdatetime(const tntdb::Datetime & tdatetime);
            bool isNullTdatetime(void) const;
            void setNullTdatetime(void);
            tntdb::Time getTtime(void) const;
            void setTtime(const tntdb::Time & ttime);
            bool isNullTtime(void) const;
            void setNullTtime(void);
            std::string getTchar(void) const;
            void setTchar(const std::string & tchar);
            bool isNullTchar(void) const;
            void setNullTchar(void);
            std::string getTvarchar(void) const;
            void setTvarchar(const std::string & tvarchar);
            bool isNullTvarchar(void) const;
            void setNullTvarchar(void);
            std::string getTtext(void) const;
            void setTtext(const std::string & ttext);
            bool isNullTtext(void) const;
            void setNullTtext(void);
            tntdb::Blob getTblob(void) const;
            void setTblob(const tntdb::Blob & tblob);
            bool isNullTblob(void) const;
            void setNullTblob(void);
            bool operator==(const Test3 &);
        private:
            short * tsmallint; /* Smallint */
            unsigned short * tsmallintUnsigned; /* Smallint unsigned */
            int * tmediumint; /* Mediumint */
            unsigned int * tmediumintUnsigned; /* Mediumint unsigned */
            int * tinteger; /* Integer */
            unsigned int * tintegerUnsigned; /* Integer unsigned */
            long * tbigint; /* Bigint */
            unsigned long * tbigintUnsigned; /* Bigint unsigned */
            double * tdecimal; /* Decimal */
            double * tdecimalUnsigned; /* Decimal unsigned */
            double * tdec; /* Dec */
            double * tdecUnsigned; /* Dec unsigned */
            double * tfixed; /* Fixed */
            double * tfixedUnsigned; /* Fixed unsigned */
            double * tfloat; /* Float */
            double * tfloatUnsigned; /* Float unsigned */
            double * tdouble; /* Double */
            double * tdoubleUnsigned; /* Double unsigned */
            tntdb::Date * tdate; /* Date */
            tntdb::Datetime * tdatetime; /* Datetime */
            tntdb::Time * ttime; /* Time */
            std::string * tchar; /* Char(100) */
            std::string * tvarchar; /* Varchar(100) */
            std::string * ttext; /* Text */
            tntdb::Blob * tblob; /* Blob */
        };
    }
}
#endif
