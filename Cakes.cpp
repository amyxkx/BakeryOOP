#include "Cakes.h"

Cakes::Cakes(int productID, const std::string& productName, const std::string& flavor, const std::string& cream,
             float weight, float basePrice, const std::string& FlavorProfile, const std::string& DecorationStyle,
             int days_fresh, const std::vector<Ornament>& ornaments)
    : Product(productID, productName, flavor, cream, weight, basePrice),
      FlavorProfile(FlavorProfile), DecorationStyle(DecorationStyle), days_fresh(days_fresh), ornaments(ornaments) {}

float Cakes::FinalPrice() const {
    float totalPrice = basePrice * weight;

    for (const auto& ornament : ornaments) {
        totalPrice += static_cast<float>(ornament.getPrice() * ornament.getPieceWeight());
    }
    if (days_fresh < 2) {
        totalPrice *= 0.9; // 10% discount
    }

    return totalPrice;
}

