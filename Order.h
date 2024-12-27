#ifndef ORDER_H
#define ORDER_H

#include <string>

#include "Client.h"
#include "Product.h"
#include "Ornament.h"

class Order {
    std::string DateOfDelivery;
    std::string paymentMethod;
    static int orderCounter;
    Client client;
    std::vector<std::shared_ptr<Product>>  orderedProduct;
public:
    Order( std::string Date, std::string payment, Client client );

    Order() = default;

    Order( const Order &other);

    Order& operator=(const Order& other);

    const std::string& getDateOfDelivery() const;
    const std::string& getPayment() const;
    void addProduct( const std::shared_ptr<Product>& PointerProduct);

    void clearOrder();

    const std::vector<std::shared_ptr<Product>>& getOrderedProducts() const {
        return orderedProduct;
    }

};

#endif //ORDER_H
