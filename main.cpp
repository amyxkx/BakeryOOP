#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Product.h"
#include "Order.h"
#include "ProductPage.h"
#include "PastryFactory.h"
#include "CakeFactory.h"
#include "SeasonalCakeFactory.h"

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

class Menu {
    std::vector<ProductFactory*> factories;
    std::vector<ProductPage*> pages;
    //ClientBuilder clientBuilder;
    //OrderBuilder orderBuilder;
    Order order;
    sf::RenderWindow window;
    sf::Font font;

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

public:

    Menu() : order() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dessert Collection");

        factories.push_back(new CakeFactory);
        factories.push_back(new PastryFactory);
        factories.push_back(new SeasonalCakeFactory);

        for (auto factory : factories) {
            if (auto* page = factory->getProductPage()) { // Declare and assign 'page' inside the if-statement
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
            sf::Event event = sf::Event();
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

void displayOrderPage(const Order& localorder) {
    buttons.clear();
    buttonTexts.clear();
    window.clear();

    sf::Texture backgroundOrder;
    if (!backgroundOrder.loadFromFile("D:/BakeryOOP/assets/client/backgroundOrder.jpg")) {
        std::cerr << "Failed to load background image.\n";
        return;
    }
    sf::Sprite backgroundSprite(backgroundOrder);

    sf::Text pageTitle = createText("Order Summary", font, 50, sf::Color(0, 0, 0), 400, 50);
    sf::Text pageTitleShadow = pageTitle;
    pageTitleShadow.setFillColor(sf::Color(139, 69, 19));
    pageTitleShadow.setPosition(pageTitle.getPosition().x + 5, pageTitle.getPosition().y + 5);

    float yPos = 150;
    float costOfOrder=0;

    const auto& orderedProduct = localorder.getOrderedProducts();
        std::cout << "Ordered Products: " << std::endl;
        for (const auto& product : orderedProduct) {
            if (product != nullptr) {
                std::cout << product->getProductName() << " " << product->FinalPrice()<< "ron "<<std::endl;
                costOfOrder+=product->FinalPrice();
            }
        }

    std::cout <<"Price for the order: "<<costOfOrder<< std::endl;

    if (orderedProduct.empty()) {
        sf::Text emptyText = createText("Your order is empty.", font, 30, sf::Color::Red, 100, yPos);
        window.draw(emptyText);
    }

    std::ostringstream formattedPrice;
    formattedPrice.precision(2); formattedPrice << std::fixed << costOfOrder;

    sf::Text priceOfOrder;
    priceOfOrder.setFont(font);
    priceOfOrder.setPosition(120, 610);
    priceOfOrder.setFillColor(sf::Color(0,0,0));

    priceOfOrder.setString("Order Price: " + formattedPrice.str() + " ron");

    sf::RectangleShape Background(sf::Vector2f(1100, 550));
    Background.setPosition( 100, 130);
    Background.setFillColor(sf::Color(255,255,255,160) );

    sf::RectangleShape finishButton(sf::Vector2f(280, 70));
    finishButton.setPosition(700, 600);
    finishButton.setFillColor(sf::Color(0, 0, 0, 200));
    buttons.push_back(finishButton);

    sf::Text finishButtonText;
    finishButtonText.setString("Finish Order");
    finishButtonText.setFont(font);
    finishButtonText.setCharacterSize(20);
    finishButtonText.setFillColor(sf::Color::White);
    finishButtonText.setPosition(750, 620);
    buttonTexts.push_back(finishButtonText);

    while (window.isOpen()) {
        sf::Event event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (buttons.back().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                std::cout << "Finish Order clicked! Proceeding to details page...\n";
                displayDetailsPage();
                return;
            }
        }
        window.clear();
        window.draw(backgroundSprite);
        window.draw(pageTitleShadow);
        window.draw(pageTitle);
        window.draw(Background);

        for (size_t i = 0; i < buttons.size(); ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        yPos=150;
        for (const auto& product : orderedProduct) {
            if (product != nullptr) {

                sf::Text productText;
                productText.setFont(font);
                productText.setString(product->getProductName());
                productText.setCharacterSize(25);
                productText.setFillColor(sf::Color::Black);
                productText.setPosition(430, yPos);
                yPos += 50;
                window.draw(productText);

            }
        }
        window.draw(priceOfOrder);
        window.display();
    }
}

void displayDetailsPage() {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/BakeryOOP/assets/client/backgroundClient.jpg")) {
        std::cerr << "Failed to load background image.\n";
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Text pageTitle = createText("Finish order", font, 50, sf::Color(0, 0, 0), 500, 50);
    sf::Text pageTitleShadow = pageTitle;
    pageTitleShadow.setFillColor(sf::Color(139, 69, 19));
    pageTitleShadow.setPosition(pageTitle.getPosition().x + 5, pageTitle.getPosition().y + 5);

    sf::Text errorMessage;
    errorMessage.setFont(font);
    errorMessage.setCharacterSize(30);
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition(350, 620);

    sf::RectangleShape Background(sf::Vector2f(1000, 500));
    Background.setPosition( 150, 130);
    Background.setFillColor(sf::Color(255,255,255,160) );

    std::string nameInput, addressInput, phoneInput, emailInput, dateInput;
    sf::Text nameLabel = createText("Name:", font, 30, sf::Color::Black, 200, 150);
    sf::Text addressLabel = createText("Delivery Address :", font, 30, sf::Color::Black, 200, 230);
    sf::Text phoneLabel = createText("Phone:", font, 30, sf::Color::Black, 200, 310);
    sf::Text emailLabel = createText("Email", font, 30, sf::Color::Black, 200, 390);
    sf::Text textemail = createText("(****@****.***)", font, 20, sf::Color::Black, 200, 430);
    sf::Text dateLabel = createText("Delivery date:", font, 30, sf::Color::Black, 200, 500);
    sf::Text textdate = createText("(DD-MM-YYYY)", font, 20, sf::Color::Black, 200, 540);

    sf::Text nameField = createText("", font, 25, sf::Color::Black, 400, 150);
    sf::Text addressField = createText("", font, 25, sf::Color::Black, 500, 230);
    sf::Text phoneField = createText("", font, 25, sf::Color::Black, 400, 310);
    sf::Text emailField = createText("", font, 25, sf::Color::Black, 400, 390);
    sf::Text dateField = createText("", font, 25, sf::Color::Black, 500, 500);

    sf::RectangleShape finishButton(sf::Vector2f(200, 70));
    finishButton.setPosition(540, 550);
    finishButton.setFillColor(sf::Color(0, 0, 0, 200));

    sf::Text finishText = createText("Submit", font, 25, sf::Color::White, 575, 565);

    int activeField = 0;

    while (window.isOpen()) {
        sf::Event event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                char inputChar = static_cast<char>(event.text.unicode);
                if (std::isprint(inputChar)) {
                    if (activeField == 0)
                        nameInput += inputChar;
                    else if (activeField == 1)
                        addressInput += inputChar;
                    else if (activeField == 2)
                        phoneInput += inputChar;
                    else if (activeField == 3)
                        emailInput += inputChar;
                    else if (activeField == 4)
                        dateInput += inputChar;
                } else if (inputChar == '\b') {
                    if (activeField == 0 && !nameInput.empty())
                        nameInput.pop_back();
                    else if (activeField == 1 && !addressInput.empty())
                        addressInput.pop_back();
                    else if (activeField == 2 && !phoneInput.empty())
                        phoneInput.pop_back();
                    else if (activeField == 3 && !emailInput.empty())
                        emailInput.pop_back();
                    else if (activeField == 4 && !dateInput.empty())
                        dateInput.pop_back();
                }
            }
            bool isFormValid = false;

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    activeField = (activeField + 1) % 5;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    try {
                        if (nameInput.empty() || phoneInput.empty() || emailInput.empty() || dateInput.empty()) {
                            throw std::runtime_error("All fields must be filled!");
                        }

                        EroareNumeInvalid numeValidator;
                        EroareNumeInvalid::valideazaNume(nameInput);

                        EroareTelefonInvalid telefonValidator;
                        EroareTelefonInvalid::valideazaTelefon(phoneInput);

                        EroareEmailInvalid emailValidator;
                        EroareEmailInvalid::valideazaEmail(emailInput);

                        EroareDataInvalida dataValidator;
                        EroareDataInvalida::valideazaData(dateInput);

                        isFormValid = true;
                        errorMessage.setString("");

                        std::cout << "Order Completed:\n";
                        std::cout << "Name: " << nameInput << "\n";
                        std::cout << "Address: " << addressInput << "\n";
                        std::cout << "Phone: " << phoneInput << "\n";
                        std::cout << "Email: " << emailInput << "\n";
                        std::cout << "Date: " << dateInput << "\n";
                        return;

                    } catch (const EroareNumeInvalid& e) {
                        errorMessage.setString(e.what());  isFormValid = false;
                    } catch (const EroareTelefonInvalid& e) {
                        errorMessage.setString(e.what());  isFormValid = false;
                    } catch (const EroareEmailInvalid& e) {
                        errorMessage.setString(e.what());  isFormValid = false;
                    } catch (const EroareDataInvalida& e) {
                        errorMessage.setString(e.what());  isFormValid = false;
                    } catch (const std::runtime_error& e) {
                        errorMessage.setString(e.what());  isFormValid = false;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (finishButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    try {
                        if (!isFormValid) {
                            throw std::runtime_error("         Form was completed wrong! \nPlease correct the errors before submitting.");
                        }
                    }catch (const std::runtime_error& e) {
                        std::cout << e.what() << std::endl;
                        errorMessage.setString(e.what());
                    }
                }
            }
        }
        nameField.setString(nameInput);
        addressField.setString(addressInput);
        phoneField.setString(phoneInput);
        emailField.setString(emailInput);
        dateField.setString(dateInput);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(Background);
        window.draw(pageTitleShadow);
        window.draw(pageTitle);

        window.draw(nameLabel);
        window.draw(addressLabel);
        window.draw(phoneLabel);
        window.draw(emailLabel);
        window.draw(textemail);
        window.draw(dateLabel);
        window.draw(textdate);

        window.draw(nameField);
        window.draw(addressField);
        window.draw(phoneField);
        window.draw(emailField);
        window.draw(dateField);

        window.draw(finishButton);
        window.draw(finishText);

        window.draw(errorMessage);

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

        float yPos = 300;
        for (auto& factory : factories) {
            if (factory != nullptr) {
               const ProductPage* page = factory->getProductPage();
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
            sf::Event event = sf::Event();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    for (size_t i = 0; i < buttons.size(); ++i) {
                        if (buttons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            displayProductPage(static_cast<int>(i));
                        }
                    }

                   if (buttonBasket.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        std::cout << "Navigating to the order page...\n";
                        displayOrderPage(order);
                        return;
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


void displayProductPage(size_t index) {
        if (index < factories.size() && factories[index] != nullptr) {
        std::vector<sf::RectangleShape> localbuttons;
        std::vector<sf::Text> localbuttonLabels;

        const ProductPage* page = factories[index]->getProductPage();
        if (page == nullptr) {
            std::cerr << "Error: Product page is null.\n";
            return;
        }

        std::vector<std::shared_ptr<Product>> products = factories[index]->getProducts();
        if (products.empty()) {
            std::cerr << "Error: No products available in the factory.\n";
            return;
        }

        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile(page->getAssets() + "background.jpg")) {
            std::cerr << "Failed to load background image.\n";
            return;
        }
        sf::Sprite backgroundSprite(backgroundTexture);

        float horizontalSpacing = (WINDOW_WIDTH - 3 * BUTTON_WIDTH) / 4;
        float verticalSpacing = (WINDOW_HEIGHT - 2 * BUTTON_HEIGHT) / 3;

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

            size_t row = i / 3;
            size_t col = i % 3;

            float posX = horizontalSpacing + static_cast<float>(col) * (BUTTON_WIDTH + horizontalSpacing);
            float posY = verticalSpacing + static_cast<float>(row) * (BUTTON_HEIGHT + verticalSpacing);

            sf::RectangleShape button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
            button.setPosition(posX, posY);

            if (textures[i].loadFromFile(page->getAssets() + std::to_string(products[i]->getProductID()) + ".jpg")) {
                button.setTexture(&textures[i]);
            } else {
                std::cerr << "Failed to load image for " << products[i]->getProductName() << "\n";
            }

            localbuttons.push_back(button);

            sf::Text label(products[i]->getProductName(), font, 20);
            label.setFillColor(sf::Color::White);
            label.setPosition(posX + 10, posY + BUTTON_HEIGHT + 5);
            localbuttonLabels.push_back(label);
        }

        while (window.isOpen()) {
            sf::Event event = sf::Event();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    for (size_t i = 0; i < localbuttons.size(); ++i) {
                        if (localbuttons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            if (i < products.size() && products[i] != nullptr) {

                                order.addProduct(products[i]);

                                std::cout << "Product added to order: " << products[i]->getProductName() << std::endl;

                                return;
                            }
                        }
                    }
                }

            }
            window.clear();
            window.draw(backgroundSprite);
            for (auto& label : localbuttonLabels) {
                window.draw(label);
            }
            for (auto& button : localbuttons) {
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