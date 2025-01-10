#ifndef CAKEFACTORY_H
#define CAKEFACTORY_H

#include "ProductFactory.h"
#include "Cakes.h"
#include "CakePage.h"
#include <memory>
#include <vector>

class CakeFactory : public ProductFactory {
private:
    std::vector<std::shared_ptr<Product>> getProducts() override;
    std::shared_ptr<Product> cloneProduct(int index);
    void initializeProducts();
    void cloneAllProducts();

    static Cakes createChocolateCake();
    static Cakes createCheesecake();
    static Cakes createLemonCake();
    static Cakes createForestFruitCake();
    static Cakes createStrawberryShortcake();
    static Cakes createCoffeeWalnutCake();

public:
    static std::unique_ptr<CakeFactory> create();
    void prepare_cake(Product* product);
    void PrepareCakesForOrders();
    ProductPage* getProductPage() override;


    ~CakeFactory() override;
};

#endif // CAKEFACTORY_H