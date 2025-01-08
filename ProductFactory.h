#ifndef PRODUCTFACTORY_H
#define PRODUCTFACTORY_H

#include <vector>
#include <memory>
#include "Product.h"
#include "ProductPage.h"

class ProductFactory {

protected:
        std::vector<std::shared_ptr<Product>> products;
      [[maybe_unused]]  ProductPage* productPage;


public:
    ProductFactory()
        : products(), productPage(nullptr) {}

    virtual std::vector<std::shared_ptr<Product>> getProducts() = 0;
    virtual ProductPage* getProductPage() = 0;
    virtual ~ProductFactory() {
        delete productPage;
    }
};

#endif // PRODUCTFACTORY_H
