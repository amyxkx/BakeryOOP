#ifndef SEASONAL_SPECIAL_CAKE_H
#define SEASONAL_SPECIAL_CAKE_H

#include "Product.h"
#include <string>

class SeasonalSpecialCake : public Product {
    std::string SeasonName;
    std::string availabilityToBuy;
    std::string message;

public:
    SeasonalSpecialCake(const int ID, const std::string& name, const std::string& flavor, const std::string& cream, float weight, float basePrice,
                        const std::string& season, const std::string& availabilityDate, const std::string& message);

  //  [[nodiscard]] int getID() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] float FinalPrice() const override;
};

#endif // SEASONAL_SPECIAL_CAKE_H
