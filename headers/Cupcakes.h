#ifndef CUPCAKES_H
#define CUPCAKES_H

#include "Product.h"
#include <string>

class Cupcake : public Product {
    std::string frosting;
    std::string filling;
    std::string topping;

public:
    Cupcake(int productID, const std::string& productName, const std::string& flavor,
            const std::string& cream, float weight, float basePrice,
            const std::string& frosting, const std::string& filling, const std::string& topping);

    [[nodiscard]] float FinalPrice() const override;

    std::shared_ptr<Product> clone() const override {
        return std::make_shared<Cupcake>(*this);
    }



    void prepare() const {
        std::cout << "Preparing the " << getName() <<" cupcake! " << std::endl;
    }
};

#endif // CUPCAKES_H
