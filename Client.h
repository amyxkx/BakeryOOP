
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

    static void valideazaNume(const std::string& nume) {
        if (nume.length() < 2) {
            throw EroareNumeInvalid();
        }
        for (char c : nume) {
            if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'') {
                throw EroareNumeInvalid();
            }
        }
    }
    static void valideazaEmail(const std::string& email) {
        const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
        if (!std::regex_match(email, pattern)) {
            throw EroareEmailInvalid();
        }
    }

public:
    Client(std::string nm, std::string phone, std::string adrs, std::string email);
    Client() = default;
};
 #endif //CLIENT_H
