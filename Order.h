#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "Cake.h"
#include "Ornament.h"


class Order {
    int OrderID;
    std::string DateOfDelivery;
    std::string paymentMethod;
    Cake cake;
    static int orderCounter;

public:
    Order( int ID, std::string Date, std::string payment, Cake ck );

    Order( const Order &other);

    Order& operator=(const Order& other);

    int getOrderID() const;
    const Cake& getCakeDetails() const;
    const std::string& getDateOfDelivery() const;
    const std::string& getPayment() const;

};
#endif //ORDER_H
