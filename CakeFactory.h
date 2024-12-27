#ifndef CAKEFACTORY_H
#define CAKEFACTORY_H

#include "ProductFactory.h"
#include "Cakes.h"
#include "CakePage.h"
#include <memory>
#include <vector>

class CakeFactory : public ProductFactory {

public:
        std::vector<std::shared_ptr<Product>> getProducts() override {

            std::vector<std::shared_ptr<Product>> products;

            products.push_back(std::make_shared<Cakes>(createChocolateCake()));
            products.push_back(std::make_shared<Cakes>(createCheesecake()));
            products.push_back(std::make_shared<Cakes>(createLemonCake()));
            products.push_back(std::make_shared<Cakes>(createForestFruitCake()));
            products.push_back(std::make_shared<Cakes>(createStrawberryShortcake()));
            products.push_back(std::make_shared<Cakes>(createCoffeeWalnutCake()));

            return products;
        }

        ProductPage* getProductPage() override {
            std::cout << "Creating Cake Page\n";
            return new CakePage(0, 0, "Cakes");
        }

        static Cakes createChocolateCake() {
            return {1, "Chocolate Cake", "Chocolate", "Chocolate Ganache", 3.0f, 80, "Rich and Velvety", "Chocolate Drip with Truffles", 4, ChocolateOrnaments};
        }

        static Cakes createCheesecake() {
            return {2, "Cheesecake", "Biscuit", "Cream Cheese", 2.0f, 70, "Creamy and Smooth", "Fruit Glaze with Fresh Berries", 3, CheesecakeOrnaments};
        }

        static Cakes createLemonCake() {
            return {3, "Lemon Cake", "Vanilla with Lemon", "Lemon Frosting", 2.5f, 80, "Citrusy and Light", "Piped Lemon Frosting", 4, LemonOrnaments};
        }

        static Cakes createForestFruitCake() {
            return {4, "Forest Fruit Cake", "Chocolate", "Whipped Cream", 2.0f, 85, "Berry Explosion", "Chocolate Shards with Fresh Fruit", 4, ForestFruitOrnaments};
        }

        static Cakes createStrawberryShortcake() {
            return {5, "Strawberry Shortcake", "Vanilla", "Whipped Cream", 3.0f, 90, "Sweet and Fruity", "Whipped Cream and Fresh Strawberries", 3, StrawberryShortcakeOrnaments};
        }

        static Cakes createCoffeeWalnutCake() {
            return {6, "Coffee Walnut Cake", "Coffee&Cacao", "Walnut Cream", 3.0f, 90, "Bold and Nutty", "Elegant Coffee Frosting with Walnut Garnish", 4, CoffeeWalnutOrnaments};
        }
    };

#endif // CAKEFACTORY_H