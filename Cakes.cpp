#include "Cakes.h"

Cakes::Cakes(int productID, const std::string& productName, const std::string& flavor, const std::string& cream,
             float weight, float basePrice, const std::string& FlavorProfile, const std::string& DecorationStyle,
             int days_fresh, const std::vector<Ornament>& ornaments)
    : Product(productID, productName, flavor, cream, weight, basePrice),
      FlavorProfile(FlavorProfile), DecorationStyle(DecorationStyle), days_fresh(days_fresh), ornaments(ornaments) {}

float Cakes::FinalPrice() const {
    float totalPrice = basePrice * weight;

    for (const auto& ornament : ornaments) {
        totalPrice += ornament.getPrice() * ornament.getPieceWeight();
    }
    if (days_fresh < 2) {
        totalPrice *= 0.9f; // 10% discount
    }

    return totalPrice;
}
Cakes::Cakes(const Cakes& other)
    : Product(other),  FlavorProfile(other.FlavorProfile), DecorationStyle(other.DecorationStyle), days_fresh(other.days_fresh), ornaments(other.ornaments) {}

Cakes& Cakes::operator=(const Cakes& other) {
    if (this != &other) {
       Cakes temp(other);
        swap(*this, temp);
    }
    return *this;
}

void swap(Cakes& first, Cakes& second) noexcept {
    using std::swap;
    swap(first.FlavorProfile, second.FlavorProfile);
    swap(first.DecorationStyle, second.DecorationStyle);
    swap( first.days_fresh, second.days_fresh);
    swap(first.ornaments, second.ornaments);
}
