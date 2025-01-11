#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "headers/PastryFactory.h"
#include "headers/CakeFactory.h"
#include "headers/SeasonalCakeFactory.h"
#include "headers/Menu.h"

int main() {
    sf::Font font;

    if (!font.loadFromFile("assets/font/YujiMai.ttf")) {
        std::cerr << "Failed to load font.\n";
        return -1;
    }
    auto pastryFactory = PastryFactory::create();
    pastryFactory->PreparePastriesForOrders();

    auto cakeFactory = CakeFactory::create();
    cakeFactory->PrepareCakesForOrders();

    auto seasonalCakeFactory = SeasonalCakeFactory::create();
    seasonalCakeFactory->PrepareSeasonalCakesForOrders();

    Menu menu;
    menu.run();
    std::cout<<"\n";

    std::cout<<"\n";
    menu.executeStockOperations();

    return 0;
}