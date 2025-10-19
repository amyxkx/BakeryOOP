#include "../headers/ValidareIntroducereDate.h"
#include "../headers/EroriIntroducereDate.h"
#include <regex>

void ValidareIntroducereDate::valideazaTelefon(const std::string& telefon) {
    valideazaTelefonIntern(telefon);
}

void ValidareIntroducereDate::valideazaTelefonIntern(const std::string& telefon) {
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

void ValidareIntroducereDate::valideazaData(const std::string& data) {
    valideazaDataIntern(data);
}

void ValidareIntroducereDate::valideazaDataIntern(const std::string& data) {
    const std::regex pattern(R"(^\d{2}-\d{2}-\d{4}$)");

    if (!std::regex_match(data, pattern)) {
        throw EroareDataInvalida();
    }

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    const std::tm* localTime = std::localtime(&currentTime);

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

void ValidareIntroducereDate::valideazaEmail(const std::string& email) {
    valideazaEmailIntern(email);
}

void ValidareIntroducereDate::valideazaEmailIntern(const std::string& email) {
    const std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    if (!std::regex_match(email, pattern)) {
        throw EroareEmailInvalid();
    }
}

void ValidareIntroducereDate::valideazaNume(const std::string& nume) {
    valideazaNumeIntern(nume);
}

void ValidareIntroducereDate::valideazaNumeIntern(const std::string& nume) {
    if (nume.length() < 2) {
        throw EroareNumeInvalid();
    }
    for (char c : nume) {
        if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'') {
            throw EroareNumeInvalid();
        }
    }
}
