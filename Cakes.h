#ifndef CAKES_H
#define CAKES_H

#include "Product.h"
#include "Ornament.h"
#include <string>
#include <vector>

class Cakes : public Product {
    std::string FlavorProfile;
    std::string DecorationStyle;
    int days_fresh;
    std::vector<Ornament> ornaments;

public:
    Cakes(int productID, const std::string& productName, const std::string& flavor, const std::string& cream,
          float weight, float basePrice, const std::string& FlavorProfile, const std::string& DecorationStyle,
          int days_fresh, const std::vector<Ornament>& ornaments);

    [[nodiscard]] float FinalPrice() const override;

};

#endif // CAKES_H
