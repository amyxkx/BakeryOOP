#ifndef CAKE_H
#define CAKE_H

#include <string>
#include <vector>
#include "Ornament.h"

class Cake {
    std::string cakeName;
    std::string flavor;
    std::string cream;
    std::vector<Ornament> ornaments;
    int days_until_expiration;
    float weight_without_ornaments;
    float price_per_kg;

public:
    Cake(const std::string& name, const std::string& flavor, const std::string& cream,
     const std::vector<Ornament>& ornaments, int days_until_expiration, float weight_without_ornaments, float price_per_kg);

    Cake(const Cake& other) = default;
    Cake& operator=(const Cake& other) = default;


    const std::string getCakeName() const;
    const float getWeight() const;
    const float getPrice() const;
    float TotalWeight();
    float FinalPrice();
};



#endif //CAKE_H
