#ifndef MENU_H
#define MENU_H

#include <iomanip>
#include <string>
#include <vector>

#include "../headers/OrderBuilder.h"
#include "../headers/ClientBuilder.h"
#include "../headers/Order.h"
#include "../headers/ProductFactory.h"
#include "../headers/ProductPage.h"

constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;
constexpr float BUTTON_WIDTH = 200;
constexpr float BUTTON_HEIGHT = 200;


class Menu {
    std::vector<ProductFactory*> factories;
    std::vector<ProductPage*> pages;
    ClientBuilder clientBuilder;
    OrderBuilder orderBuilder;
    Order order;
    sf::RenderWindow window;
    sf::Font localFont;

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

    sf::RectangleShape createButton(float x, float y, float width, float height, sf::Color color);
    sf::Text createText(const std::string& content, sf::Font const& font, unsigned int size, sf::Color color,
        float x, float y);
public:

    Menu();
    void displayWelcomePage();
    void displayOrderPage(const Order& localorder);
    void displayDetailsPage();
    void displayMenuPage();
    void displayProductPage(size_t index);
    void executeStockOperations();
    void run();

};

#endif //MENU_H
