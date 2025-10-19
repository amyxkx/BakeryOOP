#include "../headers/OrderBuilder.h"
#include "../headers/Order.h"
#include <memory>
#include <string>
#include <vector>

#include "../headers/ValidareIntroducereDate.h"

OrderBuilder& OrderBuilder::addProduct(const std::shared_ptr<Product>& product) {
    orderedProduct.push_back(product);
    return *this;
}
OrderBuilder& OrderBuilder::setDateOfDelivery(const std::string& date) {
    DateOfDelivery = date;
    return *this;
}

Order OrderBuilder::build() {

    ValidareIntroducereDate::valideazaData(DateOfDelivery);
    return Order(DateOfDelivery);

}