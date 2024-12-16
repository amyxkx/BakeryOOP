
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
    std::string name;
    std::string phoneNumber;
    std::string OrderAddress;
    std::string EmailAddress;

public:
    Client(std::string nm, std::string phone, std::string adrs, std::string email);
    Client() = default;
};

class ClientBuilder {
    std::string name;
    std::string phoneNumber;
    std::string OrderAddress;
    std::string EmailAddress;

public:
    ClientBuilder& setName(const std::string& nm) {
        name = nm;
        return *this;
    }

    ClientBuilder& setPhoneNumber(const std::string& phone) {
        phoneNumber = phone;
        return *this;
    }

    ClientBuilder& setOrderAddress(const std::string& adrs) {
        OrderAddress = adrs;
        return *this;
    }

    ClientBuilder& setEmailAddress(const std::string& email) {
        EmailAddress = email;
        return *this;
    }

    Client build() {
        return Client(this->name, this->phoneNumber, this->OrderAddress, this->EmailAddress);
    }
};
#endif //CLIENT_H
