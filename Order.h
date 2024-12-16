#ifndef ORDER_H
#define ORDER_H

#include <string>

#include "Client.h"
#include "Product.h"
#include "Ornament.h"


class Order {
    int OrderID;
    std::string DateOfDelivery;
    std::string paymentMethod;
    static int orderCounter;
    Client client;
    std::vector<std::shared_ptr<Product>>  orderedProduct;
public:
    Order( int ID, std::string Date, std::string payment, Client client );

    Order() = default;

    Order( const Order &other);

    Order& operator=(const Order& other);

    int getOrderID() const;
    const std::string& getDateOfDelivery() const;
    const std::string& getPayment() const;
    void addProduct( std::shared_ptr<Product> PointerProduct);

    float orderFinalPrice() const;


    void clearOrder();

    const std::vector<std::shared_ptr<Product>>& getOrderedProducts() const {
        return orderedProduct;
    }


};

class OrderBuilder {
    int OrderID;
    std::string DateOfDelivery;
    std::string paymentMethod;
    Client client;
    std::vector<std::shared_ptr<Product>> orderedProduct;

public:

    OrderBuilder& setOrderID(int id) {
        OrderID = id;
        return *this;
    }

    OrderBuilder& setDateOfDelivery(const std::string& date) {
        DateOfDelivery = date;
        return *this;
    }

    OrderBuilder& setPaymentMethod(const std::string& payment) {
        paymentMethod = payment;
        return *this;
    }

    OrderBuilder& setClient(const Client& cl) {
        client = cl;
        return *this;
    }

    OrderBuilder& addProduct(const std::shared_ptr<Product>& product) {
        orderedProduct.push_back(product);
        return *this;
    }

    Order build() {
        Order order(OrderID, DateOfDelivery, paymentMethod, client);
        for (const auto& product : orderedProduct) {
            order.addProduct(product);
        }
        return order;
    }
};

#endif //ORDER_H
