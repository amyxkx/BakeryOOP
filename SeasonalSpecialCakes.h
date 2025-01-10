#ifndef SEASONAL_SPECIAL_CAKE_H
#define SEASONAL_SPECIAL_CAKE_H

#include "Product.h"
#include <string>

class SeasonalSpecialCake : public Product {
    std::string SeasonName;
    std::string availabilityToBuy;
    std::string message;

public:
    SeasonalSpecialCake(int ID, const std::string& name, const std::string& flavor, const std::string& cream, float weight, float basePrice,
                        const std::string& season, const std::string& availabilityDate, const std::string& message);

    [[nodiscard]] float FinalPrice() const override;

    [[nodiscard]] std::shared_ptr<Product> clone() const override {
        return std::make_shared<SeasonalSpecialCake>(*this);
    }
    SeasonalSpecialCake(const SeasonalSpecialCake& other);

    SeasonalSpecialCake& operator=(const SeasonalSpecialCake& other);

    friend void swap(SeasonalSpecialCake& first, SeasonalSpecialCake& second) noexcept;

    void prepare() const {
        std::cout << "Preparing a seasonal special cake! " << std::endl;
    }
};

#endif // SEASONAL_SPECIAL_CAKE_H
