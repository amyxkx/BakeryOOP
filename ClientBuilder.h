#ifndef CLIENTBUILDER_H
#define CLIENTBUILDER_H

#include "Client.h"

class ClientBuilder {
private:
    std::string name;
    std::string phoneNumber;
    std::string orderAddress;
    std::string emailAddress;

public:
    // Setters pentru fiecare atribut
    ClientBuilder& setName(const std::string& nm);
    ClientBuilder& setPhoneNumber(const std::string& phone);
    ClientBuilder& setOrderAddress(const std::string& address);
    ClientBuilder& setEmailAddress(const std::string& email);

    // Metodă de validare înainte de a construi obiectul Client
    Client build();
};

#endif // CLIENTBUILDER_H
