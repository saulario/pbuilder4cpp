#include "ex1_entity.h"
using namespace ex1::entity;

Compound::Compound() {
    customer_id = 0L;
    country_id = "";
    name = "";
}

Compound::~Compound() {
}

bool Compound::operator==(const Compound & other) {
    if (this->customer_id != other.customer_id) return false;
    if (this->country_id != other.country_id) return false;
    if (this->name != other.name) return false;
    return true;
}

Country::Country() {
    id = "";
    name = "";
}

Country::~Country() {
}

bool Country::operator==(const Country & other) {
    if (this->id != other.id) return false;
    if (this->name != other.name) return false;
    return true;
}

Customer::Customer() {
    id = 0L;
    name = "";
    country_id = NULL;
    creation_date = tntdb::Date();
}

Customer::~Customer() {
    if (country_id != NULL) {
        delete country_id;
    }
}

std::string Customer::getCountry_id(void) const {
    return (country_id != NULL ? * country_id : "");
}

void Customer::setCountry_id(const std::string & country_id_) {
    if (country_id != NULL) {
        delete country_id;
    }
    country_id = new std::string(country_id_);
}

bool Customer::isNullCountry_id(void) const {
    return (country_id == NULL);
}

void Customer::setNullCountry_id(void) {
    if (country_id != NULL) {
        delete country_id;
    }
    country_id = NULL;
}

bool Customer::operator==(const Customer & other) {
    if (this->id != other.id) return false;
    if (this->name != other.name) return false;
    if (this->country_id != other.country_id) return false;
    if (this->creation_date != other.creation_date) return false;
    return true;
}

Something::Something() {
    id = 0L;
    name = "";
    customer_id = 0L;
    country_id = "";
}

Something::~Something() {
}

bool Something::operator==(const Something & other) {
    if (this->id != other.id) return false;
    if (this->name != other.name) return false;
    if (this->customer_id != other.customer_id) return false;
    if (this->country_id != other.country_id) return false;
    return true;
}
