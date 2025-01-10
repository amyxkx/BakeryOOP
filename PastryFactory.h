#ifndef PASTRYFACTORY_H
#define PASTRYFACTORY_H

#include "ProductFactory.h"
#include "Pastry.h"
#include "PastryPage.h"
#include <memory>
#include <vector>

class PastryFactory : public ProductFactory {
private:
 //   std::vector<std::shared_ptr<Product>> products;

    std::vector<std::shared_ptr<Product>> getProducts() override;
    std::shared_ptr<Product> cloneProduct(int index);

    ProductPage* getProductPage() override;

    static Pastry createCroissant();
    static Pastry createBaguette();
    static Pastry createBaklava();
    static Pastry createCinnamonRoll();
    static Pastry createDanish();
    static Pastry createEclair();

public:
    PastryFactory();
    void initializeProducts();
    void cloneAllProducts();
    static std::unique_ptr<PastryFactory> create();

    void prepare_pastry(Product* product);
    void PreparePastriesForOrders();

    ~PastryFactory() override;
};

#endif // PASTRYFACTORY_H
