#include "PastryFactory.h"
#include <iostream>
#include <stdexcept>

PastryFactory::PastryFactory() = default;

std::vector<std::shared_ptr<Product>> PastryFactory::getProducts() {
    this->products.push_back(std::make_shared<Pastry>(createCroissant()));
    this->products.push_back(std::make_shared<Pastry>(createBaguette()));
    this->products.push_back(std::make_shared<Pastry>(createBaklava()));
    this->products.push_back(std::make_shared<Pastry>(createCinnamonRoll()));
    this->products.push_back(std::make_shared<Pastry>(createDanish()));
    this->products.push_back(std::make_shared<Pastry>(createEclair()));
    return this->products;
}

std::shared_ptr<Product> PastryFactory::cloneProduct(int index) {
    if (index < 0 || index >= static_cast<int>(products.size())) {
        throw std::out_of_range("Index invalid");
    }
    return products[index]->clone();
}

ProductPage* PastryFactory::getProductPage() {
    std::cout << "Creating Pastry Page\n";
    return new PastryPage("Pastries");
}

Pastry PastryFactory::createCroissant() {
    return {1, "Croissant", "Buttery", "Chocolate Cream", 0.0f, 100.0f, "French", "Flaky and buttery"};
}

Pastry PastryFactory::createBaguette() {
    return {2, "Baguette", "Wheat", "Garlic&Butter", 0.40f, 40.0f, "French", "Crispy"};
}

Pastry PastryFactory::createBaklava() {
    return {3, "Baklava", "Sweet", "Honey", 0.2f, 150.0f, "Turkish", "Nutty and sweet"};
}

Pastry PastryFactory::createCinnamonRoll() {
    return {4, "Cinnamon Roll", "Cinnamon", "Cream Cheese Frosting", 0.25f, 120.0f, "American", "Soft, sweet, and spiced"};
}

Pastry PastryFactory::createDanish() {
    return {5, "Danish", "Fruity", "Cream cheese", 0.1f, 80.0f, "Danish", "Sweet and creamy"};
}

Pastry PastryFactory::createEclair() {
    return {6, "Eclair", "Vanilla", "Chocolate Glaze", 0.2f, 80.0f, "French", "Creamy and rich"};
}

void PastryFactory::initializeProducts() {
    cloneAllProducts();
}

void PastryFactory::cloneAllProducts() {
    auto pastries = getProducts();
    std::vector<std::shared_ptr<Product>> clonedPastries;

    for (std::size_t i = 0; i < pastries.size(); ++i) {
        try {
            auto clonedPastry = cloneProduct(i);
            clonedPastries.push_back(clonedPastry);
        } catch (const std::exception& e) {
            std::cerr << "Eroare la clonarea unui produs " << e.what() << std::endl;
        }
    }
}

std::unique_ptr<PastryFactory> PastryFactory::create() {
    auto factory = std::make_unique<PastryFactory>();
    factory->initializeProducts();
    return factory;
}

void PastryFactory::prepare_pastry(Product* product) {
    // Downcast folosind dynamic_cast
    const Pastry* pastry = dynamic_cast<Pastry*>(product);
    if (pastry) {
        pastry->prepare();
    } else {
        std::cout << "Not a pastry, cannot prepare." << std::endl;
    }
}

void PastryFactory::PreparePastriesForOrders() {
    for (auto& product : products) {
        prepare_pastry(product.get());
    }
}

PastryFactory::~PastryFactory() = default;
