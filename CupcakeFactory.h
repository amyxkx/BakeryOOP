#ifndef CUPCAKE_FACTORY_H
#define CUPCAKE_FACTORY_H

#include "Cupcakes.h"
#include "ProductFactory.h"
#include <vector>
#include <memory>

class CupcakeFactory: public ProductFactory {
private:
    std::vector<std::shared_ptr<Product>> getProducts() override;
    std::shared_ptr<Product> cloneProduct(int index);
    void initializeProducts();
    void cloneAllProducts();

    ProductPage* getProductPage() override;

    static Cupcake createChocolateCupcake();
    static Cupcake createVanillaCupcake();
    static Cupcake createRedVelvetCupcake();

public:
    CupcakeFactory();

    static std::unique_ptr<CupcakeFactory> create();
    void prepare_cupcake(Product* product);
    void PrepareCupcakesForOrders();

    ~CupcakeFactory() override;
};

#endif // CUPCAKE_FACTORY_H
