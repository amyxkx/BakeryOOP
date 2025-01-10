#include "OrderBuilder.h"
#include "Order.h"
#include <memory>
#include <string>
#include <vector>

OrderBuilder& OrderBuilder::addProduct(const std::shared_ptr<Product>& product) {
    orderedProduct.push_back(product);
    return *this;
}
OrderBuilder& OrderBuilder::setDateOfDelivery(const std::string& date) {
    DateOfDelivery = date;
    return *this;
}

Order OrderBuilder::build() {
    EroareDataInvalida::valideazaData(DateOfDelivery);
    return Order(DateOfDelivery);
}