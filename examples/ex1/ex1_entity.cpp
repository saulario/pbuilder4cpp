#include "ex1_entity.h"
using namespace ex1::entity;

Test1::Test1() {
    tkey = 0;
    tsmallint = 0;
    tsmallintUnsigned = 0;
    tmediumint = 0;
    tmediumintUnsigned = 0;
    tinteger = 0;
    tintegerUnsigned = 0;
    tbigint = 0L;
    tbigintUnsigned = 0L;
    tdecimal = 0.0;
    tdecimalUnsigned = 0.0;
    tdec = 0.0;
    tdecUnsigned = 0.0;
    tfixed = 0.0;
    tfixedUnsigned = 0.0;
    tfloat = 0.0;
    tfloatUnsigned = 0.0;
    tdouble = 0.0;
    tdoubleUnsigned = 0.0;
    tdate = tntdb::Date();
    tdatetime = tntdb::Datetime();
    ttimestamp = tntdb::Datetime();
    ttime = tntdb::Time();
    tchar = "";
    tvarchar = "";
    ttext = NULL;
    tblob = NULL;
}

Test1::~Test1() {
    if (ttext != NULL) {
        delete ttext;
    }
    if (tblob != NULL) {
        delete tblob;
    }
}

std::string Test1::getTtext(void) const {
    return (ttext != NULL ? * ttext : "");
}

void Test1::setTtext(const std::string & ttext_) {
    if (ttext != NULL) {
        delete ttext;
    }
    ttext = new std::string(ttext_);
}

bool Test1::isNullTtext(void) const {
    return (ttext == NULL);
}

void Test1::setNullTtext(void) {
    if (ttext != NULL) {
        delete ttext;
    }
    ttext = NULL;
}

tntdb::Blob Test1::getTblob(void) const {
    return (tblob != NULL ? * tblob : tntdb::Blob());
}

void Test1::setTblob(const tntdb::Blob & tblob_) {
    if (tblob != NULL) {
        delete tblob;
    }
    tblob = new tntdb::Blob(tblob_);
}

bool Test1::isNullTblob(void) const {
    return (tblob == NULL);
}

void Test1::setNullTblob(void) {
    if (tblob != NULL) {
        delete tblob;
    }
    tblob = NULL;
}

bool Test1::operator==(const Test1 & other) {
    if (this->tkey != other.tkey) return false;
    if (this->tsmallint != other.tsmallint) return false;
    if (this->tsmallintUnsigned != other.tsmallintUnsigned) return false;
    if (this->tmediumint != other.tmediumint) return false;
    if (this->tmediumintUnsigned != other.tmediumintUnsigned) return false;
    if (this->tinteger != other.tinteger) return false;
    if (this->tintegerUnsigned != other.tintegerUnsigned) return false;
    if (this->tbigint != other.tbigint) return false;
    if (this->tbigintUnsigned != other.tbigintUnsigned) return false;
    if (this->tdecimal != other.tdecimal) return false;
    if (this->tdecimalUnsigned != other.tdecimalUnsigned) return false;
    if (this->tdec != other.tdec) return false;
    if (this->tdecUnsigned != other.tdecUnsigned) return false;
    if (this->tfixed != other.tfixed) return false;
    if (this->tfixedUnsigned != other.tfixedUnsigned) return false;
    if (this->tfloat != other.tfloat) return false;
    if (this->tfloatUnsigned != other.tfloatUnsigned) return false;
    if (this->tdouble != other.tdouble) return false;
    if (this->tdoubleUnsigned != other.tdoubleUnsigned) return false;
    if (this->tdate != other.tdate) return false;
    if (this->tdatetime != other.tdatetime) return false;
    if (this->ttimestamp != other.ttimestamp) return false;
    if (this->ttime != other.ttime) return false;
    if (this->tchar != other.tchar) return false;
    if (this->tvarchar != other.tvarchar) return false;
    if (this->ttext != other.ttext) return false;
    if (this->tblob != other.tblob) return false;
    return true;
}

Test2::Test2() {
    tkey1 = 0;
    tkey2 = 0;
    tsmallint = NULL;
    tsmallintUnsigned = NULL;
    tmediumint = NULL;
    tmediumintUnsigned = NULL;
    tinteger = NULL;
    tintegerUnsigned = NULL;
    tbigint = NULL;
    tbigintUnsigned = NULL;
    tdecimal = NULL;
    tdecimalUnsigned = NULL;
    tdec = NULL;
    tdecUnsigned = NULL;
    tfixed = NULL;
    tfixedUnsigned = NULL;
    tfloat = NULL;
    tfloatUnsigned = NULL;
    tdouble = NULL;
    tdoubleUnsigned = NULL;
    tdate = NULL;
    tdatetime = NULL;
    ttimestamp = tntdb::Datetime();
    ttime = NULL;
    tchar = NULL;
    tvarchar = NULL;
    ttext = NULL;
    tblob = NULL;
}

Test2::~Test2() {
    if (tsmallint != NULL) {
        delete tsmallint;
    }
    if (tsmallintUnsigned != NULL) {
        delete tsmallintUnsigned;
    }
    if (tmediumint != NULL) {
        delete tmediumint;
    }
    if (tmediumintUnsigned != NULL) {
        delete tmediumintUnsigned;
    }
    if (tinteger != NULL) {
        delete tinteger;
    }
    if (tintegerUnsigned != NULL) {
        delete tintegerUnsigned;
    }
    if (tbigint != NULL) {
        delete tbigint;
    }
    if (tbigintUnsigned != NULL) {
        delete tbigintUnsigned;
    }
    if (tdecimal != NULL) {
        delete tdecimal;
    }
    if (tdecimalUnsigned != NULL) {
        delete tdecimalUnsigned;
    }
    if (tdec != NULL) {
        delete tdec;
    }
    if (tdecUnsigned != NULL) {
        delete tdecUnsigned;
    }
    if (tfixed != NULL) {
        delete tfixed;
    }
    if (tfixedUnsigned != NULL) {
        delete tfixedUnsigned;
    }
    if (tfloat != NULL) {
        delete tfloat;
    }
    if (tfloatUnsigned != NULL) {
        delete tfloatUnsigned;
    }
    if (tdouble != NULL) {
        delete tdouble;
    }
    if (tdoubleUnsigned != NULL) {
        delete tdoubleUnsigned;
    }
    if (tdate != NULL) {
        delete tdate;
    }
    if (tdatetime != NULL) {
        delete tdatetime;
    }
    if (ttime != NULL) {
        delete ttime;
    }
    if (tchar != NULL) {
        delete tchar;
    }
    if (tvarchar != NULL) {
        delete tvarchar;
    }
    if (ttext != NULL) {
        delete ttext;
    }
    if (tblob != NULL) {
        delete tblob;
    }
}

short Test2::getTsmallint(void) const {
    return (tsmallint != NULL ? * tsmallint : 0);
}

void Test2::setTsmallint(const short & tsmallint_) {
    if (tsmallint != NULL) {
        delete tsmallint;
    }
    tsmallint = new short(tsmallint_);
}

bool Test2::isNullTsmallint(void) const {
    return (tsmallint == NULL);
}

void Test2::setNullTsmallint(void) {
    if (tsmallint != NULL) {
        delete tsmallint;
    }
    tsmallint = NULL;
}

unsigned short Test2::getTsmallintUnsigned(void) const {
    return (tsmallintUnsigned != NULL ? * tsmallintUnsigned : 0);
}

void Test2::setTsmallintUnsigned(const unsigned short & tsmallintUnsigned_) {
    if (tsmallintUnsigned != NULL) {
        delete tsmallintUnsigned;
    }
    tsmallintUnsigned = new unsigned short(tsmallintUnsigned_);
}

bool Test2::isNullTsmallintUnsigned(void) const {
    return (tsmallintUnsigned == NULL);
}

void Test2::setNullTsmallintUnsigned(void) {
    if (tsmallintUnsigned != NULL) {
        delete tsmallintUnsigned;
    }
    tsmallintUnsigned = NULL;
}

int Test2::getTmediumint(void) const {
    return (tmediumint != NULL ? * tmediumint : 0);
}

void Test2::setTmediumint(const int & tmediumint_) {
    if (tmediumint != NULL) {
        delete tmediumint;
    }
    tmediumint = new int(tmediumint_);
}

bool Test2::isNullTmediumint(void) const {
    return (tmediumint == NULL);
}

void Test2::setNullTmediumint(void) {
    if (tmediumint != NULL) {
        delete tmediumint;
    }
    tmediumint = NULL;
}

unsigned int Test2::getTmediumintUnsigned(void) const {
    return (tmediumintUnsigned != NULL ? * tmediumintUnsigned : 0);
}

void Test2::setTmediumintUnsigned(const unsigned int & tmediumintUnsigned_) {
    if (tmediumintUnsigned != NULL) {
        delete tmediumintUnsigned;
    }
    tmediumintUnsigned = new unsigned int(tmediumintUnsigned_);
}

bool Test2::isNullTmediumintUnsigned(void) const {
    return (tmediumintUnsigned == NULL);
}

void Test2::setNullTmediumintUnsigned(void) {
    if (tmediumintUnsigned != NULL) {
        delete tmediumintUnsigned;
    }
    tmediumintUnsigned = NULL;
}

int Test2::getTinteger(void) const {
    return (tinteger != NULL ? * tinteger : 0);
}

void Test2::setTinteger(const int & tinteger_) {
    if (tinteger != NULL) {
        delete tinteger;
    }
    tinteger = new int(tinteger_);
}

bool Test2::isNullTinteger(void) const {
    return (tinteger == NULL);
}

void Test2::setNullTinteger(void) {
    if (tinteger != NULL) {
        delete tinteger;
    }
    tinteger = NULL;
}

unsigned int Test2::getTintegerUnsigned(void) const {
    return (tintegerUnsigned != NULL ? * tintegerUnsigned : 0);
}

void Test2::setTintegerUnsigned(const unsigned int & tintegerUnsigned_) {
    if (tintegerUnsigned != NULL) {
        delete tintegerUnsigned;
    }
    tintegerUnsigned = new unsigned int(tintegerUnsigned_);
}

bool Test2::isNullTintegerUnsigned(void) const {
    return (tintegerUnsigned == NULL);
}

void Test2::setNullTintegerUnsigned(void) {
    if (tintegerUnsigned != NULL) {
        delete tintegerUnsigned;
    }
    tintegerUnsigned = NULL;
}

long Test2::getTbigint(void) const {
    return (tbigint != NULL ? * tbigint : 0L);
}

void Test2::setTbigint(const long & tbigint_) {
    if (tbigint != NULL) {
        delete tbigint;
    }
    tbigint = new long(tbigint_);
}

bool Test2::isNullTbigint(void) const {
    return (tbigint == NULL);
}

void Test2::setNullTbigint(void) {
    if (tbigint != NULL) {
        delete tbigint;
    }
    tbigint = NULL;
}

unsigned long Test2::getTbigintUnsigned(void) const {
    return (tbigintUnsigned != NULL ? * tbigintUnsigned : 0L);
}

void Test2::setTbigintUnsigned(const unsigned long & tbigintUnsigned_) {
    if (tbigintUnsigned != NULL) {
        delete tbigintUnsigned;
    }
    tbigintUnsigned = new unsigned long(tbigintUnsigned_);
}

bool Test2::isNullTbigintUnsigned(void) const {
    return (tbigintUnsigned == NULL);
}

void Test2::setNullTbigintUnsigned(void) {
    if (tbigintUnsigned != NULL) {
        delete tbigintUnsigned;
    }
    tbigintUnsigned = NULL;
}

double Test2::getTdecimal(void) const {
    return (tdecimal != NULL ? * tdecimal : 0.0);
}

void Test2::setTdecimal(const double & tdecimal_) {
    if (tdecimal != NULL) {
        delete tdecimal;
    }
    tdecimal = new double(tdecimal_);
}

bool Test2::isNullTdecimal(void) const {
    return (tdecimal == NULL);
}

void Test2::setNullTdecimal(void) {
    if (tdecimal != NULL) {
        delete tdecimal;
    }
    tdecimal = NULL;
}

double Test2::getTdecimalUnsigned(void) const {
    return (tdecimalUnsigned != NULL ? * tdecimalUnsigned : 0.0);
}

void Test2::setTdecimalUnsigned(const double & tdecimalUnsigned_) {
    if (tdecimalUnsigned != NULL) {
        delete tdecimalUnsigned;
    }
    tdecimalUnsigned = new double(tdecimalUnsigned_);
}

bool Test2::isNullTdecimalUnsigned(void) const {
    return (tdecimalUnsigned == NULL);
}

void Test2::setNullTdecimalUnsigned(void) {
    if (tdecimalUnsigned != NULL) {
        delete tdecimalUnsigned;
    }
    tdecimalUnsigned = NULL;
}

double Test2::getTdec(void) const {
    return (tdec != NULL ? * tdec : 0.0);
}

void Test2::setTdec(const double & tdec_) {
    if (tdec != NULL) {
        delete tdec;
    }
    tdec = new double(tdec_);
}

bool Test2::isNullTdec(void) const {
    return (tdec == NULL);
}

void Test2::setNullTdec(void) {
    if (tdec != NULL) {
        delete tdec;
    }
    tdec = NULL;
}

double Test2::getTdecUnsigned(void) const {
    return (tdecUnsigned != NULL ? * tdecUnsigned : 0.0);
}

void Test2::setTdecUnsigned(const double & tdecUnsigned_) {
    if (tdecUnsigned != NULL) {
        delete tdecUnsigned;
    }
    tdecUnsigned = new double(tdecUnsigned_);
}

bool Test2::isNullTdecUnsigned(void) const {
    return (tdecUnsigned == NULL);
}

void Test2::setNullTdecUnsigned(void) {
    if (tdecUnsigned != NULL) {
        delete tdecUnsigned;
    }
    tdecUnsigned = NULL;
}

double Test2::getTfixed(void) const {
    return (tfixed != NULL ? * tfixed : 0.0);
}

void Test2::setTfixed(const double & tfixed_) {
    if (tfixed != NULL) {
        delete tfixed;
    }
    tfixed = new double(tfixed_);
}

bool Test2::isNullTfixed(void) const {
    return (tfixed == NULL);
}

void Test2::setNullTfixed(void) {
    if (tfixed != NULL) {
        delete tfixed;
    }
    tfixed = NULL;
}

double Test2::getTfixedUnsigned(void) const {
    return (tfixedUnsigned != NULL ? * tfixedUnsigned : 0.0);
}

void Test2::setTfixedUnsigned(const double & tfixedUnsigned_) {
    if (tfixedUnsigned != NULL) {
        delete tfixedUnsigned;
    }
    tfixedUnsigned = new double(tfixedUnsigned_);
}

bool Test2::isNullTfixedUnsigned(void) const {
    return (tfixedUnsigned == NULL);
}

void Test2::setNullTfixedUnsigned(void) {
    if (tfixedUnsigned != NULL) {
        delete tfixedUnsigned;
    }
    tfixedUnsigned = NULL;
}

double Test2::getTfloat(void) const {
    return (tfloat != NULL ? * tfloat : 0.0);
}

void Test2::setTfloat(const double & tfloat_) {
    if (tfloat != NULL) {
        delete tfloat;
    }
    tfloat = new double(tfloat_);
}

bool Test2::isNullTfloat(void) const {
    return (tfloat == NULL);
}

void Test2::setNullTfloat(void) {
    if (tfloat != NULL) {
        delete tfloat;
    }
    tfloat = NULL;
}

double Test2::getTfloatUnsigned(void) const {
    return (tfloatUnsigned != NULL ? * tfloatUnsigned : 0.0);
}

void Test2::setTfloatUnsigned(const double & tfloatUnsigned_) {
    if (tfloatUnsigned != NULL) {
        delete tfloatUnsigned;
    }
    tfloatUnsigned = new double(tfloatUnsigned_);
}

bool Test2::isNullTfloatUnsigned(void) const {
    return (tfloatUnsigned == NULL);
}

void Test2::setNullTfloatUnsigned(void) {
    if (tfloatUnsigned != NULL) {
        delete tfloatUnsigned;
    }
    tfloatUnsigned = NULL;
}

double Test2::getTdouble(void) const {
    return (tdouble != NULL ? * tdouble : 0.0);
}

void Test2::setTdouble(const double & tdouble_) {
    if (tdouble != NULL) {
        delete tdouble;
    }
    tdouble = new double(tdouble_);
}

bool Test2::isNullTdouble(void) const {
    return (tdouble == NULL);
}

void Test2::setNullTdouble(void) {
    if (tdouble != NULL) {
        delete tdouble;
    }
    tdouble = NULL;
}

double Test2::getTdoubleUnsigned(void) const {
    return (tdoubleUnsigned != NULL ? * tdoubleUnsigned : 0.0);
}

void Test2::setTdoubleUnsigned(const double & tdoubleUnsigned_) {
    if (tdoubleUnsigned != NULL) {
        delete tdoubleUnsigned;
    }
    tdoubleUnsigned = new double(tdoubleUnsigned_);
}

bool Test2::isNullTdoubleUnsigned(void) const {
    return (tdoubleUnsigned == NULL);
}

void Test2::setNullTdoubleUnsigned(void) {
    if (tdoubleUnsigned != NULL) {
        delete tdoubleUnsigned;
    }
    tdoubleUnsigned = NULL;
}

tntdb::Date Test2::getTdate(void) const {
    return (tdate != NULL ? * tdate : tntdb::Date());
}

void Test2::setTdate(const tntdb::Date & tdate_) {
    if (tdate != NULL) {
        delete tdate;
    }
    tdate = new tntdb::Date(tdate_);
}

bool Test2::isNullTdate(void) const {
    return (tdate == NULL);
}

void Test2::setNullTdate(void) {
    if (tdate != NULL) {
        delete tdate;
    }
    tdate = NULL;
}

tntdb::Datetime Test2::getTdatetime(void) const {
    return (tdatetime != NULL ? * tdatetime : tntdb::Datetime());
}

void Test2::setTdatetime(const tntdb::Datetime & tdatetime_) {
    if (tdatetime != NULL) {
        delete tdatetime;
    }
    tdatetime = new tntdb::Datetime(tdatetime_);
}

bool Test2::isNullTdatetime(void) const {
    return (tdatetime == NULL);
}

void Test2::setNullTdatetime(void) {
    if (tdatetime != NULL) {
        delete tdatetime;
    }
    tdatetime = NULL;
}

tntdb::Time Test2::getTtime(void) const {
    return (ttime != NULL ? * ttime : tntdb::Time());
}

void Test2::setTtime(const tntdb::Time & ttime_) {
    if (ttime != NULL) {
        delete ttime;
    }
    ttime = new tntdb::Time(ttime_);
}

bool Test2::isNullTtime(void) const {
    return (ttime == NULL);
}

void Test2::setNullTtime(void) {
    if (ttime != NULL) {
        delete ttime;
    }
    ttime = NULL;
}

std::string Test2::getTchar(void) const {
    return (tchar != NULL ? * tchar : "");
}

void Test2::setTchar(const std::string & tchar_) {
    if (tchar != NULL) {
        delete tchar;
    }
    tchar = new std::string(tchar_);
}

bool Test2::isNullTchar(void) const {
    return (tchar == NULL);
}

void Test2::setNullTchar(void) {
    if (tchar != NULL) {
        delete tchar;
    }
    tchar = NULL;
}

std::string Test2::getTvarchar(void) const {
    return (tvarchar != NULL ? * tvarchar : "");
}

void Test2::setTvarchar(const std::string & tvarchar_) {
    if (tvarchar != NULL) {
        delete tvarchar;
    }
    tvarchar = new std::string(tvarchar_);
}

bool Test2::isNullTvarchar(void) const {
    return (tvarchar == NULL);
}

void Test2::setNullTvarchar(void) {
    if (tvarchar != NULL) {
        delete tvarchar;
    }
    tvarchar = NULL;
}

std::string Test2::getTtext(void) const {
    return (ttext != NULL ? * ttext : "");
}

void Test2::setTtext(const std::string & ttext_) {
    if (ttext != NULL) {
        delete ttext;
    }
    ttext = new std::string(ttext_);
}

bool Test2::isNullTtext(void) const {
    return (ttext == NULL);
}

void Test2::setNullTtext(void) {
    if (ttext != NULL) {
        delete ttext;
    }
    ttext = NULL;
}

tntdb::Blob Test2::getTblob(void) const {
    return (tblob != NULL ? * tblob : tntdb::Blob());
}

void Test2::setTblob(const tntdb::Blob & tblob_) {
    if (tblob != NULL) {
        delete tblob;
    }
    tblob = new tntdb::Blob(tblob_);
}

bool Test2::isNullTblob(void) const {
    return (tblob == NULL);
}

void Test2::setNullTblob(void) {
    if (tblob != NULL) {
        delete tblob;
    }
    tblob = NULL;
}

bool Test2::operator==(const Test2 & other) {
    if (this->tkey1 != other.tkey1) return false;
    if (this->tkey2 != other.tkey2) return false;
    if (this->tsmallint != other.tsmallint) return false;
    if (this->tsmallintUnsigned != other.tsmallintUnsigned) return false;
    if (this->tmediumint != other.tmediumint) return false;
    if (this->tmediumintUnsigned != other.tmediumintUnsigned) return false;
    if (this->tinteger != other.tinteger) return false;
    if (this->tintegerUnsigned != other.tintegerUnsigned) return false;
    if (this->tbigint != other.tbigint) return false;
    if (this->tbigintUnsigned != other.tbigintUnsigned) return false;
    if (this->tdecimal != other.tdecimal) return false;
    if (this->tdecimalUnsigned != other.tdecimalUnsigned) return false;
    if (this->tdec != other.tdec) return false;
    if (this->tdecUnsigned != other.tdecUnsigned) return false;
    if (this->tfixed != other.tfixed) return false;
    if (this->tfixedUnsigned != other.tfixedUnsigned) return false;
    if (this->tfloat != other.tfloat) return false;
    if (this->tfloatUnsigned != other.tfloatUnsigned) return false;
    if (this->tdouble != other.tdouble) return false;
    if (this->tdoubleUnsigned != other.tdoubleUnsigned) return false;
    if (this->tdate != other.tdate) return false;
    if (this->tdatetime != other.tdatetime) return false;
    if (this->ttimestamp != other.ttimestamp) return false;
    if (this->ttime != other.ttime) return false;
    if (this->tchar != other.tchar) return false;
    if (this->tvarchar != other.tvarchar) return false;
    if (this->ttext != other.ttext) return false;
    if (this->tblob != other.tblob) return false;
    return true;
}

Test3::Test3() {
    tkey1 = 0;
    tkey2 = 0;
    tsmallint = NULL;
    tsmallintUnsigned = NULL;
    tmediumint = NULL;
    tmediumintUnsigned = NULL;
    tinteger = NULL;
    tintegerUnsigned = NULL;
    tbigint = NULL;
    tbigintUnsigned = NULL;
    tdecimal = NULL;
    tdecimalUnsigned = NULL;
    tdec = NULL;
    tdecUnsigned = NULL;
    tfixed = NULL;
    tfixedUnsigned = NULL;
    tfloat = NULL;
    tfloatUnsigned = NULL;
    tdouble = NULL;
    tdoubleUnsigned = NULL;
    tdate = NULL;
    tdatetime = NULL;
    ttimestamp = tntdb::Datetime();
    ttime = NULL;
    tchar = NULL;
    tvarchar = NULL;
    ttext = NULL;
    tblob = NULL;
}

Test3::~Test3() {
    if (tsmallint != NULL) {
        delete tsmallint;
    }
    if (tsmallintUnsigned != NULL) {
        delete tsmallintUnsigned;
    }
    if (tmediumint != NULL) {
        delete tmediumint;
    }
    if (tmediumintUnsigned != NULL) {
        delete tmediumintUnsigned;
    }
    if (tinteger != NULL) {
        delete tinteger;
    }
    if (tintegerUnsigned != NULL) {
        delete tintegerUnsigned;
    }
    if (tbigint != NULL) {
        delete tbigint;
    }
    if (tbigintUnsigned != NULL) {
        delete tbigintUnsigned;
    }
    if (tdecimal != NULL) {
        delete tdecimal;
    }
    if (tdecimalUnsigned != NULL) {
        delete tdecimalUnsigned;
    }
    if (tdec != NULL) {
        delete tdec;
    }
    if (tdecUnsigned != NULL) {
        delete tdecUnsigned;
    }
    if (tfixed != NULL) {
        delete tfixed;
    }
    if (tfixedUnsigned != NULL) {
        delete tfixedUnsigned;
    }
    if (tfloat != NULL) {
        delete tfloat;
    }
    if (tfloatUnsigned != NULL) {
        delete tfloatUnsigned;
    }
    if (tdouble != NULL) {
        delete tdouble;
    }
    if (tdoubleUnsigned != NULL) {
        delete tdoubleUnsigned;
    }
    if (tdate != NULL) {
        delete tdate;
    }
    if (tdatetime != NULL) {
        delete tdatetime;
    }
    if (ttime != NULL) {
        delete ttime;
    }
    if (tchar != NULL) {
        delete tchar;
    }
    if (tvarchar != NULL) {
        delete tvarchar;
    }
    if (ttext != NULL) {
        delete ttext;
    }
    if (tblob != NULL) {
        delete tblob;
    }
}

short Test3::getTsmallint(void) const {
    return (tsmallint != NULL ? * tsmallint : 0);
}

void Test3::setTsmallint(const short & tsmallint_) {
    if (tsmallint != NULL) {
        delete tsmallint;
    }
    tsmallint = new short(tsmallint_);
}

bool Test3::isNullTsmallint(void) const {
    return (tsmallint == NULL);
}

void Test3::setNullTsmallint(void) {
    if (tsmallint != NULL) {
        delete tsmallint;
    }
    tsmallint = NULL;
}

unsigned short Test3::getTsmallintUnsigned(void) const {
    return (tsmallintUnsigned != NULL ? * tsmallintUnsigned : 0);
}

void Test3::setTsmallintUnsigned(const unsigned short & tsmallintUnsigned_) {
    if (tsmallintUnsigned != NULL) {
        delete tsmallintUnsigned;
    }
    tsmallintUnsigned = new unsigned short(tsmallintUnsigned_);
}

bool Test3::isNullTsmallintUnsigned(void) const {
    return (tsmallintUnsigned == NULL);
}

void Test3::setNullTsmallintUnsigned(void) {
    if (tsmallintUnsigned != NULL) {
        delete tsmallintUnsigned;
    }
    tsmallintUnsigned = NULL;
}

int Test3::getTmediumint(void) const {
    return (tmediumint != NULL ? * tmediumint : 0);
}

void Test3::setTmediumint(const int & tmediumint_) {
    if (tmediumint != NULL) {
        delete tmediumint;
    }
    tmediumint = new int(tmediumint_);
}

bool Test3::isNullTmediumint(void) const {
    return (tmediumint == NULL);
}

void Test3::setNullTmediumint(void) {
    if (tmediumint != NULL) {
        delete tmediumint;
    }
    tmediumint = NULL;
}

unsigned int Test3::getTmediumintUnsigned(void) const {
    return (tmediumintUnsigned != NULL ? * tmediumintUnsigned : 0);
}

void Test3::setTmediumintUnsigned(const unsigned int & tmediumintUnsigned_) {
    if (tmediumintUnsigned != NULL) {
        delete tmediumintUnsigned;
    }
    tmediumintUnsigned = new unsigned int(tmediumintUnsigned_);
}

bool Test3::isNullTmediumintUnsigned(void) const {
    return (tmediumintUnsigned == NULL);
}

void Test3::setNullTmediumintUnsigned(void) {
    if (tmediumintUnsigned != NULL) {
        delete tmediumintUnsigned;
    }
    tmediumintUnsigned = NULL;
}

int Test3::getTinteger(void) const {
    return (tinteger != NULL ? * tinteger : 0);
}

void Test3::setTinteger(const int & tinteger_) {
    if (tinteger != NULL) {
        delete tinteger;
    }
    tinteger = new int(tinteger_);
}

bool Test3::isNullTinteger(void) const {
    return (tinteger == NULL);
}

void Test3::setNullTinteger(void) {
    if (tinteger != NULL) {
        delete tinteger;
    }
    tinteger = NULL;
}

unsigned int Test3::getTintegerUnsigned(void) const {
    return (tintegerUnsigned != NULL ? * tintegerUnsigned : 0);
}

void Test3::setTintegerUnsigned(const unsigned int & tintegerUnsigned_) {
    if (tintegerUnsigned != NULL) {
        delete tintegerUnsigned;
    }
    tintegerUnsigned = new unsigned int(tintegerUnsigned_);
}

bool Test3::isNullTintegerUnsigned(void) const {
    return (tintegerUnsigned == NULL);
}

void Test3::setNullTintegerUnsigned(void) {
    if (tintegerUnsigned != NULL) {
        delete tintegerUnsigned;
    }
    tintegerUnsigned = NULL;
}

long Test3::getTbigint(void) const {
    return (tbigint != NULL ? * tbigint : 0L);
}

void Test3::setTbigint(const long & tbigint_) {
    if (tbigint != NULL) {
        delete tbigint;
    }
    tbigint = new long(tbigint_);
}

bool Test3::isNullTbigint(void) const {
    return (tbigint == NULL);
}

void Test3::setNullTbigint(void) {
    if (tbigint != NULL) {
        delete tbigint;
    }
    tbigint = NULL;
}

unsigned long Test3::getTbigintUnsigned(void) const {
    return (tbigintUnsigned != NULL ? * tbigintUnsigned : 0L);
}

void Test3::setTbigintUnsigned(const unsigned long & tbigintUnsigned_) {
    if (tbigintUnsigned != NULL) {
        delete tbigintUnsigned;
    }
    tbigintUnsigned = new unsigned long(tbigintUnsigned_);
}

bool Test3::isNullTbigintUnsigned(void) const {
    return (tbigintUnsigned == NULL);
}

void Test3::setNullTbigintUnsigned(void) {
    if (tbigintUnsigned != NULL) {
        delete tbigintUnsigned;
    }
    tbigintUnsigned = NULL;
}

double Test3::getTdecimal(void) const {
    return (tdecimal != NULL ? * tdecimal : 0.0);
}

void Test3::setTdecimal(const double & tdecimal_) {
    if (tdecimal != NULL) {
        delete tdecimal;
    }
    tdecimal = new double(tdecimal_);
}

bool Test3::isNullTdecimal(void) const {
    return (tdecimal == NULL);
}

void Test3::setNullTdecimal(void) {
    if (tdecimal != NULL) {
        delete tdecimal;
    }
    tdecimal = NULL;
}

double Test3::getTdecimalUnsigned(void) const {
    return (tdecimalUnsigned != NULL ? * tdecimalUnsigned : 0.0);
}

void Test3::setTdecimalUnsigned(const double & tdecimalUnsigned_) {
    if (tdecimalUnsigned != NULL) {
        delete tdecimalUnsigned;
    }
    tdecimalUnsigned = new double(tdecimalUnsigned_);
}

bool Test3::isNullTdecimalUnsigned(void) const {
    return (tdecimalUnsigned == NULL);
}

void Test3::setNullTdecimalUnsigned(void) {
    if (tdecimalUnsigned != NULL) {
        delete tdecimalUnsigned;
    }
    tdecimalUnsigned = NULL;
}

double Test3::getTdec(void) const {
    return (tdec != NULL ? * tdec : 0.0);
}

void Test3::setTdec(const double & tdec_) {
    if (tdec != NULL) {
        delete tdec;
    }
    tdec = new double(tdec_);
}

bool Test3::isNullTdec(void) const {
    return (tdec == NULL);
}

void Test3::setNullTdec(void) {
    if (tdec != NULL) {
        delete tdec;
    }
    tdec = NULL;
}

double Test3::getTdecUnsigned(void) const {
    return (tdecUnsigned != NULL ? * tdecUnsigned : 0.0);
}

void Test3::setTdecUnsigned(const double & tdecUnsigned_) {
    if (tdecUnsigned != NULL) {
        delete tdecUnsigned;
    }
    tdecUnsigned = new double(tdecUnsigned_);
}

bool Test3::isNullTdecUnsigned(void) const {
    return (tdecUnsigned == NULL);
}

void Test3::setNullTdecUnsigned(void) {
    if (tdecUnsigned != NULL) {
        delete tdecUnsigned;
    }
    tdecUnsigned = NULL;
}

double Test3::getTfixed(void) const {
    return (tfixed != NULL ? * tfixed : 0.0);
}

void Test3::setTfixed(const double & tfixed_) {
    if (tfixed != NULL) {
        delete tfixed;
    }
    tfixed = new double(tfixed_);
}

bool Test3::isNullTfixed(void) const {
    return (tfixed == NULL);
}

void Test3::setNullTfixed(void) {
    if (tfixed != NULL) {
        delete tfixed;
    }
    tfixed = NULL;
}

double Test3::getTfixedUnsigned(void) const {
    return (tfixedUnsigned != NULL ? * tfixedUnsigned : 0.0);
}

void Test3::setTfixedUnsigned(const double & tfixedUnsigned_) {
    if (tfixedUnsigned != NULL) {
        delete tfixedUnsigned;
    }
    tfixedUnsigned = new double(tfixedUnsigned_);
}

bool Test3::isNullTfixedUnsigned(void) const {
    return (tfixedUnsigned == NULL);
}

void Test3::setNullTfixedUnsigned(void) {
    if (tfixedUnsigned != NULL) {
        delete tfixedUnsigned;
    }
    tfixedUnsigned = NULL;
}

double Test3::getTfloat(void) const {
    return (tfloat != NULL ? * tfloat : 0.0);
}

void Test3::setTfloat(const double & tfloat_) {
    if (tfloat != NULL) {
        delete tfloat;
    }
    tfloat = new double(tfloat_);
}

bool Test3::isNullTfloat(void) const {
    return (tfloat == NULL);
}

void Test3::setNullTfloat(void) {
    if (tfloat != NULL) {
        delete tfloat;
    }
    tfloat = NULL;
}

double Test3::getTfloatUnsigned(void) const {
    return (tfloatUnsigned != NULL ? * tfloatUnsigned : 0.0);
}

void Test3::setTfloatUnsigned(const double & tfloatUnsigned_) {
    if (tfloatUnsigned != NULL) {
        delete tfloatUnsigned;
    }
    tfloatUnsigned = new double(tfloatUnsigned_);
}

bool Test3::isNullTfloatUnsigned(void) const {
    return (tfloatUnsigned == NULL);
}

void Test3::setNullTfloatUnsigned(void) {
    if (tfloatUnsigned != NULL) {
        delete tfloatUnsigned;
    }
    tfloatUnsigned = NULL;
}

double Test3::getTdouble(void) const {
    return (tdouble != NULL ? * tdouble : 0.0);
}

void Test3::setTdouble(const double & tdouble_) {
    if (tdouble != NULL) {
        delete tdouble;
    }
    tdouble = new double(tdouble_);
}

bool Test3::isNullTdouble(void) const {
    return (tdouble == NULL);
}

void Test3::setNullTdouble(void) {
    if (tdouble != NULL) {
        delete tdouble;
    }
    tdouble = NULL;
}

double Test3::getTdoubleUnsigned(void) const {
    return (tdoubleUnsigned != NULL ? * tdoubleUnsigned : 0.0);
}

void Test3::setTdoubleUnsigned(const double & tdoubleUnsigned_) {
    if (tdoubleUnsigned != NULL) {
        delete tdoubleUnsigned;
    }
    tdoubleUnsigned = new double(tdoubleUnsigned_);
}

bool Test3::isNullTdoubleUnsigned(void) const {
    return (tdoubleUnsigned == NULL);
}

void Test3::setNullTdoubleUnsigned(void) {
    if (tdoubleUnsigned != NULL) {
        delete tdoubleUnsigned;
    }
    tdoubleUnsigned = NULL;
}

tntdb::Date Test3::getTdate(void) const {
    return (tdate != NULL ? * tdate : tntdb::Date());
}

void Test3::setTdate(const tntdb::Date & tdate_) {
    if (tdate != NULL) {
        delete tdate;
    }
    tdate = new tntdb::Date(tdate_);
}

bool Test3::isNullTdate(void) const {
    return (tdate == NULL);
}

void Test3::setNullTdate(void) {
    if (tdate != NULL) {
        delete tdate;
    }
    tdate = NULL;
}

tntdb::Datetime Test3::getTdatetime(void) const {
    return (tdatetime != NULL ? * tdatetime : tntdb::Datetime());
}

void Test3::setTdatetime(const tntdb::Datetime & tdatetime_) {
    if (tdatetime != NULL) {
        delete tdatetime;
    }
    tdatetime = new tntdb::Datetime(tdatetime_);
}

bool Test3::isNullTdatetime(void) const {
    return (tdatetime == NULL);
}

void Test3::setNullTdatetime(void) {
    if (tdatetime != NULL) {
        delete tdatetime;
    }
    tdatetime = NULL;
}

tntdb::Time Test3::getTtime(void) const {
    return (ttime != NULL ? * ttime : tntdb::Time());
}

void Test3::setTtime(const tntdb::Time & ttime_) {
    if (ttime != NULL) {
        delete ttime;
    }
    ttime = new tntdb::Time(ttime_);
}

bool Test3::isNullTtime(void) const {
    return (ttime == NULL);
}

void Test3::setNullTtime(void) {
    if (ttime != NULL) {
        delete ttime;
    }
    ttime = NULL;
}

std::string Test3::getTchar(void) const {
    return (tchar != NULL ? * tchar : "");
}

void Test3::setTchar(const std::string & tchar_) {
    if (tchar != NULL) {
        delete tchar;
    }
    tchar = new std::string(tchar_);
}

bool Test3::isNullTchar(void) const {
    return (tchar == NULL);
}

void Test3::setNullTchar(void) {
    if (tchar != NULL) {
        delete tchar;
    }
    tchar = NULL;
}

std::string Test3::getTvarchar(void) const {
    return (tvarchar != NULL ? * tvarchar : "");
}

void Test3::setTvarchar(const std::string & tvarchar_) {
    if (tvarchar != NULL) {
        delete tvarchar;
    }
    tvarchar = new std::string(tvarchar_);
}

bool Test3::isNullTvarchar(void) const {
    return (tvarchar == NULL);
}

void Test3::setNullTvarchar(void) {
    if (tvarchar != NULL) {
        delete tvarchar;
    }
    tvarchar = NULL;
}

std::string Test3::getTtext(void) const {
    return (ttext != NULL ? * ttext : "");
}

void Test3::setTtext(const std::string & ttext_) {
    if (ttext != NULL) {
        delete ttext;
    }
    ttext = new std::string(ttext_);
}

bool Test3::isNullTtext(void) const {
    return (ttext == NULL);
}

void Test3::setNullTtext(void) {
    if (ttext != NULL) {
        delete ttext;
    }
    ttext = NULL;
}

tntdb::Blob Test3::getTblob(void) const {
    return (tblob != NULL ? * tblob : tntdb::Blob());
}

void Test3::setTblob(const tntdb::Blob & tblob_) {
    if (tblob != NULL) {
        delete tblob;
    }
    tblob = new tntdb::Blob(tblob_);
}

bool Test3::isNullTblob(void) const {
    return (tblob == NULL);
}

void Test3::setNullTblob(void) {
    if (tblob != NULL) {
        delete tblob;
    }
    tblob = NULL;
}

bool Test3::operator==(const Test3 & other) {
    if (this->tkey1 != other.tkey1) return false;
    if (this->tkey2 != other.tkey2) return false;
    if (this->tsmallint != other.tsmallint) return false;
    if (this->tsmallintUnsigned != other.tsmallintUnsigned) return false;
    if (this->tmediumint != other.tmediumint) return false;
    if (this->tmediumintUnsigned != other.tmediumintUnsigned) return false;
    if (this->tinteger != other.tinteger) return false;
    if (this->tintegerUnsigned != other.tintegerUnsigned) return false;
    if (this->tbigint != other.tbigint) return false;
    if (this->tbigintUnsigned != other.tbigintUnsigned) return false;
    if (this->tdecimal != other.tdecimal) return false;
    if (this->tdecimalUnsigned != other.tdecimalUnsigned) return false;
    if (this->tdec != other.tdec) return false;
    if (this->tdecUnsigned != other.tdecUnsigned) return false;
    if (this->tfixed != other.tfixed) return false;
    if (this->tfixedUnsigned != other.tfixedUnsigned) return false;
    if (this->tfloat != other.tfloat) return false;
    if (this->tfloatUnsigned != other.tfloatUnsigned) return false;
    if (this->tdouble != other.tdouble) return false;
    if (this->tdoubleUnsigned != other.tdoubleUnsigned) return false;
    if (this->tdate != other.tdate) return false;
    if (this->tdatetime != other.tdatetime) return false;
    if (this->ttimestamp != other.ttimestamp) return false;
    if (this->ttime != other.ttime) return false;
    if (this->tchar != other.tchar) return false;
    if (this->tvarchar != other.tvarchar) return false;
    if (this->ttext != other.ttext) return false;
    if (this->tblob != other.tblob) return false;
    return true;
}
