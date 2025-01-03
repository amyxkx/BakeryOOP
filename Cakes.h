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

    [[nodiscard]] const std::string& getFlavorProfile() const;
    [[nodiscard]] const std::string& getDecorationStyle() const;
    [[nodiscard]] int getDaysFresh() const;
    [[nodiscard]] const std::vector<Ornament>& getOrnaments() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getID() const;

    std::shared_ptr<Product> clone() const override {
        return std::make_shared<Cakes>(*this);
    }
};

#endif // CAKES_H
