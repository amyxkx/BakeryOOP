#ifndef PASTRYFACTORY_H
#define PASTRYFACTORY_H

#include "ProductFactory.h"
#include "Pastry.h"
#include "PastryPage.h"
#include <memory>
#include <vector>
class PastryFactory : public ProductFactory {

    public:

        std::vector<std::shared_ptr<Product>> getProducts() override {

            std::vector<std::shared_ptr<Product>> products;
            products.push_back(std::make_shared<Pastry>(createCroissant()));
            products.push_back(std::make_shared<Pastry>(createBaguette()));
            products.push_back(std::make_shared<Pastry>(createBaklava()));
            products.push_back(std::make_shared<Pastry>(createCinnamonRoll()));
            products.push_back(std::make_shared<Pastry>(createDanish()));
            products.push_back(std::make_shared<Pastry>(createEclair()));

            return products;
        }

        ProductPage* getProductPage() override {
            std::cout << "Creating Pastry Page\n";
            return new PastryPage( "Pastries");
        }

        static Pastry createCroissant() {
            return {1, "Croissant", "Buttery", "Chocolate Cream", 0.0f, 100.0f, "French", "Flaky and buttery"};
        }

        static Pastry createBaguette() {
            return {2, "Baguette", "Wheat", "Garlic&Butter", 0.40f, 40.0f, "French", "Crispy"};
        }

        static Pastry createBaklava() {
            return {3, "Baklava", "Sweet", "Honey", 0.2f, 150.0f, "Turkish", "Nutty and sweet"};
        }

        static Pastry createCinnamonRoll() {
            return {4, "Cinnamon Roll", "Cinnamon", "Cream Cheese Frosting", 0.25f, 120.0f, "American", "Soft, sweet, and spiced"};
        }

        static Pastry createDanish() {
            return {5, "Danish", "Fruity", "Cream cheese", 0.1f, 80.0f, "Danish", "Sweet and creamy"};
        }

        static Pastry createEclair() {
            return {6, "Eclair", "Vanilla", "Chocolate Glaze", 0.2f, 80.0f, "French", "Creamy and rich"};
        }

    };


#endif // PASTRYFACTORY_H