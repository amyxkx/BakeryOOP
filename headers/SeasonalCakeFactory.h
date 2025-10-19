#ifndef SEASONALCAKEFACTORY_H
#define SEASONALCAKEFACTORY_H

#include "ProductFactory.h"
#include "SeasonalSpecialCakes.h"
#include "SeasonalCakePage.h"
#include <memory>
#include <vector>
#include <iostream>

class SeasonalCakeFactory : public ProductFactory {
private:
    std::vector<std::shared_ptr<Product>> getProducts() override;
    std::shared_ptr<Product> cloneProduct(int index);
    void initializeProducts();
    void cloneAllProducts();

    static SeasonalSpecialCake createChristmasCake();
    static SeasonalSpecialCake createEasterCake();
    static SeasonalSpecialCake createNewYearCake();
    static SeasonalSpecialCake createValentinesCake();
    static SeasonalSpecialCake createMothersDayCake();
    static SeasonalSpecialCake createHalloweenCake();

public:
    static std::unique_ptr<SeasonalCakeFactory> create();
    void prepare_cake(Product* product);
    void PrepareSeasonalCakesForOrders();
    ProductPage* getProductPage() override;

    ~SeasonalCakeFactory() override;
};

#endif // SEASONALCAKEFACTORY_H
