//
// Created by amalia on 1/11/2025.
//
#include "../headers/Menu.h"
#include "../headers/storage.h"
#include <SFML/Window.hpp>
#include "../headers/Product.h"
#include "../headers/PastryFactory.h"
#include "../headers/CakeFactory.h"
#include "../headers/SeasonalCakeFactory.h"


sf::RectangleShape Menu::createButton(float x, float y, float width, float height, sf::Color color) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(color);
    return button;
}

sf::Text Menu::createText(const std::string& content, sf::Font const& font, unsigned int size, sf::Color color, float x, float y) {
    sf::Text text(content, font, size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}

Menu::Menu() : order() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dessert Collection");

    factories.push_back(new CakeFactory);
    factories.push_back(new PastryFactory);
    factories.push_back(new SeasonalCakeFactory);

    for (auto factory : factories) {
        if (auto* page = factory->getProductPage()) {
            pages.push_back(page);
        }
    }

    if (!font.loadFromFile("assets/font/YujiMai.ttf")) {
        std::cerr << "Failed to load font.\n";
        exit(-1);
    }
}


void Menu::displayWelcomePage() {
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/background.jpeg")) {
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
                 //  std::cout << "Button clicked! Transitioning to Menu Page...\n";
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

void Menu::displayOrderPage(const Order& localorder) {
    buttons.clear();
    buttonTexts.clear();
    window.clear();

    sf::Texture backgroundOrder;
    if (!backgroundOrder.loadFromFile("assets/client/backgroundOrder.jpg")) {
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
        for (const auto& product : orderedProduct) {
            if (product != nullptr) {
                costOfOrder+=product->FinalPrice();
            }
        }

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
            //    std::cout << "Finish Order clicked! Proceeding to details page...\n";
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

void Menu::displayDetailsPage() {

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/client/backgroundClient.jpg")) {
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

    std::vector<std::string> inputFields(5);
    std::vector<sf::Text> labels(7);

    labels[0] = createText("Name:", font, 30, sf::Color::Black, 200, 150);
    labels[1] = createText("Delivery Address :", font, 30, sf::Color::Black, 200, 230);
    labels[2] = createText("Phone:", font, 30, sf::Color::Black, 200, 310);
    labels[3] = createText("Email", font, 30, sf::Color::Black, 200, 390);
    labels[4] = createText("(@.*)", font, 20, sf::Color::Black, 200, 430);
    labels[5] = createText("Delivery date:", font, 30, sf::Color::Black, 200, 500);
    labels[6] = createText("(DD-MM-YYYY)", font, 20, sf::Color::Black, 200, 540);

    std::vector<sf::Text> fields(5);

    fields[0] = createText("", font, 25, sf::Color::Black, 400, 150);
    fields[1] = createText("", font, 25, sf::Color::Black, 500, 230);
    fields[2] = createText("", font, 25, sf::Color::Black, 400, 310);
    fields[3] = createText("", font, 25, sf::Color::Black, 400, 390);
    fields[4] = createText("", font, 25, sf::Color::Black, 500, 500);


    sf::RectangleShape finishButton(sf::Vector2f(200, 70));
    finishButton.setPosition(540, 550);
    finishButton.setFillColor(sf::Color(0, 0, 0, 200));

    sf::Text finishText = createText("Submit", font, 25, sf::Color::White, 575, 565);

    int activeField = 0;
    bool isFormValid = false;

    auto checkInput = [&]() {
        try {
            for (auto& field : inputFields) {
                if (field.empty()) {
                    throw EroareCampFormGol();
                }
            }

            for (size_t i = 0; i < inputFields.size(); ++i) {
                switch (i) {
                    case 0:
                        clientBuilder.setName(inputFields[i]);
                    break;
                    case 1:
                        clientBuilder.setOrderAddress(inputFields[i]);
                    break;
                    case 2:
                        clientBuilder.setPhoneNumber(inputFields[i]);
                    break;
                    case 3:
                        clientBuilder.setEmailAddress(inputFields[i]);
                    break;
                    case 4:
                        orderBuilder.setDateOfDelivery(inputFields[i]);
                    break;
                }
            }

            Client client = clientBuilder.build();
            isFormValid = true;
            Order orderLocal = orderBuilder.build();

            errorMessage.setString("");

        } catch (const EroareInput& e) {
            errorMessage.setString(e.what());  isFormValid = false;
        }
    };

    while (window.isOpen()) {
        sf::Event event = sf::Event();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                char inputChar = static_cast<char>(event.text.unicode);
                if (std::isprint(inputChar)) {
                    inputFields[activeField] += inputChar;
                } else if (inputChar == '\b') {
                    if (!inputFields[activeField].empty()) {
                        inputFields[activeField].pop_back();
                    }
                }
            }
            isFormValid = false;

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    activeField = (activeField + 1) % 5;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                   checkInput();
                    if (isFormValid) {
                        return;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (finishButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    checkInput();
                    if (isFormValid) {
                        return;
                    }
                }
            }
        }

        for (size_t i = 0; i < inputFields.size(); ++i) {
           fields[i].setString(inputFields[i]);
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(Background);
        window.draw(pageTitleShadow);
        window.draw(pageTitle);

        for (auto& label : labels) {
            window.draw(label);
        }

        for (auto& field : fields) {
            window.draw(field);
        }

        window.draw(finishButton);
        window.draw(finishText);

        window.draw(errorMessage);

        window.display();
    }
}

void Menu::displayMenuPage() {

        sf::Texture backgroundTexturePage2;
        if (!backgroundTexturePage2.loadFromFile("assets/background2.jpeg")) {
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

        if (textureBasket.loadFromFile("assets/cos.jpg")) {
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


void Menu::displayProductPage(size_t index) {
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
                                orderBuilder.addProduct(products[i]);
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

void Menu::executeStockOperations() {

        Storage<int> productStock(200);

        Storage<std::string> productState("Stoc suficient");

        productStock.display();
        std::cout << "Stare initiala stoc: " << productState.getValue() << std::endl;

        productStock.applyTransformation(updateStock);

        productStock.display();

        productState.setValue(changeState(productState.getValue()));
        std::cout << "Starea curenta a stocului: " << productState.getValue() << std::endl;

        productStock.applyTransformation(updateStock);

        productStock.display();

        productState.setValue(changeState(productState.getValue()));
        std::cout << "Starea curenta a stocului: " << productState.getValue() << std::endl;
}

void Menu::run() {
        displayWelcomePage();
}

