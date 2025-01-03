#include "Ornament.h"
#include <vector>

Ornament::Ornament( std::string n, std::string amntType, const float w, const float p)
: name(n), amountType( amntType), weight_piece(w), price(p) {}

Ornament::Ornament(const Ornament& other)
    : name(other.name), amountType(other.amountType),
      weight_piece(other.weight_piece), price(other.price) {}


Ornament& Ornament::operator=( const Ornament& other) {
    if( this != &other) {
        name=other.name;
        amountType=other.amountType;
        weight_piece=other.weight_piece;
        price=other.price;
    }

    return *this;
};

//  const std::string& Ornament::getName() const& {
//     return name;
// };
//
// const std::string& Ornament::getAmountType() const{
//     return amountType;
// };

 float Ornament::getPieceWeight() const {
    return weight_piece;
};

 float Ornament::getPrice() const {
    return price;
};

std::ostream& operator <<( std::ostream& os, const Ornament& ornm) {
    os<< ornm.name<< " ("<<ornm.amountType<<")";

    return os;
}
Ornament ChocolateShavings = {"chocolate shavings", "kilograms", 0.15f, 100.0f};  // Price per kg
Ornament TrufflePieces = {"truffle pieces", "kilograms", 0.30f, 200.0f};  // Price per kg
Ornament ChocolateDrip = {"chocolate drip", "kilograms", 0.25f, 150.0f};  // Price per kg

Ornament Strawberries = {"strawberries", "kilograms", 0.10f, 50.0f};  // Price per kg
Ornament StrawberryCream = {"strawberry cream", "kilograms", 0.20f, 70.0f};  // Price per kg

Ornament DarkCherries = {"dark cherries", "kilograms", 0.20f, 30.0f};  // Price per kg
Ornament WhippedCream = {"whipped cream", "kilograms", 0.30f, 50.0f};  // Price per kg

Ornament LemonSlices = {"lemon slices", "kilograms", 0.20f, 10.0f};  // Price per kg
Ornament LemonCream = {"lemon cream", "kilograms", 0.30f, 60.0f};  // Price per kg

Ornament MintLeaves = {"mint leaves", "kilograms", 0.02f, 30.0f};  // Price per kg

Ornament Walnuts = {"walnuts", "kilograms", 0.12f, 110.0f};  // Price per kg
Ornament CoffeeBeans = {"coffee beans", "kilograms", 0.20f, 120.0f};  // Price per kg
Ornament CoffeeCream = {"coffee cream", "kilograms", 0.15f, 80.0f};  // Price per kg


std::vector<Ornament> ChocolateOrnaments = { ChocolateShavings, TrufflePieces, ChocolateDrip};
std::vector<Ornament> CheesecakeOrnaments = {Strawberries, StrawberryCream};
std::vector<Ornament> ForestFruitOrnaments = { DarkCherries , ChocolateShavings, WhippedCream};
std::vector<Ornament> LemonOrnaments = { LemonSlices, WhippedCream, LemonCream};
std::vector<Ornament> StrawberryShortcakeOrnaments = { Strawberries, MintLeaves, WhippedCream};
std::vector<Ornament> CoffeeWalnutOrnaments =  { Walnuts, CoffeeBeans, CoffeeCream};

