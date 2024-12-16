#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include "Ornament.h"
#include "Product.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iomanip>
#include <sstream>

#include "Order.h"

enum class PageState {
    MENU,
    PRODUCT_PAGE,
    PRODUCT_DETAILS,
    WELCOME
};

PageState currentPageState = PageState::MENU;


class Cakes : public Product {
    std::string FlavorProfile;
    std::string DecorationStyle;
    int days_fresh;
    std::vector<Ornament> ornaments;

public:
    Cakes(int productID, const std::string& productName, const std::string& flavor, const std::string& cream,
         float weight, float basePrice, const std::string& FlavorProfile, const std::string& DecorationStyle,
         int days_fresh, const std::vector<Ornament>& ornaments)
       : Product(productID, productName, flavor, cream, weight, basePrice),
         FlavorProfile(FlavorProfile), DecorationStyle(DecorationStyle), days_fresh(days_fresh), ornaments(ornaments) {}

    [[nodiscard]] float FinalPrice() const override {
        float totalPrice = basePrice * weight;

        for (const auto& ornament : ornaments) {
            totalPrice += ornament.getPrice() * ornament.getAmount();
        }

        return totalPrice;
    }

    [[nodiscard]] const std::string& getFlavorProfile() const {
        return FlavorProfile;
    }

    [[nodiscard]] const std::string& getDecorationStyle() const {
        return DecorationStyle;
    }

    [[nodiscard]] int getDaysFresh() const {
        return days_fresh;
    }

    [[nodiscard]] const std::vector<Ornament>& getOrnaments() const {
        return ornaments;
    }


    [[nodiscard]] std::string getName() const {
        return Product::getProductName();
    }

    [[nodiscard]] int getID() const {
        return Product::getProductID();
    }
};


class SeasonalSpecialCake : public Product{
    std::string SeasonName;
    std::string availabilityToBuy;
    std::string message;

    public:

        SeasonalSpecialCake(const int ID, const std::string& name, const std::string& flavor, const std::string& cream, float weight, float basePrice,
            const std::string& season, const std::string& availabilityDate, const std::string& message)

        : Product(ID, name, flavor, cream, weight, basePrice), SeasonName(season), availabilityToBuy(availabilityDate), message(message) {}

        [[nodiscard]] int getID() const {
            return getProductID();
        }

        [[nodiscard]] std::string getName() const {
            return getProductName();
        }

        [[nodiscard]] float FinalPrice() const override {

            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm* const localTime = std::localtime(&currentTime);


            std::ostringstream currentDateStream;
            currentDateStream << std::put_time(localTime, "%Y-%m-%d");
            std::string currentDate = currentDateStream.str();


            std::tm availabilityDate = {};
            std::tm currentTm = {};
            std::istringstream availabilityStream(availabilityToBuy);
            std::istringstream currentStream(currentDate);
            availabilityStream >> std::get_time(&availabilityDate, "%Y-%m-%d");
            currentStream >> std::get_time(&currentTm, "%Y-%m-%d");


            auto availabilityTime = std::mktime(&availabilityDate);
            auto currentTimeSec = std::mktime(&currentTm);
            double differenceInDays = std::difftime(availabilityTime, currentTimeSec) / (60 * 60 * 24);


            if (differenceInDays >= 0 && differenceInDays <= 1) {
                return basePrice*weight * 1.5f;
            }

            if (differenceInDays >= 20 && differenceInDays <= 30) {
                return basePrice*weight * 0.8f;
            }

            return basePrice*weight;
        }
        static std::vector<SeasonalSpecialCake> SeasonalCakeList;
    };


std::vector<SeasonalSpecialCake> SeasonalSpecialCake::SeasonalCakeList {
    SeasonalSpecialCake(1, "Christmas Special", "Vanilla", "Buttercream", 2.0f, 150.0f, "Winter", "2024-12-24", "Merry Christmas!"),
    SeasonalSpecialCake(4, "Easter Special", "Carrot", "Cream Cheese", 1.5f, 120.0f, "Spring", "2024-04-20", "Happy Easter!"),
    SeasonalSpecialCake(3, "New Year's Special", "Chocolate", "Ganache", 2.0f, 150.0f, "Winter", "2024-12-30", "Happy New Year!"),
    SeasonalSpecialCake(2, "Valentine's Day Special", "Red Velvet", "Cream Cheese", 1.9f, 90.0f, "Winter", "2024-02-14", "Happy Valentine's Day!"),
    SeasonalSpecialCake(5, "Mother's Day Special", "Mango", "Coconut Cream", 1.5f, 110.0f, "Spring", "2024-03-08", "Happy Mother's Day!"),
    SeasonalSpecialCake(6, "Halloween Special", "Pumpkin", "Spiced Cream", 2.0f, 140.0f, "Autumn", "2024-10-31", "Happy Halloween!")
};

    class Pastry : public Product {
        std::string Specific;
        std::string FlavorProfile;
        static int closingHour;

    public:

        Pastry(const int ID, const std::string& name, const std::string& flavor, const std::string& cream,
        float weight_without_ornaments, float price_per_kg, const std::string& specific, const std::string& flavorProfile)
        : Product(ID, name, flavor, cream, weight_without_ornaments, price_per_kg),
          Specific(specific), FlavorProfile(flavorProfile) {}

        [[nodiscard]] std::string getName() const {
            return Product::getProductName();
        }

        [[nodiscard]] int getID() const {
            return Product::getProductID();
        }

        [[nodiscard]] const std::string& getSpecific() const {
            return Specific;
        }

        [[nodiscard]] const std::string& getFlavorProfile() const {
            return FlavorProfile;
        }

        [[nodiscard]] float FinalPrice() const override {
            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm* localTime = std::localtime(&currentTime);

            int currentHour = localTime->tm_hour;

            if (closingHour - currentHour == 1) {
                return basePrice * 0.5f; // 50% off
            }
            return basePrice;
        }

    };
    int Pastry::closingHour = 20;

    // class WeddingCake: public Product {
    //     std::string ColourTheme;
    //     std::vector<std::string> WeddingOrnaments;
    //     int guests;
    //     int tiers_number;
    //
    // };

#include <ctime>

constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;
constexpr float BUTTON_WIDTH = 200;
constexpr float BUTTON_HEIGHT = 200;


sf::RectangleShape createButton(float x, float y, float width, float height, sf::Color color) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(color);
    return button;
}


sf::Text createText(const std::string& content, sf::Font const& font, unsigned int size, sf::Color color, float x, float y) {
    sf::Text text(content, font, size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}


sf::Sprite createSprite(const std::string& imagePath, float x, float y) {
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Failed to load image: " << imagePath << '\n';
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    return sprite;
}


class ProductPage {
protected:
    sf::RectangleShape button;
    sf::Text buttonText;
    int basePosition = 300;
    sf::Font font;
    std::string title;
    std::string assets;
public:
    ProductPage(int offsetX, int offsetY, const std::string& buttonText_) {
        if (!font.loadFromFile("D:/BakeryOOP/assets/font/YujiMai.ttf")) {
            std::cerr << "Failed to load font.\n";
            exit(-1);
        }

        button = sf::RectangleShape(sf::Vector2f(320, 70));
        button.setPosition(120, basePosition + 50);
        button.setFillColor(sf::Color(0, 0, 0, 170));
        buttonText.setString(buttonText_);
        buttonText.setFont(font);
        buttonText.setCharacterSize(20);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(140, basePosition + 60);
    }
    std::string getTitle() const {
        return title;
    }

    std::string getButtonText() const {
        return buttonText.getString();
    }

    std::string getAssets() const {
        return assets;
    }

    virtual bool isClicked(sf::RenderWindow& window) {
        return button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }

};


class CakePage : public ProductPage {
public:
    CakePage(int offsetX, int offsetY, const std::string& buttonText_) : ProductPage(offsetX, offsetY, buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaCakes/";
    }
};

class PastryPage : public ProductPage {
public:
    PastryPage(int offsetX, int offsetY, const std::string& buttonText_) : ProductPage(offsetX, offsetY, buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaPastries/";
    }
};

class SeasonalCakePage : public ProductPage {
public:
    SeasonalCakePage(int offsetX, int offsetY, const std::string& buttonText_) : ProductPage(offsetX, offsetY, buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaSeasonalCakes/";
    }

    };

    class ProductFactory {
        std::vector<std::shared_ptr<Product>> products;
        ProductPage* productPage;
    public:
        virtual std::vector<std::shared_ptr<Product>> getProducts() = 0;
        virtual ProductPage* getProductPage() = 0;
        virtual ~ProductFactory() = default;
    };

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
            return new PastryPage(0, 0, "Pastries");
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

    class SeasonalCakeFactory : public ProductFactory {
    public:

        std::vector<std::shared_ptr<Product>> getProducts() override {
            std::vector<std::shared_ptr<Product>> products;
            products.push_back(std::make_shared<SeasonalSpecialCake>(createChristmasCake()));
            products.push_back(std::make_shared<SeasonalSpecialCake>(createEasterCake()));
            products.push_back(std::make_shared<SeasonalSpecialCake>(createHalloweenCake()));
            products.push_back(std::make_shared<SeasonalSpecialCake>(createValentinesCake()));
            products.push_back(std::make_shared<SeasonalSpecialCake>(createMothersDayCake()));
            products.push_back(std::make_shared<SeasonalSpecialCake>(createNewYearCake()));
            return products;
        }


        ProductPage* getProductPage() override {
            std::cout << "Creating Seasonal Cake Page\n";
            return new SeasonalCakePage(0, 0, "Seasonals");
        }

        static SeasonalSpecialCake createChristmasCake() {
            return {1, "Christmas Special", "Vanilla", "Buttercream", 2.0f, 150.0f, "Winter", "2024-12-24", "Merry Christmas!"};
        }

        static SeasonalSpecialCake createEasterCake() {
            return {4, "Easter Special", "Carrot", "Cream Cheese", 1.5f, 120.0f, "Spring", "2024-04-20", "Happy Easter!"};
        }

        static SeasonalSpecialCake createNewYearCake() {
            return {3, "New Year's Special", "Chocolate", "Ganache", 2.0f, 150.0f, "Winter", "2024-12-30", "Happy New Year!"};
        }

        static SeasonalSpecialCake createValentinesCake() {
            return {2, "Valentine's Day Special", "Red Velvet", "Cream Cheese", 1.9f, 90.0f, "Winter", "2024-02-14", "Happy Valentine's Day!"};
        }

        static SeasonalSpecialCake createMothersDayCake() {
            return {5, "Mother's Day Special", "Mango", "Coconut Cream", 1.5f, 110.0f, "Spring", "2024-03-08", "Happy Mother's Day!"};
        }

        static SeasonalSpecialCake createHalloweenCake() {
            return {6, "Halloween Special", "Pumpkin", "Spiced Cream", 2.0f, 140.0f, "Autumn", "2024-10-31", "Happy Halloween!"};
        }

    };


class Menu {
    std::vector<ProductFactory*> factories;
    std::vector<ProductPage*> pages;
    ClientBuilder clientBuilder;
    OrderBuilder orderBuilder;
    Order order;
    sf::RenderWindow window;
    sf::Font font;

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

public:
    Menu(){
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dessert Collection");

        factories.push_back(new CakeFactory);
        factories.push_back(new PastryFactory);
        factories.push_back(new SeasonalCakeFactory);

        for (auto factory: factories) {
            ProductPage *page = factory->getProductPage();
            if (page) {
                pages.push_back(page);
            }
        }

        if (!font.loadFromFile("D:/BakeryOOP/assets/font/YujiMai.ttf")) {
            std::cerr << "Failed to load font.\n";
            exit(-1);
        }
    }


    void displayWelcomePage() {

        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/background.jpeg")) {
            std::cerr << "Failed to load background image.\n"; }

        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(0.3125f, 0.3125f);

        sf::Text welcomeText = createText("Welcome to Sweet Spell Bakery!", font, 50, sf::Color::White, 200, 50);

        sf::Text welcomeShadow = welcomeText;
        welcomeShadow.setFillColor(sf::Color(139, 69, 19));
        welcomeShadow.setPosition(welcomeText.getPosition().x + 5, welcomeText.getPosition().y + 5);

        sf::RectangleShape button = createButton(100, 300, 280, 100, sf::Color(255, 255, 255, 160));
        sf::Text buttonText = createText("Our Dessert \n Collection", font, 25, sf::Color(139, 69, 19), 160, 310);

        sf::Text buttonShadow = buttonText;
        buttonShadow.setFillColor(sf::Color::White);
        buttonShadow.setPosition(buttonText.getPosition().x + 1, buttonText.getPosition().y + 3);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        std::cout << "Button clicked! Transitioning to Menu Page...\n";
                        displayMenuPage();
                    }
                }
            }

            window.clear();
            window.draw(backgroundSprite);

            window.draw(welcomeShadow);
            window.draw(welcomeText);


            window.draw(button);
            window.draw(buttonShadow);
            window.draw(buttonText);

            window.display();
        }
    }
    void displayOrderPage(const Order& order) {


    buttons.clear();
    buttonTexts.clear();


    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/backgroundBasket.jpg")) {
        std::cerr << "Failed to load background image.\n";
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);


    sf::Text pageTitle = createText("Your Order", font, 50, sf::Color(0,0,0), 130, 50);

    int yPos = 150;


        const auto& orderedProducts = order.getOrderedProducts();


        if (orderedProducts.empty()) {
            sf::Text emptyText = createText("Your order is empty.", font, 30, sf::Color::Red, 100, yPos);
            window.draw(emptyText);
        } else {
            for (const auto& product : orderedProducts) {
                if (product != nullptr) {
                    sf::Text productText;
                    productText.setFont(font);
                    productText.setString(product->getProductName());
                    productText.setCharacterSize(25);
                    productText.setFillColor(sf::Color::Black);
                    productText.setPosition(100, yPos);

                    window.draw(productText);
                    yPos += 40; // Mută poziția pentru următorul produs
                }
            }
        }


    sf::RectangleShape finishButton(sf::Vector2f(320, 70));
    finishButton.setPosition(120, 500);
    finishButton.setFillColor(sf::Color(0, 0, 0, 200));
    buttons.push_back(finishButton);


    sf::Text finishButtonText;
    finishButtonText.setString("Finish Order");
    finishButtonText.setFont(font);
    finishButtonText.setCharacterSize(20);
    finishButtonText.setFillColor(sf::Color::White);
    finishButtonText.setPosition(140, 520);
    buttonTexts.push_back(finishButtonText);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {

                if (buttons.back().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Finish Order clicked!" << std::endl;

                    return;
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(pageTitle);

        for (size_t i = 0; i < buttons.size(); ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }

        window.display();
    }
}

    void displayMenuPage() {

        sf::Texture backgroundTexturePage2;
        if (!backgroundTexturePage2.loadFromFile("D:/BakeryOOP/assets/background2.jpeg")) {
            std::cerr << "Failed to load background image.\n";
        }
        sf::Sprite backgroundPage2(backgroundTexturePage2);
        backgroundPage2.setScale(0.3125f, 0.3125f);


        sf::Text pageTitle = createText("Discover the magic of our \n    Enchanted Desserts!", font, 50, sf::Color::White, 100, 50);
        sf::Text pageTitleShadow = pageTitle;
        pageTitleShadow.setFillColor(sf::Color(139, 69, 19));
        pageTitleShadow.setPosition(pageTitle.getPosition().x + 5, pageTitle.getPosition().y + 5);


        buttons.clear();
        buttonTexts.clear();

        int yPos = 300;
        for (auto& factory : factories) {
            if (factory != nullptr) {
                ProductPage* page = factory->getProductPage();
                if (page != nullptr) {

                    sf::RectangleShape button(sf::Vector2f(320, 70));
                    button.setPosition(120, yPos);
                    button.setFillColor(sf::Color(0, 0, 0, 170));
                    buttons.push_back(button);


                    sf::Text buttonText;
                    buttonText.setString(page->getButtonText());
                    buttonText.setFont(font);
                    buttonText.setCharacterSize(20);
                    buttonText.setFillColor(sf::Color::White);
                    buttonText.setPosition(140, yPos + 20);
                    buttonTexts.push_back(buttonText);


                    yPos += 100;
                }
            }
        }
        sf::RectangleShape buttonBasket(sf::Vector2f(120, 120));
        buttonBasket.setPosition(1050, 50);
        sf::Texture textureBasket;

        if (textureBasket.loadFromFile("D:/BakeryOOP/assets/cos.jpg")) {
            buttonBasket.setTexture(&textureBasket);
        } else {
            std::cerr << "Failed to load image for basket"  << "\n";
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {

                    for (size_t i = 0; i < buttons.size(); ++i) {
                        if (buttons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            displayProductPage(i);
                        }
                    }

                    if (buttonBasket.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        std::cout << "Navigating to the order page...\n";
                        displayOrderPage(order);
                    }
                }
            }



            window.clear();
            window.draw(backgroundPage2);
            window.draw(pageTitleShadow);
            window.draw(pageTitle);

            for (size_t i = 0; i < buttons.size(); ++i) {
                window.draw(buttons[i]);
                window.draw(buttonTexts[i]);
            }
            window.draw(buttonBasket);
            window.display();

        }
    }
    void displayProductPage(int index) {
        if (index >= 0 && index < factories.size() && factories[index] != nullptr) {

            std::vector<sf::RectangleShape> buttons;
            std::vector<sf::Text> buttonLabels;

            ProductPage* page = factories[index]->getProductPage();
            if (page == nullptr) {
                std::cerr << "Error: Product page is null.\n";
                return;
            }

            std::vector<std::shared_ptr<Product>> products = factories[index]->getProducts();
            if (products.empty()) {
                std::cerr << "Error: No products available in the factory.\n";
                return;
            }

            for (const auto& product : products) {
                if (product == nullptr) {
                    std::cerr << "Error: Found a null product.\n";
                    continue;
                }
            }

            sf::Texture backgroundTexture;
            if (!backgroundTexture.loadFromFile(page->getAssets() + "background.jpg")) {
                std::cerr << "Failed to load background image.\n";
                return;
            }
            sf::Sprite backgroundSprite(backgroundTexture);

            float horizontalSpacing = (WINDOW_WIDTH - 3 * BUTTON_WIDTH) / 4;
            float verticalSpacing = (WINDOW_HEIGHT - 2 * BUTTON_HEIGHT) / 3;
            std::cout<<"bbb"<<std::endl;
            std::vector<sf::Texture> textures;
            for (size_t i = 0; i < products.size(); ++i) {
                sf::Texture texture;
                textures.push_back(backgroundTexture);
            }

            for (size_t i = 0; i < products.size(); ++i) {

                if (products[i] == nullptr) {
                    std::cerr << "Product at index " << i << " is null!\n";
                    continue;
                }
                std::cout<<i<<std::endl;

                size_t row = i / 3;
                size_t col = i % 3;


                float posX = horizontalSpacing + col * (BUTTON_WIDTH + horizontalSpacing);
                float posY = verticalSpacing + row * (BUTTON_HEIGHT + verticalSpacing);

                sf::RectangleShape button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
                button.setPosition(posX, posY);

                if (textures[i].loadFromFile(page->getAssets() + std::to_string(products[i]->getProductID()) + ".jpg")) {
                    button.setTexture(&textures[i]);
                    std::cout << page->getAssets() + std::to_string(products[i]->getProductID()) + ".jpg" << std::endl;
                } else {
                    std::cerr << "Failed to load image for " << products[i]->getProductName() << "\n";
                }

                buttons.push_back(button);
                std::cout<<i<< " " <<i<<std::endl;

                sf::Text label(products[i]->getProductName(), font, 20);
                label.setFillColor(sf::Color::White);
                label.setPosition(posX + 10, posY + BUTTON_HEIGHT + 5);
                buttonLabels.push_back(label);
            }
            std::vector<std::shared_ptr<Product>> orderedProduct;

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {

                        window.close();
                    }

                    if (event.type == sf::Event::MouseButtonPressed) {
                        for (size_t i = 0; i < buttons.size(); ++i) {
                            if (buttons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {

                                if (i < products.size() && products[i] != nullptr) {

                                    orderBuilder.addProduct(products[i]);
                                    return;
                                }
                            }
                        }

                    }

                }

                window.clear(sf::Color::Black);
                window.draw(backgroundSprite);
                for (auto& label : buttonLabels) {
                    window.draw(label);
                }
                for (auto& button : buttons) {
                    window.draw(button);
                }
                window.display();
            }
        } else {
            std::cerr << "Invalid factory index or null factory pointer.\n";
        }
    }

    void run() {
        displayWelcomePage();
    }

};

void printCurrentDateTime() {

    auto now = std::chrono::system_clock::now();


    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    std::cout << "Current Date and Time: ";
    std::cout << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << '\n';
}


int main() {
    sf::Font font;

    if (!font.loadFromFile("D:/BakeryOOP/assets/font/YujiMai.ttf")) {
        std::cerr << "Failed to load font.\n";
        return -1;
    }

    Menu menu;
    menu.run();
    printCurrentDateTime();


    return 0;
}
