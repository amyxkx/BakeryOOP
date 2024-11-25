#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "Ornament.h"
#include "Cake.h"
#include "Order.h"


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Helper.h>
//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"

/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass *getC() {
    return new SomeClass{2};
}
//////////////////////////////////////////////////////////////////////
void clearScreen();

class SeasonalSpecialCake: public Cake {
    std::string SeasonName;
    std::string availabilityToBuy;

};

class WeddingCake: public Cake {
    std::string ColourTheme;
    std::vector<std::string> WeddingOrnaments;
    int guests;
    int tiers_number;

};

class Pastries: public Cake {
    std::string Specific;
    std::string FlavorProfile;
};

// class BirthdayCake: public Cake {
//     std::string BirthdayTheme;
//     std::vector<std::string> BirthdayOrnaments;
//     int guests;
//     int tiers_number;
// };

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void placeOrder(const std::vector<Cake>& cakes); // Function prototype
int getValidCakeSelection(const std::vector<Cake>& cakes); // Function prototype

void placeOrder(const std::vector<Cake>& cakes) {
    std::cout << "*********************************************************\n"
              << "Thank you for taking an interest in Sweet Spell Bakery! \nWe make cakes out of love and passion\n"
              << "*********************************************************\n\n"
              << "Our current cake collection is:\n\n"
              << "*********************************************************\n"
              << "\n";

    int aux = 1;
    for (const auto& c : cakes) {
        std::cout << "Option " << aux << ": " << c.getCakeName() << "\n";
        aux++;
    }

    std::cout << "*********************************************************\n"
              << "\n\n"
              << "Which one would you like to order? (choose just the number <3): \n";

   const int order_temp = getValidCakeSelection(cakes); // Using the helper function

    clearScreen();
    std::cout << "---------------------------------------------------------\n"
              << "*********************************************************\n"
              << "\n     Amazing choice! :)                                \n\n"
              << "*********************************************************\n"
              << "---------------------------------------------------------\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::string deliveryDate;
    std::cout << "\nEnter delivery date (format: MM-DD): ";
    std::cin >> deliveryDate;

    int aux_paymentMethod;
    std::string paymentMethod;
    std::cout << "\nPlease choose a payment method  (Choose just the number)\n"
              << "Option 1: Cash on Delivery\n"
              << "Option 2: Online Payment by Card\n"
              << "Option 3: Bank Deposit\n";
    std::cin >> aux_paymentMethod;

    while (true) {
        if (aux_paymentMethod == 1 || aux_paymentMethod == 2 || aux_paymentMethod == 3) {
            if (aux_paymentMethod == 1) {
                paymentMethod = "Cash on Delivery";
                std::cout << "You chose Cash on Delivery as payment method.\n";
                break;
            }
            if (aux_paymentMethod == 2) {
                paymentMethod = "Online Payment by Card";
                std::cout << "You chose Online Payment by Card.\n";
                break;
            }
            if (aux_paymentMethod == 3) {
                paymentMethod = "Bank Deposit";
                std::cout << "You chose Bank Deposit.\n";
                break;
            }
        } else {
            clearScreen();
            std::cout << "\n ****** Invalid input.******  \n"
                      << "Please select a valid payment method from 1 to 3: "
                      << "Option 1: Cash on Delivery\n"
                      << "Option 2: Online Payment by Card\n"
                      << "Option 3: Bank Deposit\n";
            std::cin >> aux_paymentMethod;
        }
    }

    std::cout << "\nOrder successfully placed! Thank you for supporting our business!\n";
}

int getValidCakeSelection(const std::vector<Cake>& cakes) {
    int order_temp = 0;
    std::cin >> order_temp;

    while (order_temp < 1 || order_temp > static_cast<int>(cakes.size())) {
        std::cout << "\nInvalid selection. Please enter a number between 1 and " << cakes.size() << " :)\n";
        std::cin >> order_temp;
    }

    return order_temp;
}

int main() {
    init_threads(); // NOTE: this function call is needed for environment-specific fixes //                                            //
    Helper helper;
    helper.help();

    sf::RenderWindow window;
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    window.setVerticalSyncEnabled(true);                                    ///
    /// window.setFramerateLimit(60);                                       ///


    while(window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                break;
                case sf::Event::Resized:
                    std::cout << "New width: " << window.getSize().x << '\n'
                              << "New height: " << window.getSize().y << '\n';
                break;
                case sf::Event::KeyPressed:
                    std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if(e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
                default:
                    break;
            }
        }
        if(shouldExit) {
            window.close();
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }

    //displayWelcomeMessage();clearScreen();

    placeOrder(cakes);

    return 0;
}
