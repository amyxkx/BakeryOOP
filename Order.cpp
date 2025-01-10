#include "Order.h"

#include <utility>

Order::Order( std::string Date, std::string payment, Client client )
    : DateOfDelivery(std::move(Date)), paymentMethod(std::move(payment)), client(std::move(client)) {
};

Order& Order::operator=(const Order &other) {
    if (this != &other) {
        DateOfDelivery=other.DateOfDelivery;
        paymentMethod=other.paymentMethod;

    }
    return *this;
}

void Order::addProduct( const std::shared_ptr<Product>& PointerProduct) {
    this->orderedProduct.push_back(PointerProduct);
}
