#ifndef ERORIINTRODUCEREDATE_H
#define ERORIINTRODUCEREDATE_H

#include "EroareInput.h"

class EroareTelefonInvalid : public EroareInput {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Numarul de telefon trebuie sa contina 10 cifre!";
    }
};

class EroareDataInvalida : public EroareInput {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Va rog puneti o data valabila !";
    }
};

class EroareEmailInvalid : public EroareInput {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Adresa de email introdusa este invalida!";
    }
};

class EroareNumeInvalid : public EroareInput {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Numele introdus este invalid!";
    }
};

class EroareCampFormGol : public EroareInput {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Numele introdus este invalid!";
    }
};


#endif //ERORIINTRODUCEREDATE_H
