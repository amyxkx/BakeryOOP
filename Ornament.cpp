#include "Ornament.h"


Ornament::Ornament( std:: string n, std::string amntType, const float amnt, const float w, const float p)
: name(n), amount(amnt), weight_piece(w), price(p) {}

Ornament& Ornament::operator=( const Ornament& other) {
    if( this != &other) {
        name=other.name;
        amountType=other.amountType;
        amount=other.amount;
        weight_piece=other.weight_piece;
        price=other.price;
    }

    return *this;
};

const std::string& Ornament::getName() const& {
    return name;
};

const std::string Ornament::getAmountType() const{
    return amountType;
};

const float Ornament::getPieceWeight() const {
    return weight_piece;
};

const float Ornament::getAmount() const {
    return amount;
};

const float Ornament::getPrice() const {
    return price;
};

std::ostream& operator <<( std::ostream& os, const Ornament& ornm) {
    os<< ornm.name<< " ("<<ornm.amountType<<")"<<ornm.amount;

    return os;
}


