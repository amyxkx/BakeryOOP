
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Order.h"


class Client {
    Order order;
    std::string name;
    std::string phoneNumber;
    std::string OrderAddress;
    std::string EmailAddress;

public:
    Client( const Order &ord, std::string nm, std::string phone, std::string adrs, std::string email);
};


#endif //CLIENT_H
