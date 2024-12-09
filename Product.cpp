#include "Product.h"

// Constructor implementations
Product::Product(int ID, const std::string& name, const std::string& flv, const std::string& cr, float w, float price)
    : productID(ID), productName(name), flavor(flv), cream(cr), weight(w), basePrice(price) {}

Product::Product(float price)
    : productID(0), productName(""), flavor(""), cream(""), weight(0), basePrice(price) {}

// FinalPrice implementation
float Product::FinalPrice() const {
    return basePrice;
}

// Clone function implementation (this is abstract, so it might return nullptr)
std::shared_ptr<Product> Product::clone() const {
    return nullptr;
}

// Getter implementations
std::string Product::getProductName() const {
    return productName;
}

int Product::getProductID() const {
    return productID;
}

std::string Product::getFlavor() const {
    return flavor;
}

std::string Product::getCream() const {
    return cream;
}

float Product::getWeight() const {
    return weight;
}

float Product::getBasePrice() const {
    return basePrice;
}
