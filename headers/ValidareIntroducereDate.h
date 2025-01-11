#ifndef VALIDAREINTRODUCEREDATE_H
#define VALIDAREINTRODUCEREDATE_H

#include <chrono>

class ValidareIntroducereDate {
public:
    static void valideazaTelefon(const std::string& telefon);
    static void valideazaData(const std::string& data);
    static void valideazaEmail(const std::string& email);
    static void valideazaNume(const std::string& nume);

private:
    static void valideazaTelefonIntern(const std::string& telefon);
    static void valideazaDataIntern(const std::string& data);
    static void valideazaEmailIntern(const std::string& email);
    static void valideazaNumeIntern(const std::string& nume);
};

#endif //VALIDAREINTRODUCEREDATE_H
