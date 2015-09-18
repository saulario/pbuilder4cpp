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
MyCompound::MyCompound() {
  myCustomerId = 0L;
  countryId = "";
  name = "";
}
MyCompound::~MyCompound() {
}
bool MyCompound::operator == (const MyCompound & other) {
  if (this->myCustomerId != other.myCustomerId) return false;
  if (this->countryId != other.countryId) return false;
  if (this->name != other.name) return false;
  return true;
}
MyCustomer::MyCustomer() {
  id = 0L;
  name = "";
  countryId = NULL;
  creationDate = tntdb::Date();
}
MyCustomer::~MyCustomer() {
  if (countryId != NULL) {
    delete countryId;
  }
}
std::string MyCustomer::getCountryId(void) const {
  return (countryId != NULL ? * countryId : "");
}
void MyCustomer::setCountryId(const std::string & countryId_) {
  if (countryId != NULL) {
    delete countryId;
  }
  countryId = new std::string(countryId_);
}
bool MyCustomer::isNullCountryId(void) const {
  return (countryId == NULL);
}
void MyCustomer::setNullCountryId(void) {
  if (countryId != NULL) {
    delete countryId;
  }
  countryId = NULL;
}
bool MyCustomer::operator == (const MyCustomer & other) {
  if (this->id != other.id) return false;
  if (this->name != other.name) return false;
  if (this->countryId != other.countryId) return false;
  if (this->creationDate != other.creationDate) return false;
  return true;
}
Something::Something() {
  id = 0L;
  name = "";
  myCustomerId = 0L;
  countryId = "";
}
Something::~Something() {
}
bool Something::operator == (const Something & other) {
  if (this->id != other.id) return false;
  if (this->name != other.name) return false;
  if (this->myCustomerId != other.myCustomerId) return false;
  if (this->countryId != other.countryId) return false;
  return true;
}
