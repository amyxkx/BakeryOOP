
#include "Order.h"

int Order::orderCounter = 0;

Order::Order( int ID, std::string Date, std::string payment, Cake ck )
    : DateOfDelivery(Date),
      paymentMethod(payment),
      cake(ck) {
        OrderID=orderCounter++;
};

Order::Order(const Order& other)
    :DateOfDelivery(other.DateOfDelivery),
      paymentMethod(other.paymentMethod),
      cake(other.cake) {
        OrderID=orderCounter++;
};

Order& Order::operator=(const Order &other) {
    if (this != &other) {
        DateOfDelivery=other.DateOfDelivery;
        paymentMethod=other.paymentMethod;
        cake=other.cake;

        OrderID = ++orderCounter;
    }
    return *this;
}

[[nodiscard]] int Order::getOrderID() const  {
    return OrderID;
}

[[nodiscard]] const Cake& Order::getCakeDetails() const {
    return cake;
}

[[nodiscard]] const std::string& Order::getDateOfDelivery() const {
    return DateOfDelivery;
}

[[nodiscard]] const std::string& Order::getPayment() const {
    return paymentMethod;
}

