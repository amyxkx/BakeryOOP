
#include "Order.h"

int Order::orderCounter = 0;

Order::Order( int ID, std::string Date, std::string payment, Client client )
    : DateOfDelivery(Date), paymentMethod(payment), client(client) {
        OrderID=orderCounter++;
};

Order::Order(const Order& other)
    :DateOfDelivery(other.DateOfDelivery), paymentMethod(other.paymentMethod), client(other.client) {
        OrderID=orderCounter++;
};

Order& Order::operator=(const Order &other) {
    if (this != &other) {
        DateOfDelivery=other.DateOfDelivery;
        paymentMethod=other.paymentMethod;

        OrderID = ++orderCounter;
    }
    return *this;
}

[[nodiscard]] int Order::getOrderID() const  {
    return OrderID;
}


[[nodiscard]] const std::string& Order::getDateOfDelivery() const {
    return DateOfDelivery;
}

[[nodiscard]] const std::string& Order::getPayment() const {
    return paymentMethod;
}

void Order::addProduct( std::shared_ptr<Product> PointerProduct) {
    this->orderedProduct.push_back(PointerProduct);
}

float Order::orderFinalPrice() const {
    float finalPrice = 0;

    for( auto & PointerProduct: this->orderedProduct) {
        finalPrice+=PointerProduct->FinalPrice();
    }
}

void Order::clearOrder() {
    orderedProduct.clear();  // Clears the products in the order
}