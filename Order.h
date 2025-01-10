#ifndef ORDER_H
#define ORDER_H

#include <string>

#include "Client.h"
#include "Product.h"
#include "Ornament.h"

class Order {
    std::string DateOfDelivery;
    static int orderCounter;
    Client client;
    std::vector<std::shared_ptr<Product>>  orderedProduct;

public:
    Order( std::string Date,  Client client );

    Order() = default;

    Order( const Order &other);

    Order& operator=(const Order& other);

    void addProduct( const std::shared_ptr<Product>& PointerProduct);

    void clearOrder();

    [[nodiscard]] const std::vector<std::shared_ptr<Product>>& getOrderedProducts() const {
        return orderedProduct;
    }
    explicit Order(const std::string& date) : DateOfDelivery(date) {}
};

#endif //ORDER_H
