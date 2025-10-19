#include "../headers/Cupcakes.h"

Cupcake::Cupcake(int productID, const std::string& productName, const std::string& flavor, const std::string& cream,
                 float weight, float basePrice, const std::string& frosting, const std::string& filling, const std::string& topping)
    : Product(productID, productName, flavor, cream, weight, basePrice),
      frosting(frosting), filling(filling), topping(topping) {}

float Cupcake::FinalPrice() const {
    float totalPrice = basePrice * weight;

    if (frosting == "Vanilla Frosting") {
        totalPrice += 0.5f;  // Add extra charge for vanilla frosting
    }
    if (topping == "Sprinkles") {
        totalPrice += 0.3f;  // Add extra charge for sprinkles
    }

    return totalPrice;
}

