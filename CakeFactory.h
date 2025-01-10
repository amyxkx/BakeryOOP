#ifndef CAKEFACTORY_H
#define CAKEFACTORY_H

#include "ProductFactory.h"
#include "Cakes.h"
#include "CakePage.h"
#include <memory>
#include <vector>

class CakeFactory : public ProductFactory {

        std::vector<std::shared_ptr<Product>> getProducts() override {

            this->products.push_back(std::make_shared<Cakes>(createChocolateCake()));
            this->products.push_back(std::make_shared<Cakes>(createCheesecake()));
            this->products.push_back(std::make_shared<Cakes>(createLemonCake()));
            this->products.push_back(std::make_shared<Cakes>(createForestFruitCake()));
            this->products.push_back(std::make_shared<Cakes>(createStrawberryShortcake()));
            this->products.push_back(std::make_shared<Cakes>(createCoffeeWalnutCake()));

            return this->products;
        }

        std::shared_ptr<Product> cloneProduct(int index) {
            if (index < 0 || index >= static_cast<int>(products.size())) {
                throw std::out_of_range("Index invalid");
            }
            return products[index]->clone();
        }


        ProductPage* getProductPage() override {
            std::cout << "Creating Cake Page\n";
            return new CakePage( "Cakes");
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

    void initializeProducts() {
            cloneAllProducts();
        }

    void cloneAllProducts() {
            auto cakes = getProducts();
            std::vector<std::shared_ptr<Product>> clonedCakes;

            for (std::size_t i = 0; i < cakes.size(); ++i) {
                try {
                    auto clonedCake = cloneProduct(i);
                    clonedCakes.push_back(clonedCake);
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la clonarea unui tort " << e.what() << std::endl;
                }
            }
        }
public:
    static std::unique_ptr<CakeFactory> create() {
            auto factory = std::make_unique<CakeFactory>();
            factory->initializeProducts();
            return factory;
        }
    void prepare_cake(Product* product) {
            // Downcast folosind dynamic_cast
            const Cakes* cake = dynamic_cast<Cakes*>(product);
            if (cake) {
                cake->prepare();
            } else {
                std::cout << "Not a cake, cannot prepare." << std::endl;
            }
        }

    void PrepareCakesForOrders() {
            for (auto& product : products) {
                prepare_cake(product.get());
            }
        }
    ~CakeFactory() override = default;
    };

#endif // CAKEFACTORY_H