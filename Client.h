
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

    void valideazaNume(const std::string& nume) {
        if (nume.length() < 2) {
            throw EroareNumeInvalid();
        }
        for (char c : nume) {
            if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'') {
                throw EroareNumeInvalid();
            }
        }
    }
    void valideazaEmail(const std::string& email) {
        const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
        if (!std::regex_match(email, pattern)) {
            throw EroareEmailInvalid();
        }
    }

public:
    Client(std::string nm, std::string phone, std::string adrs, std::string email);
    Client() = default;

    void setName(const std::string& nume) {
        valideazaNume(nume);
        name = nume;
    }

    void setEmailAddress(const std::string& email) {
        valideazaEmail(email);
        EmailAddress = email;
    }
};
 #endif //CLIENT_H
