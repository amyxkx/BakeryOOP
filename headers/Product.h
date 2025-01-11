#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <memory>
#include <iostream>

class Product {
protected:
    int productID;
    std::string productName;
    std::string flavor;
    std::string cream;
    float weight;
    float basePrice;

public:

    Product(int ID, const std::string& name, const std::string& flv, const std::string& cr, float w, float price);
    explicit Product(float price);

    [[nodiscard]] virtual float FinalPrice() const;

    [[nodiscard]] const std::string& getProductName() const;
    [[nodiscard]] int getProductID() const;

    [[nodiscard]] float getBasePrice() const;

    virtual ~Product() = default;

    virtual std::shared_ptr<Product> clone() const=0;

    [[nodiscard]] const std::string& getName() const {
        return productName;
    }
};

#endif // PRODUCT_H
