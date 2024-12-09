#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "Product.h"
#include "Ornament.h"


class Order {
    int OrderID;
    std::string DateOfDelivery;
    std::string paymentMethod;
    static int orderCounter;
    std::vector<std::shared_ptr<Product>>  orderedProduct;
public:
    Order( int ID, std::string Date, std::string payment);

    Order( const Order &other);

    Order& operator=(const Order& other);

    int getOrderID() const;
    const std::string& getDateOfDelivery() const;
    const std::string& getPayment() const;
    void addProduct( std::shared_ptr<Product> PointerProduct);

    float orderFinalPrice() const;

};
#endif //ORDER_H
