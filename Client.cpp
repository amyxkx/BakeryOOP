#include "Client.h"


Client::Client(std::string nm, std::string phone, std::string adrs, std::string email)
   : name(std::move(nm)), phoneNumber(std::move(phone)),
    OrderAddress(std::move(adrs)), EmailAddress(std::move(email)) {}
