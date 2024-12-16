//
// Created by amalia on 12/16/2024.
//

#ifndef EROARENUMARTELEFON_H
#define EROARENUMARTELEFON_H

class EroareNumarTelefon : public EroareInput {
public:
    const char* what() const noexcept override {
        return "A fost introdus altceva inafara unui cifre!";
    }
};

class EroareMaiMultDe10Cifre : public EroareInput {
public:
    const char* what() const noexcept override {
        return "Numarul de telefon contine mai mult de 10 cifre!";
    }
};

class EroareData : public EroareInput {
public:
    const char* what() const noexcept override {
        return "Va rog puneti o data valabila (dupa azi)!";
    }
};


#endif //EROARENUMARTELEFON_H
