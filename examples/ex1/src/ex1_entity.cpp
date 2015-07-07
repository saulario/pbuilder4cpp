#include "ex1_entity.h"
using namespace ex1::entity;
Country::Country() {
  id = "";
  name = "";
}
Country::~Country() {
}
bool Country::operator == (const Country & other) {
  if (this->id != other.id) return false;
  if (this->name != other.name) return false;
  return true;
}
Customer::Customer() {
  id = 0L;
  name = "";
  countryId = NULL;
  creationDate = tntdb::Date();
}
Customer::~Customer() {
  if (countryId != NULL) {
    delete countryId;
  }
}
std::string Customer::getCountryId(void) const {
  return (countryId != NULL ? * countryId : "");
}
void Customer::setCountryId(const std::string & countryId_) {
  if (countryId != NULL) {
    delete countryId;
  }
  countryId = new std::string(countryId_);
}
bool Customer::isNullCountryId(void) const {
  return (countryId == NULL);
}
void Customer::setNullCountryId(void) {
  if (countryId != NULL) {
    delete countryId;
  }
  countryId = NULL;
}
bool Customer::operator == (const Customer & other) {
  if (this->id != other.id) return false;
  if (this->name != other.name) return false;
  if (this->countryId != other.countryId) return false;
  if (this->creationDate != other.creationDate) return false;
  return true;
}
Something::Something() {
  id = 0L;
  name = "";
  customerId = 0L;
  countryId = "";
}
Something::~Something() {
}
bool Something::operator == (const Something & other) {
  if (this->id != other.id) return false;
  if (this->name != other.name) return false;
  if (this->customerId != other.customerId) return false;
  if (this->countryId != other.countryId) return false;
  return true;
}
