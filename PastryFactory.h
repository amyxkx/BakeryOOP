#ifndef PASTRYFACTORY_H
#define PASTRYFACTORY_H

#include "ProductFactory.h"
#include "Pastry.h"
#include "PastryPage.h"
#include <memory>
#include <vector>

class PastryFactory : public ProductFactory {

    std::vector<std::shared_ptr<Product>> getProducts() override;
    std::shared_ptr<Product> cloneProduct(int index);
    void initializeProducts();
    void cloneAllProducts();

    ProductPage* getProductPage() override;

    static Pastry createCroissant();
    static Pastry createBaguette();
    static Pastry createBaklava();
    static Pastry createCinnamonRoll();
    static Pastry createDanish();
    static Pastry createEclair();

public:
    PastryFactory();
    static std::unique_ptr<PastryFactory> create();

    void prepare_pastry(Product* product);
    void PreparePastriesForOrders();

    ~PastryFactory() override;
};

#endif // PASTRYFACTORY_H
