#ifndef PRODUCTFACTORY_H
#define PRODUCTFACTORY_H

#include <vector>
#include <memory>
#include "Product.h"
#include "ProductPage.h"

class ProductFactory {
        std::vector<std::shared_ptr<Product>> products;
        ProductPage* productPage;
public:
    virtual std::vector<std::shared_ptr<Product>> getProducts() = 0;
    virtual ProductPage* getProductPage() = 0;
    virtual ~ProductFactory() = default;
};

#endif // PRODUCTFACTORY_H
