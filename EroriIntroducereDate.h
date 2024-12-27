#include "EroareInput.h"
#include <chrono>

#ifndef ERORIINTRODUCEREDATE_H
#define ERORIINTRODUCEREDATE_H

class EroareTelefonInvalid : public EroareInput {

    void valideazaTelefonIntern(const std::string& telefon) {
        int digitCount = 0;

        for (char c : telefon) {
            if (std::isdigit(c)) {
                digitCount++;
            }
        }

        if (digitCount != 10) {
            throw EroareTelefonInvalid();
        }
    }

public:
    // Funcția publică care apelează metoda privată
    void valideazaTelefon(const std::string& telefon) {
        valideazaTelefonIntern(telefon);  // Apelează metoda privată
    }

    const char* what() const noexcept override {
        return "Numarul de telefon trebuie sa contina 10 cifre!";
    }
};

class EroareDataInvalida : public EroareInput {
private:
    void valideazaDataIntern(const std::string& data) {
        const std::regex pattern("^\\d{2}-\\d{2}-\\d{4}$");

        if (!std::regex_match(data, pattern)) {
            throw EroareDataInvalida();
        }

        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* localTime = std::localtime(&currentTime);

        int currentDay = localTime->tm_mday;
        int currentMonth = localTime->tm_mon + 1;
        int currentYear = localTime->tm_year + 1900;

        int day, month, year;
        char separator1, separator2;
        std::istringstream iss(data);
        if (!(iss >> day >> separator1 >> month >> separator2 >> year) ||
            separator1 != '-' || separator2 != '-') {
            throw EroareDataInvalida();
        }

        if (year < currentYear ||
            (year == currentYear && month < currentMonth) ||
            (year == currentYear && month == currentMonth && day < currentDay)) {
            throw EroareDataInvalida();
        }
    }

public:
    void valideazaData(const std::string& data) {
        valideazaDataIntern(data);  // Apelează metoda privată
    }

    const char* what() const noexcept override {
        return "Va rog puneti o data valabila !";
    }
};

class EroareEmailInvalid : public EroareInput {

    void valideazaEmailIntern(const std::string& email) {
        const std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

        if (!std::regex_match(email, pattern)) {
            throw EroareEmailInvalid();
        }
    }

public:
    void valideazaEmail(const std::string& email) {
        valideazaEmailIntern(email);  // Apelează metoda privată
    }

    const char* what() const noexcept override {
        return "Adresa de email introdusă este invalidă!";
    }
};

class EroareNumeInvalid : public EroareInput {

    void valideazaNumeIntern(const std::string& nume) {
        if (nume.length() < 2) {
            throw EroareNumeInvalid();
        }
        for (char c : nume) {
            if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'') {
                throw EroareNumeInvalid();
            }
        }
    }

public:
    void valideazaNume(const std::string& nume) {
        valideazaNumeIntern(nume);  // Apelează metoda privată
    }

    const char* what() const noexcept override {
        return "Numele introdus este invalid!";
    }
};


#endif //ERORIINTRODUCEREDATE_H
