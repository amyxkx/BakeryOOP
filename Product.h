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
    Product(float price);

    virtual float FinalPrice() const;
    virtual std::shared_ptr<Product> clone() const;

    const std::string& getProductName() const;
    int getProductID() const;
    // const std::string& getFlavor() const;
    // const std::string& getCream() const;
    float getWeight() const;
    float getBasePrice() const;

    virtual ~Product() = default;
};

#endif // PRODUCT_H
