#include "ProductPage.h"
#include <iostream>

ProductPage::ProductPage(int offsetX, int offsetY, const std::string& buttonText_) {
    if (!font.loadFromFile("D:/BakeryOOP/assets/font/YujiMai.ttf")) {
        std::cerr << "Failed to load font.\n";
        exit(-1);
    }

    button = sf::RectangleShape(sf::Vector2f(320, 70));
    button.setPosition(static_cast<float>(120), static_cast<float>(basePosition + 50));
    button.setFillColor(sf::Color(0, 0, 0, 170));
    buttonText.setString(buttonText_);
    buttonText.setFont(font);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(static_cast<float>(140), static_cast<float>(basePosition + 60));

}

std::string ProductPage::getTitle() const {
    return title;
}

std::string ProductPage::getButtonText() const {
    return buttonText.getString();
}

std::string ProductPage::getAssets() const {
    return assets;
}

bool ProductPage::isClicked(sf::RenderWindow& window) {
    return button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
