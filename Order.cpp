#include "Order.h"

#include <utility>


Order::Order( std::string Date, Client client )
    : DateOfDelivery(std::move(Date)), client(std::move(client)) {
};

Order& Order::operator=(const Order &other) {
    if (this != &other) {
        DateOfDelivery=other.DateOfDelivery;
    }
    return *this;
}

void Order::addProduct( const std::shared_ptr<Product>& PointerProduct) {
    this->orderedProduct.push_back(PointerProduct);
}
