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
    explicit ProductPage( const std::string& buttonText_);

   // [[nodiscard]] const std::string& getTitle() const;
    [[nodiscard]] std::string getButtonText() const;
    [[nodiscard]] const std::string& getAssets() const;

    virtual bool isClicked(sf::RenderWindow& window);
    virtual ~ProductPage()  = default;
};

#endif // PRODUCT_PAGE_H
