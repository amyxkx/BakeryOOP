//
// Created by amalia on 11/25/2024.
//

#include "Client.h"

Client::Client( const Order &ord, std::string nm, std::string phone, std::string adrs, std::string email)
   : order(ord), name(std::move(nm)), phoneNumber(std::move(phone)),
    OrderAddress(std::move(adrs)), EmailAddress(std::move(email)) {}
