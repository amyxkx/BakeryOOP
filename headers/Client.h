
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <regex>
#include "EroriIntroducereDate.h"

class Client {
    std::string name;
    std::string phoneNumber;
    std::string OrderAddress;
    std::string EmailAddress;

public:

    Client(std::string nm, std::string phone, std::string adrs, std::string email);
    Client() = default;
    Client(const Client &other);

};
 #endif //CLIENT_H
