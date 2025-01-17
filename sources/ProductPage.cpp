#include "../headers/ProductPage.h"
#include <iostream>

ProductPage::ProductPage( const std::string& buttonText_) {
    if (!font.loadFromFile("assets/font/YujiMai.ttf")) {
        std::cerr << "Failed to load font.\n";
        exit(-1);
    }

    button = sf::RectangleShape(sf::Vector2f(320, 70));
    button.setPosition(120.f, static_cast<float>(basePosition + 50));
    button.setFillColor(sf::Color(0, 0, 0, 170));
    buttonText.setString(buttonText_);
    buttonText.setFont(font);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(140.f, static_cast<float>(basePosition + 60));
}

// const std::string &ProductPage::getTitle() const {
//     return title;
// }

std::string ProductPage::getButtonText() const {
    return buttonText.getString();
}

const std::string &ProductPage::getAssets() const {
    return assets;
}
// cppcheck-suppress unusedFunction ; false positive
bool ProductPage::isClicked(sf::RenderWindow& window) {
    return button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
