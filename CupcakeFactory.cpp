#include "CupcakeFactory.h"
#include <iostream>
#include <stdexcept>

CupcakeFactory::CupcakeFactory() = default;

std::vector<std::shared_ptr<Product>> CupcakeFactory::getProducts() {
    this->products.push_back(std::make_shared<Cupcake>(createChocolateCupcake()));
    this->products.push_back(std::make_shared<Cupcake>(createVanillaCupcake()));
    this->products.push_back(std::make_shared<Cupcake>(createRedVelvetCupcake()));
    return this->products;
}

std::shared_ptr<Product> CupcakeFactory::cloneProduct(int index) {
    if (index < 0 || index >= static_cast<int>(products.size())) {
        throw std::out_of_range("Invalid index");
    }
    return products[index]->clone();
}

ProductPage* CupcakeFactory::getProductPage() {

    return nullptr;
}

Cupcake CupcakeFactory::createChocolateCupcake() {
    return {1, "Chocolate Cupcake", "Chocolate", "Buttercream", 0.3f, 2.5f, "Chocolate Frosting", "Chocolate Filling", "Sprinkles"};
}

Cupcake CupcakeFactory::createVanillaCupcake() {
    return {2, "Vanilla Cupcake", "Vanilla", "Cream Cheese", 0.25f, 2.0f, "Strawberry Frosting", "Vanilla Filling", "Sugar Pearls"};
}

Cupcake CupcakeFactory::createRedVelvetCupcake() {
    return {3, "Red Velvet Cupcake", "Red Velvet", "Cream Cheese", 0.3f, 3.0f, "Cream Cheese Frosting", "Chocolate Filling", "Chocolate Shavings"};
}

void CupcakeFactory::initializeProducts() {
    cloneAllProducts();
}

void CupcakeFactory::cloneAllProducts() {
    auto cupcakes = getProducts();
    std::vector<std::shared_ptr<Product>> clonedCupcakes;

    for (std::size_t i = 0; i < cupcakes.size(); ++i) {
        try {
            auto clonedCupcake = cloneProduct(i);
            clonedCupcakes.push_back(clonedCupcake);
        } catch (const std::exception& e) {
            std::cerr << "Error cloning cupcake: " << e.what() << std::endl;
        }
    }
}

std::unique_ptr<CupcakeFactory> CupcakeFactory::create() {
    auto factory = std::make_unique<CupcakeFactory>();
    factory->initializeProducts();
    return factory;
}

void CupcakeFactory::prepare_cupcake(Product* product) {
    const Cupcake* cupcake = dynamic_cast<Cupcake*>(product);
    if (cupcake) {
        cupcake->prepare();
    } else {
        std::cout << "Not a cupcake, cannot prepare." << std::endl;
    }
}
// cppcheck-suppress unusedFunction ; false positive
void CupcakeFactory::PrepareCupcakesForOrders() {
    for (auto& product : products) {
        prepare_cupcake(product.get());
    }
}

CupcakeFactory::~CupcakeFactory() = default;
