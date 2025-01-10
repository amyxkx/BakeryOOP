#ifndef CAKES_H
#define CAKES_H

#include "Product.h"
#include "Ornament.h"
#include <string>
#include <vector>

class Cakes : public Product {
    std::string FlavorProfile;
    std::string DecorationStyle;
    int days_fresh;
    std::vector<Ornament> ornaments;

public:
    Cakes(int productID, const std::string& productName, const std::string& flavor, const std::string& cream,
          float weight, float basePrice, const std::string& FlavorProfile, const std::string& DecorationStyle,
          int days_fresh, const std::vector<Ornament>& ornaments);

    [[nodiscard]] float FinalPrice() const override;

    [[nodiscard]] std::shared_ptr<Product> clone() const override {
        return std::make_shared<Cakes>(*this);
    }
    Cakes(const Cakes& other);

    Cakes& operator=(const Cakes& other);

    friend void swap(Cakes& first, Cakes& second) noexcept;

    void prepare() const {
        std::cout << "Preparing the " << getName() <<" cake! " << std::endl;
    }
};

#endif // CAKES_H
