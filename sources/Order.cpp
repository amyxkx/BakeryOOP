#include "../headers/Order.h"

#include <utility>


Order::Order( std::string Date, Client client )
    : DateOfDelivery(std::move(Date)), client(std::move(client)) {
};

void Order::addProduct( const std::shared_ptr<Product>& PointerProduct) {
    this->orderedProduct.push_back(PointerProduct);
}

//https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
//copy-and-swap

Order::Order(const Order &other) : DateOfDelivery(other.DateOfDelivery),
client(other.client), orderedProduct(std::vector<std::shared_ptr<Product>>(other.orderedProduct.size())) {
        for (const auto& product : other.orderedProduct) {
            orderedProduct.push_back(product->clone()); //Facem o copie, deci copiem prin valoare
        }
}

void swap(Order& first, Order& second) {
    using std::swap;
    //aici se face swap la smart pointeri pointeri smart al lui second vor merge in first
    swap(first.orderedProduct, second.orderedProduct);
    // aici nu era necesar, dar am considerat ca este mai frumos
    first.client = second.client;
    first.DateOfDelivery = second.DateOfDelivery;
}

Order& Order::operator=(const Order& other) {
    // se face o copie prin valoaree
    Order temp(other);
    //copiile prin valoare sunt mutate in this
    swap(*this, temp);
    // se apeleaza destructorul lui temp dar vectorul este gol
    return *this;
}


