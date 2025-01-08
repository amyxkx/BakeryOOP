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

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getID() const;
    // [[nodiscard]] const std::string& getSpecific() const;
    // [[nodiscard]] const std::string& getFlavorProfile() const;
    [[nodiscard]] float FinalPrice() const override;
};

#endif // PASTRY_H
