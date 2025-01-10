#ifndef ORDER_BUILDER_H
#define ORDER_BUILDER_H

#include "Order.h"
#include <memory>
#include <string>
#include <vector>

class OrderBuilder {
    std::string DateOfDelivery;
    Client client;
    std::vector<std::shared_ptr<Product>> orderedProduct;

public:

    OrderBuilder& setDateOfDelivery(const std::string& date);
    OrderBuilder& addProduct(const std::shared_ptr<Product>& product);
    Order build();
};

#endif // ORDER_BUILDER_H
