#ifndef ORNAMENT_H
#define ORNAMENT_H

#include <string>
#include <ostream>
#include <vector>


class Ornament {
    std::string name;
    std::string amountType;
    float amount;
    float weight_piece;
    float price;

public:
    Ornament( std::string n, std::string amntType, float amnt, float w_piece, float p) ;

    Ornament( const Ornament& other) ;

    Ornament& operator=( const Ornament& other) ;

    [[nodiscard]] const std::string& getName() const&;

    [[nodiscard]] std::string getAmountType() const;

    [[nodiscard]] float getAmount() const;

    [[nodiscard]] float getPieceWeight() const;

    [[nodiscard]] float getPrice() const;



    friend std::ostream& operator<<(std::ostream&os, const Ornament& ornm);
};
// Kilograms
extern Ornament Almonds;
extern Ornament CaramelFudge;
extern Ornament ChocolateBites;
extern Ornament ChocolateDrizzle;
extern Ornament CoconutFlakes;
extern Ornament EdibleGlitter;
extern Ornament PineappleSlices;
extern Ornament Pistachios;
extern Ornament Raspberries;
extern Ornament Strawberries;
extern Ornament WhippedCream;
extern Ornament LemonSlices;
extern Ornament MintCream;
extern Ornament Sprinkles;
extern Ornament WhiteChocolateShavings;
extern Ornament MMs;
extern Ornament Cinnamon;
// Pieces
extern Ornament BiscoffCookies;
extern Ornament CandyCanes;
extern Ornament GummyBears;
extern Ornament KinderBueno;
extern Ornament JellyBeans;
extern Ornament Macarons;
extern Ornament Marshmallows;
extern Ornament Oreos;
extern Ornament SugarRoses;

extern std::vector<Ornament> ChocolateOrnaments;
extern std::vector<Ornament> VanillaOrnaments;
extern std::vector<Ornament> CarrotOrnaments;
extern std::vector<Ornament> CheesecakeOrnaments;
extern std::vector<Ornament> ForestFruitOrnaments;
extern std::vector<Ornament> LemonOrnaments;
extern std::vector<Ornament> RedVelvetOrnaments;
extern std::vector<Ornament> PistachioOrnaments;
extern std::vector<Ornament> TiramisuOrnaments;
extern std::vector<Ornament> MangoCoconutOrnaments;
extern std::vector<Ornament> StrawberryShortcakeOrnaments;
extern std::vector<Ornament> ChocolateMintOrnaments;
extern std::vector<Ornament> CoffeeWalnutOrnaments;
extern std::vector<Ornament> AppleCinnamonOrnaments;
extern std::vector<Ornament> PineappleUpsideDownOrnaments;
extern std::vector<Ornament> ChurroOrnaments;
extern std::vector<Ornament> PeachMelbaOrnaments;

#endif