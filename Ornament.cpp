#include "Ornament.h"
#include <vector>

Ornament::Ornament( std:: string n, std::string amntType, const float amnt, const float w, const float p)
: name(n), amountType( amntType), amount(amnt), weight_piece(w), price(p) {}

Ornament::Ornament(const Ornament& other)
    : name(other.name), amountType(other.amountType), amount(other.amount),
      weight_piece(other.weight_piece), price(other.price) {}


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

 std::string Ornament::getAmountType() const{
    return amountType;
};

 float Ornament::getPieceWeight() const {
    return weight_piece;
};

 float Ornament::getAmount() const {
    return amount;
};

 float Ornament::getPrice() const {
    return price;
};

std::ostream& operator <<( std::ostream& os, const Ornament& ornm) {
    os<< ornm.name<< " ("<<ornm.amountType<<")"<<ornm.amount;

    return os;
}

   // Kilograms
    Ornament Almonds = {"almonds", "kilograms",0.0f, 0.1f, 100.0f};  // Price per kg
    Ornament CaramelFudge = {"caramel fudge", "kilograms",0.0f, 0.25f, 200.0f};  // Price per kg
    Ornament ChocolateBites = {"chocolate bites", "kilograms",0.0f, 0.1f, 80.0f};  // Price per kg
    Ornament ChocolateDrizzle = {"chocolate drizzle", "kilograms",0.0f, 0.1f, 150.0f};  // Price per kg
    Ornament CoconutFlakes = {"coconut flakes", "kilograms",0.0f, 0.1f, 100.0f};  // Price per kg
    Ornament EdibleGlitter = {"edible glitter", "grams", 0.0f,0.01f, 500.0f};  // Price per gram
    Ornament PineappleSlices = {"pineapple slices", "kilograms",0.0f, 0.3f, 60.0f};  // Price per kg
    Ornament Pistachios = {"pistachios", "kilograms", 0.0f,0.3f, 120.0f};  // Price per kg
    Ornament Raspberries = {"raspberries", "kilograms",0.0f, 0.15f, 90.0f};  // Price per kg
    Ornament Strawberries = {"strawberries", "kilograms",0.0f, 0.2f, 75.0f};  // Price per kg
    Ornament WhippedCream = {"whipped cream", "kilograms",0.0f, 0.5f, 30.0f};  // Price per kg
    Ornament LemonSlices = {"lemon slices", "kilograms", 0.0f,0.2f, 75.0f};  // Price per kg
    Ornament MintCream = {"mint cream", "kilograms",0.0f, 0.5f, 30.0f};  // Price per kg
    Ornament Sprinkles = {"sprinkles", "kilograms", 0.0f, 0.05f, 60.0f};  // Price per kg
    Ornament WhiteChocolateShavings = {"white chocolate shavings", "kilograms", 0.0f, 0.15f, 120.0f};  // Price per kg
    Ornament MMs = {"M&Ms", "kilograms",0.0f, 0.1f, 80.0f};
    Ornament Cinnamon = {"cinnamon", "kilograms",0.0f, 0.05f, 60.0f};  // Price per kg
    // Pieces
    Ornament BiscoffCookies = {"Biscoff cookies", "pieces",0.1f, 3.0f, 1.0f};  // Price per piece
    Ornament CandyCanes = {"candy canes", "pieces", 0.1f, 4.0f, 3.0f};  // Price per piece
    Ornament GummyBears = {"gummy bears", "pieces",0.1f, 5.0f, 2.0f};  // Price per piece
    Ornament KinderBueno = {"kinderbueno", "pieces",0.1f, 2.0f, 2.5f};  // Price per piece
    Ornament JellyBeans = {"jelly beans", "pieces",0.1f, 10.0f, 1.0f};  // Price per piece
    Ornament Macarons = {"macarons", "pieces",0.1f, 3.0f, 5.0f};  // Price per piece
    Ornament Marshmallows = {"marshmallows", "pieces",0.1f, 5.0f, 2.0f};  // Price per piece
    Ornament Oreos = {"oreos", "pieces",0.1f, 2.0f, 1.5f};  // Price per piece
    Ornament SugarRoses = {"sugar roses", "pieces",0.1f, 1.0f, 8.0f};  // Price per piece

    std::vector<Ornament> ChocolateOrnaments = {ChocolateBites, ChocolateDrizzle};
    std::vector<Ornament> VanillaOrnaments = {Sprinkles, WhiteChocolateShavings};
    std::vector<Ornament> CarrotOrnaments = {EdibleGlitter, Almonds};
    std::vector<Ornament> CheesecakeOrnaments = {Raspberries, WhippedCream, EdibleGlitter};
    std::vector<Ornament> ForestFruitOrnaments = {Raspberries, Strawberries, PineappleSlices};
    std::vector<Ornament> LemonOrnaments = {SugarRoses, LemonSlices};
    std::vector<Ornament> RedVelvetOrnaments = {EdibleGlitter, SugarRoses};
    std::vector<Ornament> PistachioOrnaments = {Pistachios, WhiteChocolateShavings};
    std::vector<Ornament> TiramisuOrnaments = {ChocolateBites, EdibleGlitter};
    std::vector<Ornament> MangoCoconutOrnaments = {CoconutFlakes, PineappleSlices};
    std::vector<Ornament> StrawberryShortcakeOrnaments = {Raspberries, WhippedCream};
    std::vector<Ornament> ChocolateMintOrnaments = {ChocolateDrizzle, MintCream};
    std::vector<Ornament> CoffeeWalnutOrnaments = {Pistachios, WhiteChocolateShavings};
    std::vector<Ornament> AppleCinnamonOrnaments = {Cinnamon, EdibleGlitter};
    std::vector<Ornament> PineappleUpsideDownOrnaments = {PineappleSlices, WhippedCream};
    std::vector<Ornament> ChurroOrnaments = {Cinnamon, Sprinkles};
    std::vector<Ornament> PeachMelbaOrnaments = {SugarRoses, Raspberries};

