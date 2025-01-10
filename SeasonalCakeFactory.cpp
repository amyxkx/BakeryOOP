#include "SeasonalCakeFactory.h"

std::vector<std::shared_ptr<Product>> SeasonalCakeFactory::getProducts() {
    this->products.push_back(std::make_shared<SeasonalSpecialCake>(createChristmasCake()));
    this->products.push_back(std::make_shared<SeasonalSpecialCake>(createEasterCake()));
    this->products.push_back(std::make_shared<SeasonalSpecialCake>(createHalloweenCake()));
    this->products.push_back(std::make_shared<SeasonalSpecialCake>(createValentinesCake()));
    this->products.push_back(std::make_shared<SeasonalSpecialCake>(createMothersDayCake()));
    this->products.push_back(std::make_shared<SeasonalSpecialCake>(createNewYearCake()));
    return this->products;
}

std::shared_ptr<Product> SeasonalCakeFactory::cloneProduct(int index) {
    if (index < 0 || index >= static_cast<int>(products.size())) {
        throw std::out_of_range("Index invalid");
    }
    return products[index]->clone();
}

ProductPage* SeasonalCakeFactory::getProductPage() {
    return new SeasonalCakePage("Seasonals");
}

SeasonalSpecialCake SeasonalCakeFactory::createChristmasCake() {
    return {1, "Christmas Special", "Vanilla", "Buttercream", 2.0f, 150.0f, "Winter", "2024-12-24", "Merry Christmas!"};
}

SeasonalSpecialCake SeasonalCakeFactory::createEasterCake() {
    return {4, "Easter Special", "Carrot", "Cream Cheese", 1.5f, 120.0f, "Spring", "2024-04-20", "Happy Easter!"};
}

SeasonalSpecialCake SeasonalCakeFactory::createNewYearCake() {
    return {3, "New Year's Special", "Chocolate", "Ganache", 2.0f, 150.0f, "Winter", "2024-12-30", "Happy New Year!"};
}

SeasonalSpecialCake SeasonalCakeFactory::createValentinesCake() {
    return {2, "Valentine's Day Special", "Red Velvet", "Cream Cheese", 1.9f, 90.0f, "Winter", "2024-02-14", "Happy Valentine's Day!"};
}

SeasonalSpecialCake SeasonalCakeFactory::createMothersDayCake() {
    return {5, "Mother's Day Special", "Mango", "Coconut Cream", 1.5f, 110.0f, "Spring", "2024-03-08", "Happy Mother's Day!"};
}

SeasonalSpecialCake SeasonalCakeFactory::createHalloweenCake() {
    return {6, "Halloween Special", "Pumpkin", "Spiced Cream", 2.0f, 140.0f, "Autumn", "2024-10-31", "Happy Halloween!"};
}

void SeasonalCakeFactory::initializeProducts() {
    cloneAllProducts();
}

void SeasonalCakeFactory::cloneAllProducts() {
    auto seasonalcakes = getProducts();
    std::vector<std::shared_ptr<Product>> clonedSeasonalCake;

    for (std::size_t i = 0; i < seasonalcakes.size(); ++i) {
        try {
            auto clonedCake = cloneProduct(i);
            clonedSeasonalCake.push_back(clonedCake);
        } catch (const std::exception& e) {
            std::cerr << "Eroare la clonarea unui tort de sezon " << e.what() << std::endl;
        }
    }
}

std::unique_ptr<SeasonalCakeFactory> SeasonalCakeFactory::create() {
    auto factory = std::make_unique<SeasonalCakeFactory>();
    factory->initializeProducts();
    return factory;
}

void SeasonalCakeFactory::prepare_cake(Product* product) {
    const SeasonalSpecialCake* Seasonalcake = dynamic_cast<SeasonalSpecialCake*>(product);
    if (Seasonalcake) {
        Seasonalcake->prepare();
    } else {
        std::cout << "Not a seasonal cake, cannot prepare." << std::endl;
    }
}

void SeasonalCakeFactory::PrepareSeasonalCakesForOrders() {
    for (auto& product : products) {
        prepare_cake(product.get());
    }
}

SeasonalCakeFactory::~SeasonalCakeFactory() = default;
