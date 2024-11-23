#ifndef ORNAMENT_H
#define ORNAMENT_H

#include <string>
#include <ostream>


class Ornament {
    std::string name;
    std::string amountType;
    float weight_piece;
    float amount;
    float price;

public:
    Ornament( std::string n, std::string amntType, float w_piece, float amnt, float p) ;

    Ornament( const Ornament& other) ;

    Ornament& operator=( const Ornament& other) ;

    [[nodiscard]] const std::string& getName() const&;

    [[nodiscard]] const std::string getAmountType() const;

    [[nodiscard]] const float getPieceWeight() const;

    [[nodiscard]] const float getAmount() const;

    [[nodiscard]] const float getPrice() const;



    friend std::ostream& operator<<(std::ostream&os, const Ornament& ornm);
};

#endif