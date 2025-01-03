#ifndef PRODUCT_PAGE_H
#define PRODUCT_PAGE_H

#include <SFML/Graphics.hpp>
#include <string>

class ProductPage {
protected:
    sf::RectangleShape button;
    sf::Text buttonText;
    int basePosition = 300;
    sf::Font font;
    std::string title;
    std::string assets;

public:
    ProductPage(int offsetX, int offsetY, const std::string& buttonText_);

    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] std::string getButtonText() const;
    [[nodiscard]] std::string getAssets() const;

    virtual bool isClicked(sf::RenderWindow& window);
};

#endif // PRODUCT_PAGE_H
