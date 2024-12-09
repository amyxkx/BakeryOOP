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

#include <Helper.h>
#include "env_fixes.h" /// NOTE: this include is needed for environment-specific fixes     //
#include <iomanip>  // For std::fixed and std::setprecision
#include <sstream>

void displayDessertCollection(sf::RenderWindow& window, sf::Font& font);
void displayCakesPage(sf::RenderWindow& window, sf::Font& font);
void displaySpecialCakesPage(sf::RenderWindow& window, sf::Font& font);
void displayPastriesPage(sf::RenderWindow& window, sf::Font& font);

class Cakes : public Product {
    std::string FlavorProfile;
    std::string DecorationStyle;
    int days_fresh;
    std::vector<Ornament> ornaments;

public:
    Cakes(int productID, const std::string& productName, const std::string& flavor, const std::string& cream,
         float weight, float basePrice, const std::string& FlavorProfile, const std::string& DecorationStyle,
         int days_fresh, const std::vector<Ornament>& ornaments)
       : Product(productID, productName, flavor, cream, weight, basePrice),  // Parent class initialized first
         FlavorProfile(FlavorProfile), DecorationStyle(DecorationStyle), days_fresh(days_fresh), ornaments(ornaments) {}

    [[nodiscard]] float FinalPrice() const override {
        // Start with base price * weight
        float totalPrice = basePrice * weight;

        // Add the price of each ornament
        for (const auto& ornament : ornaments) {
            totalPrice += ornament.getPrice() * ornament.getAmount();
        }

        return totalPrice;  // Return the total price including ornaments
    }

    // Getter for FlavorProfile
    [[nodiscard]] std::string getFlavorProfile() const {
        return FlavorProfile;
    }

    // Getter for DecorationStyle
    [[nodiscard]] std::string getDecorationStyle() const {
        return DecorationStyle;
    }
    // Getter for days_fresh
    [[nodiscard]] int getDaysFresh() const {
        return days_fresh;
    }
    // Getter for ornaments
    [[nodiscard]] const std::vector<Ornament>& getOrnaments() const {
        return ornaments;
    }


    [[nodiscard]] std::string getName() const {
        return Product::getProductName();
    }

    [[nodiscard]] int getID() const {
        return Product::getProductID();
    }
    static std::vector<Cakes> CakeList;
};

std::vector<Cakes> Cakes::CakeList = {
    Cakes(1, "Chocolate Cake", "Chocolate", "Chocolate Ganache", 3.0f, 80, "Rich and Velvety", "Chocolate Drip with Truffles", 4,ChocolateOrnaments),
    Cakes(2, "Cheesecake", "Biscuit", "Cream Cheese", 2.0f, 70, "Creamy and Smooth", "Fruit Glaze with Fresh Berries", 3, CheesecakeOrnaments),
    Cakes(3, "Lemon Cake", "Vanilla with Lemon", "Lemon Frosting", 2.5f, 80, "Citrusy and Light", "Piped Lemon Frosting", 4, LemonOrnaments ),
    Cakes(4, "Forest Fruit Cake", "Chocolate", "Whipped Cream", 2.0f, 85, "Berry Explosion", "Chocolate Shards with Fresh Fruit", 4, ForestFruitOrnaments),
    Cakes(5, "Strawberry Shortcake", "Vanilla", "Whipped Cream", 3.0f, 90, "Sweet and Fruity", "Whipped Cream and Fresh Strawberries",3, StrawberryShortcakeOrnaments),
    Cakes(6, "Coffee Walnut Cake", "Coffee&Cacao", "Walnut Cream", 3.0f, 90, "Bold and Nutty", "Elegant Coffee Frosting with Walnut Garnish", 4, CoffeeWalnutOrnaments),
};



class SeasonalSpecialCake : public Product{
    std::string SeasonName;
    std::string availabilityToBuy;
    std::string message;

    public:

        SeasonalSpecialCake(const int ID, const std::string& name, const std::string& flavor, const std::string& cream, float weight, float basePrice,
            const std::string& season, const std::string& availabilityDate, const std::string& message)

        : Product(ID, name, flavor, cream, weight, basePrice), SeasonName(season), availabilityToBuy(availabilityDate), message(message) {}


        // Getter for ID (uses Product's getProductID)
        [[nodiscard]] int getID() const {
            return getProductID();  // Calls the inherited getProductID() method
        }

        // Getter for name (uses Product's getProductName)
        [[nodiscard]] std::string getName() const {
            return getProductName();  // Calls the inherited getProductName() method
        }

        [[nodiscard]] float FinalPrice() const override {
            // Get the current date
            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm* localTime = std::localtime(&currentTime);

            // Convert current date to YYYY-MM-DD string
            std::ostringstream currentDateStream;
            currentDateStream << std::put_time(localTime, "%Y-%m-%d");
            std::string currentDate = currentDateStream.str();

            // Convert both dates to tm structures
            std::tm availabilityDate = {};
            std::tm currentTm = {};
            std::istringstream availabilityStream(availabilityToBuy);
            std::istringstream currentStream(currentDate);
            availabilityStream >> std::get_time(&availabilityDate, "%Y-%m-%d");
            currentStream >> std::get_time(&currentTm, "%Y-%m-%d");

            // Compute the difference in days
            auto availabilityTime = std::mktime(&availabilityDate);
            auto currentTimeSec = std::mktime(&currentTm);
            double differenceInDays = std::difftime(availabilityTime, currentTimeSec) / (60 * 60 * 24);


            if (differenceInDays >= 0 && differenceInDays <= 1) {
                return basePrice*weight * 1.5f;
            }

            if (differenceInDays >= 20 && differenceInDays <= 30) {
                return basePrice*weight * 0.8f;
            }

            return basePrice*weight; // No discount
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

    class Pastries : public Product {
        std::string Specific;
        std::string FlavorProfile;
        static int closingHour;

    public:

        Pastries(const int ID, const std::string& name, const std::string& flavor, const std::string& cream,
        float weight_without_ornaments, float price_per_kg, const std::string& specific, const std::string& flavorProfile, float price)
        : Product(ID, name, flavor, cream, weight_without_ornaments, price_per_kg),
          Specific(specific), FlavorProfile(flavorProfile) {}

        [[nodiscard]] std::string getName() const {
            return Product::getProductName();
        }

        [[nodiscard]] int getID() const {
            return Product::getProductID();
        }

        [[nodiscard]] float FinalPrice() const override {
            auto now = std::chrono::system_clock::now(); // Get the current hour
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm* localTime = std::localtime(&currentTime);

            int currentHour = localTime->tm_hour;

            if (closingHour - currentHour == 1) {   // Apply discount if it's one hour before closing
                return basePrice * 0.5f; // 50% off
            }
            return basePrice; // No discount
        }

    };
    int Pastries::closingHour = 20;

std::vector<Pastries> PastriesList= {
    Pastries(1, "Croissant", "Buttery", "Chocolate Cream", 50.0f, 10.0f, "French", "Flaky and buttery", 15.0f),
    Pastries(2, "Baguette", "Wheat", "Garlic&Butter", 20.0f, 2.0f, "French", "Crispy", 10.0f),
    Pastries(3, "Baklava", "Sweet", "Honey", 0.2f, 150.0f, "Turkish", "Nutty and sweet", 10.0f),
    Pastries(4, "Cinnamon Roll", "Cinnamon", "Cream Cheese Frosting", 0.25f, 120.0f, "American", "Soft, sweet, and spiced", 15.0f),
    Pastries(5, "Danish", "Fruity", "Cream cheese", 0.1f, 80.0f, "Danish", "Sweet and creamy", 6.0f),
    Pastries(6, "Eclair", "Vanilla", "Chocolate Glaze", 0.2f, 80.0f, "French", "Creamy and rich", 12.0f)
};


    // class WeddingCake: public Product {
    //     std::string ColourTheme;
    //     std::vector<std::string> WeddingOrnaments;
    //     int guests;
    //     int tiers_number;
    //
    // };
class SomeClass {
public:
    explicit SomeClass(int) {} /// This class is used to test that the memory leak checks work as expected even when using a GUI
};

SomeClass *getC() {
    return new SomeClass{2};
}
//////////////////////////////////////////////////////////////////////

constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;

// Function to create a button
sf::RectangleShape createButton(float x, float y, float width, float height, sf::Color color) {

    sf::RectangleShape button(sf::Vector2f(width, height));

    button.setPosition(x, y);
    button.setFillColor(color);
    return button;
}

// Function to create a text object
sf::Text createText(const std::string& content, const sf::Font& font, unsigned int size, sf::Color color, float x, float y) {

    sf::Text text(content, font, size);

    text.setFillColor(color);
    text.setPosition(x, y);

    return text;
}

// Load a texture and apply it to a sprite
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

// Function to handle the main menu
void displayMainMenu(sf::RenderWindow& window, sf::Font& font) {
    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/background.jpeg")) {
        std::cerr << "Failed to load background image.\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(0.3125f, 0.3125f);  // Scale the background sprite

    // Create welcome text and its shadow
    sf::Text welcomeText = createText("Welcome to Sweet Spell Bakery!", font, 50, sf::Color::White, 200, 50);
    sf::Text welcomeShadow = welcomeText;
    welcomeShadow.setFillColor(sf::Color(139, 69, 19));  // Brown shadow color
    welcomeShadow.setPosition(welcomeText.getPosition().x + 5, welcomeText.getPosition().y + 5);

    // Create the "Our Dessert Collection" button and its text
    sf::RectangleShape viewButton = createButton(100, 300, 280, 100, sf::Color(255, 255, 255, 160));  // Semi-transparent white
    sf::Text viewButtonText = createText("Our Dessert \n Collection", font, 25, sf::Color(139, 69, 19), 160, 310);

    sf::Text viewButtonShadow = viewButtonText;
    viewButtonShadow.setFillColor(sf::Color::White);  // White shadow color
    viewButtonShadow.setPosition(viewButtonText.getPosition().x + 1, viewButtonText.getPosition().y + 3);

        window.clear();
        window.draw(backgroundSprite);

        // Draw welcome text and its shadow
        window.draw(welcomeShadow);
        window.draw(welcomeText);

        // Draw button and its text
        window.draw(viewButton);
        window.draw(viewButtonShadow);
        window.draw(viewButtonText);

        window.display();

    // Event loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (viewButton.getGlobalBounds().contains(mousePos)) {
                    return;  // Exit the main menu and proceed to the dessert collection
                }
            }
        }
    }
}


void displayDessertCollection(sf::RenderWindow& window, sf::Font& font) {
    // Load background texture
    sf::Texture backgroundTexturePage2;
    if (!backgroundTexturePage2.loadFromFile("D:/BakeryOOP/assets/background2.jpeg")) {
        std::cerr << "Failed to load background image.\n";
    }
    sf::Sprite backgroundPage2(backgroundTexturePage2);
    backgroundPage2.setScale(0.3125f, 0.3125f);  // Scale the background sprite

    // Create title text and its shadow
    sf::Text pageTitle = createText("Discover the magic of our \n    Enchanted Desserts!", font, 50, sf::Color::White, 100, 50);
    sf::Text pageTitleShadow = pageTitle;
    pageTitleShadow.setFillColor(sf::Color(139, 69, 19));  // Brown shadow color
    pageTitleShadow.setPosition(pageTitle.getPosition().x + 5, pageTitle.getPosition().y + 5);

    // Define button properties
    sf::RectangleShape cakesButton(sf::Vector2f(320, 70));
    sf::RectangleShape specialCakesButton(sf::Vector2f(320, 70));
    sf::RectangleShape pastriesButton(sf::Vector2f(320, 70));

    cakesButton.setPosition(120, 300);
    specialCakesButton.setPosition(120, 450);
    pastriesButton.setPosition(120, 600);

    cakesButton.setFillColor(sf::Color(0, 0, 0, 170));  // Semi-transparent black
    specialCakesButton.setFillColor(sf::Color(0, 0, 0, 170));
    pastriesButton.setFillColor(sf::Color(0, 0, 0, 170));

    // Create button labels
    sf::Text cakesText = createText("     Delicious Cakes", font, 20, sf::Color::White, 120, 320);
    sf::Text specialCakesText = createText("     Special Seasonal Products", font, 20, sf::Color::White, 120, 470);
    sf::Text pastriesText = createText("     Fresh Pastries", font, 20, sf::Color::White, 120, 620);

    // Function to draw the UI elements
        window.clear();
        window.draw(backgroundPage2);

        // Draw title and shadow
        window.draw(pageTitleShadow);
        window.draw(pageTitle);

        // Draw buttons and their labels
        window.draw(cakesButton);
        window.draw(specialCakesButton);
        window.draw(pastriesButton);
        window.draw(cakesText);
        window.draw(specialCakesText);
        window.draw(pastriesText);

        window.display();

    // Event loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (cakesButton.getGlobalBounds().contains(mousePos)) {
                        displayCakesPage(window, font);

                    } else if (specialCakesButton.getGlobalBounds().contains(mousePos)) {
                        displaySpecialCakesPage(window, font);

                    } else if (pastriesButton.getGlobalBounds().contains(mousePos)) {

                        displayPastriesPage(window, font);
                    }
            }
        }
    }
}

void displayCakeDetailsPage(sf::RenderWindow& window, sf::Font& font, const Cakes& cake);

void displayCakesPage(sf::RenderWindow& window, sf::Font& font) {


    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/PaginaCakes/background.jpeg")) {
        std::cerr << "Failed to load background image.\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(0.472f, 0.469f);  // Scale the background sprite

    // Load cake textures and names

    std::vector<sf::Texture> cakeTextures(Cakes::CakeList.size());
    std::vector<sf::Sprite> cakeSprites(Cakes::CakeList.size());
    std::vector<sf::Text> cakeTexts(Cakes::CakeList.size());

    for (size_t i = 0; i < Cakes::CakeList.size(); ++i) {
        if (!cakeTextures[i].loadFromFile("D:/BakeryOOP/assets/PaginaCakes/" + std::to_string(Cakes::CakeList[i].getID()) + ".jpeg")) {
            std::cerr << "Failed to load image for " << Cakes::CakeList[i].getName() << ".\n";
        }

        // Set up the sprite for each cake
        cakeSprites[i].setTexture(cakeTextures[i]);

        if( i==0 ) cakeSprites[i].setScale(1.3f, 1.3f);
        else
            if( i==1 || i==2 ) cakeSprites[i].setScale(1.0f, 1.0f);
            else
                if( i==3 ) cakeSprites[i].setScale(0.8f, 0.8f);
                else
                    if( i==4) cakeSprites[i].setScale(0.55f, 0.55f);
                    else
                        if( i==5) cakeSprites[i].setScale(0.09f, 0.09f);

        cakeSprites[i].setPosition(
    100.0f + static_cast<float>(i % 3) * 450.0f,
    50.0f + static_cast<float>(i) / 3.0f * 320.0f );



        // Set up the text for each cake
        if( i ==4 || i==5)
        cakeTexts[i] = createText(Cakes::CakeList[i].getName(), font, 20, sf::Color::White,
                                         cakeSprites[i].getPosition().x, cakeSprites[i].getPosition().y + 250);
        else
        cakeTexts[i] = createText(Cakes::CakeList[i].getName(), font, 20, sf::Color::White,
                                  cakeSprites[i].getPosition().x+30, cakeSprites[i].getPosition().y + 250);
    }


    window.draw(backgroundSprite);

        for (size_t i = 0; i < cakeSprites.size(); ++i) {
            window.draw(cakeSprites[i]);
            window.draw(cakeTexts[i]);
        }

        window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (size_t i = 0; i < cakeSprites.size(); ++i) {
                    if (cakeSprites[i].getGlobalBounds().contains(mousePos)) {
                        displayCakeDetailsPage(window, font, Cakes::CakeList[i]); // Display details for the clicked cake
                    }
                }
            }
        }

    }
    };


void displayCakeDetailsPage(sf::RenderWindow& window, sf::Font& font, const Cakes& cake) {
    // Load the background texture based on the cake
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/PaginaCakes/backgrounds/" + std::to_string(cake.getID()) + ".jpg") ) {
        throw std::runtime_error("Failed to load background image");
    }

    sf::RectangleShape textBackground;
    textBackground.setPosition(80, 120); // Adjust position as needed
    textBackground.setSize(sf::Vector2f(700, 500)); // Adjust size as needed

    if( cake.getID() == 1)
        textBackground.setFillColor(sf::Color(0, 0, 0, 130));
    else if( cake.getID() == 2 || cake.getID() == 3 || cake.getID() == 5 )
       textBackground.setFillColor(sf::Color(204, 153, 51, 130));
    else if(cake.getID() == 4 || cake.getID() == 6)
        textBackground.setFillColor(sf::Color(65, 43, 21, 230));

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / static_cast<float>(backgroundTexture.getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(backgroundTexture.getSize().y)
    );

    window.clear();
    window.draw(backgroundSprite);
    window.draw(textBackground );

    sf::Text detailsTitle;
    if( cake.getID() == 1)
        detailsTitle = createText(cake.getName(), font, 50, sf::Color::White, 400, 50);
    else if( cake.getID() == 2 || cake.getID() == 3 || cake.getID() == 5 )
        detailsTitle = createText(cake.getName(), font, 50,sf::Color(204, 153, 51), 400, 50);
    else if(cake.getID() == 4 || cake.getID() == 6)
         detailsTitle = createText(cake.getName(), font, 50, sf::Color(65, 43, 21), 170, 50);
    window.draw(detailsTitle);
        std::vector<sf::Text> details;

        details.push_back(createText("Flavor Profile:     " + cake.getFlavorProfile(), font, 25, sf::Color::White, 100, 150));
        details.push_back(createText("Cream:     " + cake.getCream(), font, 25, sf::Color::White, 100, 200));


    // Format the weight to show 2 decimals
    std::ostringstream ossWeight;
    ossWeight << std::fixed << std::setprecision(2) << cake.getWeight();
    details.push_back(createText("Weight:     " + ossWeight.str() + " kg", font, 25, sf::Color::White, 100, 250));
    // Format the base price to show 2 decimals
    std::ostringstream ossPrice;
    ossPrice << std::fixed << std::setprecision(2) << cake.getBasePrice();
    details.push_back(createText("Base Price (per kg):     " + ossPrice.str() +" ron", font, 25, sf::Color::White, 100, 350));

    std::ostringstream ossOrnaments;
    float yOffset = 390;

    // Iterate through the ornaments and format their prices
    for (const auto& ornament : cake.getOrnaments()) {
        std::ostringstream priceStream;
        priceStream << std::fixed << std::setprecision(2) << ornament.getPrice()*ornament.getPieceWeight();

        details.push_back(createText("- " + ornament.getName() + ": " + priceStream.str() +"ron", font, 20, sf::Color::White, 120, yOffset));
        yOffset += 30;
    }
    details.push_back(createText("Recommended to be consumed in maximum " + std::to_string(cake.getDaysFresh()) + "days ", font, 25, sf::Color::White, 100, 550));

            for (const auto& detail : details) {
                window.draw(detail);
            }

            window.display();

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    return; // Return to the previous page
                }
            }

        }
    };
// Function to display Special Cakes page
void displaySpecialCakesPage(sf::RenderWindow& window, sf::Font& font) {
    window.clear();
sf::Texture backgroundTexture;
if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/PaginaSeasonalCakes/background2.jpg")) {
    std::cerr << "Failed to load background image.\n";
}
sf::Sprite backgroundSprite(backgroundTexture);
backgroundSprite.setScale(2.0f, 2.0f);  // Scale the background sprite

// Load seasonal cake textures and names
std::vector<sf::Texture> cakeTextures(SeasonalSpecialCake::SeasonalCakeList.size());
std::vector<sf::Sprite> cakeSprites(SeasonalSpecialCake::SeasonalCakeList.size());
std::vector<sf::Text> cakeTexts(SeasonalSpecialCake::SeasonalCakeList.size());

for (size_t i = 0; i <SeasonalSpecialCake:: SeasonalCakeList.size(); ++i) {
    if (!cakeTextures[i].loadFromFile("D:/BakeryOOP/assets/PaginaSeasonalCakes/" + std::to_string(SeasonalSpecialCake::SeasonalCakeList[i].getID()) + ".jpg")) {
        std::cerr << "Failed to load image for " << SeasonalSpecialCake::SeasonalCakeList[i].getName() << ".\n";
    }

    // Set up the sprite for each cake
    cakeSprites[i].setTexture(cakeTextures[i]);
    if (i == 0) cakeSprites[i].setScale(0.445f, 0.445f);  // 505x505
    else if (i == 1) cakeSprites[i].setScale(0.197f, 0.197f);  // 1144x1144
    else if (i == 2) cakeSprites[i].setScale(0.422f, 0.422f);  // 532x532
    else if (i == 3) cakeSprites[i].setScale(0.417f, 0.417f);  // 540x540
    else if (i == 4) cakeSprites[i].setScale(0.393f, 0.393f);  // 572x572
    else if (i == 5) cakeSprites[i].setScale(0.255f, 0.255f);  // 881x881


    cakeSprites[i].setPosition(
    100.0f + static_cast<float>(i % 3) * 450.0f, // Floating-point arithmetic for horizontal positioning
    50.0f + static_cast<float>(i) / 3.0f * 320.0f // Explicit floating-point division for vertical positioning
);


    // Set up the text for each cake
    if (i==3 || i == 4 || i == 5)
        cakeTexts[i] = createText(SeasonalSpecialCake::SeasonalCakeList[i].getName(), font, 20, sf::Color::White,
                                  cakeSprites[i].getPosition().x, cakeSprites[i].getPosition().y + 250);
    else
        cakeTexts[i] = createText(SeasonalSpecialCake::SeasonalCakeList[i].getName(), font, 20, sf::Color::White,
                                  cakeSprites[i].getPosition().x + 30, cakeSprites[i].getPosition().y + 250);
}

window.draw(backgroundSprite);

for (size_t i = 0; i < cakeSprites.size(); ++i) {
    window.draw(cakeSprites[i]);
    window.draw(cakeTexts[i]);
}

window.display();

while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
          //  sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
       //     for (size_t i = 0; i < cakeSprites.size(); ++i) {
              //  if (cakeSprites[i].getGlobalBounds().contains(mousePos)) {
                 //   displayCakeDetailsPage(window, font, SeasonalCakes[i]); // Display details for the clicked cake
                }
            }
        }

};

// Function to display Pastries page
void displayPastriesPage(sf::RenderWindow& window, sf::Font& font) {

        window.clear();

        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/PaginaPastries/background.jpg")) {
            std::cerr << "Failed to load background image.\n";
        }

        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(2.0f, 2.0f);

        // Load pastry textures and names
        std::vector<sf::Texture> pastryTextures(PastriesList.size());
        std::vector<sf::Sprite> pastrySprites(PastriesList.size());
        std::vector<sf::Text> pastryTexts(PastriesList.size());

        for (size_t i = 0; i < PastriesList.size(); ++i) {
            if (!pastryTextures[i].loadFromFile("D:/BakeryOOP/assets/PaginaPastries/" + std::to_string(PastriesList[i].getID()) + ".jpg")) {
                std::cerr << "Failed to load image for " << PastriesList[i].getName() << ".\n";
            }

            // Set up the sprite for each pastry
            pastrySprites[i].setTexture(pastryTextures[i]);
            if (i == 0) pastrySprites[i].setScale(0.445f, 0.445f);  // 505x505
            else if (i == 1) pastrySprites[i].setScale(0.197f, 0.197f);  // 1144x1144
            else if (i == 2) pastrySprites[i].setScale(0.422f, 0.422f);  // 532x532
            else if (i == 3) pastrySprites[i].setScale(0.417f, 0.417f);  // 540x540
            else if (i == 4) pastrySprites[i].setScale(0.393f, 0.393f);  // 572x572
            else if (i == 5) pastrySprites[i].setScale(0.255f, 0.255f);  // 881x881

            pastrySprites[i].setPosition(
            100.0f + static_cast<float>(i % 3) * 450.0f,
            50.0f + static_cast<float>(i) / 3.0f * 320.0f );


            if (i == 3 || i == 4 || i == 5)
                pastryTexts[i] = createText(PastriesList[i].getName(), font, 20, sf::Color::White,
                                            pastrySprites[i].getPosition().x, pastrySprites[i].getPosition().y + 250);
            else
                pastryTexts[i] = createText(PastriesList[i].getName(), font, 20, sf::Color::White,
                                            pastrySprites[i].getPosition().x + 30, pastrySprites[i].getPosition().y + 250);
        }

        window.draw(backgroundSprite);

        for (size_t i = 0; i < pastrySprites.size(); ++i) {
            window.draw(pastrySprites[i]);
            window.draw(pastryTexts[i]);
        }

        window.display();

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
               //     sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
            }
}

    };


void printCurrentDateTime() {
    // Get the current time
    auto now = std::chrono::system_clock::now();

    // Convert to time_t to work with calendar times
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert to a tm structure
    std::tm* localTime = std::localtime(&currentTime);

    // Print the date and time
    std::cout << "Current Date and Time: ";
    std::cout << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << '\n';
};

    int main(){
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sweet Spell Bakery");
        sf::Font font;

        if (!font.loadFromFile("D:/BakeryOOP/assets/font/YujiMai.ttf")) {
            std::cerr << "Failed to load font.\n";
            return -1;
        }

        displayMainMenu(window, font);
        displayDessertCollection(window, font);

        init_threads(); // NOTE: this function call is needed for environment-specific fixes
        Helper helper;
        helper.help();

        /// This is needed so we do not burn the GPU
        window.setVerticalSyncEnabled(true);


        printCurrentDateTime();


        return 0;
    }

