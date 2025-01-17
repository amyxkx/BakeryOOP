#include "../headers/Client.h"


Client::Client(std::string nm, std::string phone, std::string adrs, std::string email)
   : name(std::move(nm)), phoneNumber(std::move(phone)),
    OrderAddress(std::move(adrs)), EmailAddress(std::move(email)) {}

Client::Client(const Client &other) {
    this->name = other.name;
    this->phoneNumber = other.phoneNumber;
    this->EmailAddress = other.EmailAddress;
}

Client& Client::operator=(const Client& other) {
    if (this != &other) {
        name = other.name;
        phoneNumber = other.phoneNumber;
        OrderAddress = other.OrderAddress;
        EmailAddress = other.EmailAddress;
    }
    return *this;
}