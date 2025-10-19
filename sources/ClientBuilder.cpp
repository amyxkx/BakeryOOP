#include "../headers/ClientBuilder.h"

#include "../headers/ValidareIntroducereDate.h"


ClientBuilder& ClientBuilder::setName(const std::string& nm) {
    name = nm;
    return *this;
}

ClientBuilder& ClientBuilder::setPhoneNumber(const std::string& phone) {
    phoneNumber = phone;
    return *this;
}

ClientBuilder& ClientBuilder::setOrderAddress(const std::string& address) {
    orderAddress = address;
    return *this;
}

ClientBuilder& ClientBuilder::setEmailAddress(const std::string& email) {
    emailAddress = email;
    return *this;
}

Client ClientBuilder::build() {
    ValidareIntroducereDate::valideazaNume(name);
    ValidareIntroducereDate::valideazaTelefon(phoneNumber);
    ValidareIntroducereDate::valideazaEmail(emailAddress);

    return Client(name, phoneNumber, orderAddress, emailAddress);
}
