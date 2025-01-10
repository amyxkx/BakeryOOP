#ifndef PASTRY_H
#define PASTRY_H

#include "Product.h"
#include <string>
#include <chrono>

class Pastry : public Product {
    std::string Specific;
    std::string FlavorProfile;
    static int closingHour;

public:
    Pastry(int ID, const std::string& name, const std::string& flavor, const std::string& cream,
           float weight_without_ornaments, float price_per_kg, const std::string& specific, const std::string& flavorProfile);

    [[nodiscard]] float FinalPrice() const override;

    std::shared_ptr<Product> clone() const override {
        return std::make_shared<Pastry>(*this);
    }
    Pastry(const Pastry& other);

    Pastry& operator=(const Pastry& other);

    friend void swap(Pastry& first, Pastry& second) noexcept;

    void prepare() const {
        std::cout << "Preparing the " << getName() <<" pastry! " << std::endl;
    }
};

#endif // PASTRY_H
