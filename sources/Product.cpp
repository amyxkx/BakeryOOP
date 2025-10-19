#include "../headers/Product.h"
#include <iostream>

Product::Product(int ID, const std::string& name, const std::string& flv, const std::string& cr, float w, float price)
    : productID(ID), productName(name), flavor(flv), cream(cr), weight(w), basePrice(price) {}

Product::Product(float price)
    : productID(0), productName(""), flavor(""), cream(""), weight(0), basePrice(price) {}

float Product::getBasePrice() const {
    return basePrice*weight;
}

float Product::FinalPrice() const {
    return basePrice*weight;
}

const std::string& Product::getProductName() const {
    return productName;
}

int Product::getProductID() const {
    return productID;
}

