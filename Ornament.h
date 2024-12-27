#ifndef ORNAMENT_H
#define ORNAMENT_H

#include <string>
#include <ostream>
#include <vector>

class Ornament {
    std::string name;
    std::string amountType;
    float weight_piece;
    float price;

public:
    Ornament( std::string n, std::string amntType, float w_piece, float p) ;

    Ornament( const Ornament& other) ;

    Ornament& operator=( const Ornament& other) ;

    [[nodiscard]] const std::string& getName() const&;

    [[nodiscard]] std::string getAmountType() const;

    [[nodiscard]] float getPieceWeight() const;

    [[nodiscard]] float getPrice() const;



friend std::ostream& operator<<(std::ostream&os, const Ornament& ornm);
};
extern std::vector<Ornament> ChocolateOrnaments;
extern std::vector<Ornament> CheesecakeOrnaments;
extern std::vector<Ornament> LemonOrnaments;
extern std::vector<Ornament> ForestFruitOrnaments;
extern std::vector<Ornament> StrawberryShortcakeOrnaments;
extern std::vector<Ornament> CoffeeWalnutOrnaments;

#endif