#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "Ornament.h"
#include <SFML/Graphics.hpp>

#include <Helper.h>

void clearScreen();

class Cake {
    std::string CakeName;
    std::string flavor;
    std::string cream;
    std::vector<Ornament> ornaments;
    int days_until_expiration;
    float weight_without_ornaments;
    float price_per_kg;


public:
    Cake(const std::string  &cknm, const std::string& flv, std::string cr,
             const std::vector<Ornament>& ornm, const int days, const float w, const float price )
    : CakeName(cknm), flavor(flv), cream(std::move(cr)), ornaments(ornm),
      days_until_expiration(days), weight_without_ornaments(w), price_per_kg(price) {}

    [[nodiscard]] const std:: string & getCakeName() const {
        return CakeName;
    }

    [[nodiscard]] const float  & getPrice() const {
        return price_per_kg;
    }
    [[nodiscard]] const float  & getWeight() const {
        return weight_without_ornaments;
    }
    [[nodiscard]]float TotalWeight( float  total_weight) const {
        for (const auto& ornm : ornaments) {
            if( ornm.getAmountType()== "kilograms")
            total_weight += ornm.getAmount();
            else
                if( ornm.getAmountType()== "pieces")
                    total_weight += ornm.getAmount()*ornm.getPieceWeight();
        }
        return total_weight;
    }

    [[nodiscard]]float CostOfCake(float price) const {
        for (const auto& ornm : ornaments) {
                price += ornm.getPrice()*ornm.getAmount();
        }
        return price;
    }

    void displaySummary() const {
        std::cout << "Flavor of the cake base: " << this->flavor << std::endl;
        std::cout << "Weight of the cake (edible): " << this->weight_without_ornaments << " killograms" << std::endl;
        std::cout << "Covering cream: " << this->cream << std::endl;
        std::cout << "Price per kg: " << this->price_per_kg << std::endl;
        std::cout << "Days until expiration: " << this->days_until_expiration << std::endl;
        std::cout << "Ornaments (on top of cake): ";
        for (const auto& ornm : ornaments) {
            std::cout << ornm.getName() << " "<<std::endl;
        }
        std::cout <<"\n";
        std::cout << "All cakes have carefully chosen details that add to the weight and the price of the cake. Here are some more details: \n\n";
        std::cout << "Decorated, the cake weights : " << TotalWeight(this->weight_without_ornaments ) << " killograms "<< std::endl;
        std::cout << "Final price for the cake is: " << CostOfCake(this->weight_without_ornaments * this->price_per_kg) << " lei "<< std::endl;
    };

    friend std::ostream& operator<<(std::ostream& os, const Cake& details) {
        os << "Cake Name: " << details.CakeName << "\n"
           << "Flavor: " << details.flavor << "\n"
           << "Cream: " << details.cream << "\n"
           << "Days Until Expiration: " << details.days_until_expiration << "\n"
           << "Weight (without ornaments): " << details.weight_without_ornaments << " kg\n"
           << "Price per kg: " << details.price_per_kg << " lei\n"
           << "Ornaments: ";
        for (const auto& ornm : details.ornaments) {
            os << ornm << " ";
        }
        os << "\n";
        return os;
    }
};

class SeasonalSpecialCake: public Cake {
    std::string SeasonName;
    std::string availabilityToBuy;

};

class SpecialEventCake: public Cake {
    std::string EventType;
    std::vector <std::string> Candles;
    float AdditionalCharge;
    int guests;
    int tiers_number;

};

class MiniCakes: public Cake {
    int type;
    int NrServings;
};


class Order {
    int orderID;
    static int orderCounter;
    Cake cake;
    std::string DateOfDelivery;
    std::string payment;

public:
    Order(const Order& other)
       : cake(other.cake), DateOfDelivery(other.DateOfDelivery), payment(other.payment) {
        orderID = ++orderCounter;
    }

    Order(const Cake& ck, std::string Delivery, std::string pay)
    : cake(ck), DateOfDelivery(std::move(Delivery)), payment(std::move(pay)) {
        orderID = ++orderCounter;
    }

    Order& operator=(const Order& other) {
        if (this != &other) {
            cake = other.cake;
            DateOfDelivery = other.DateOfDelivery;
            payment = other.payment;
            orderID = ++orderCounter;
        }
        return *this;
    }

    [[nodiscard]] int getOrderID() const {
        return orderID;
    }

    [[nodiscard]] const Cake& getCakeDetails() const {
        return cake;
    }

    [[nodiscard]] const std::string& getDateOfDelivery() const {
        return DateOfDelivery;
    }

    [[nodiscard]] const std::string& getPayment() const {
        return payment;
    }

    ~Order() =default;


    friend std::ostream& operator<<(std::ostream& os, const Order& order){
        os << "Order ID: " << order.getOrderID() << " Cake: ";
        order.getCakeDetails().displaySummary();
        os << " Delivery date: " << order.getDateOfDelivery() << " Payment method: " << order.getPayment() << std::endl;
        return os;
    }
};

class Client {

    Order order;
    std::string name;
    std::string phoneNumber;
    std::string OrderAddress;
    std::string EmailAddress;

public:
    Client( const Order &ord, std::string nm, std::string phone, std::string adrs, std::string email)
    : order(ord), name(std::move(nm)), phoneNumber(std::move(phone)), OrderAddress(std::move(adrs)), EmailAddress(std::move(email)) {}

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
                  << "Which one would you like to order? (choose just the number <3): ";

        const int order_temp = getValidCakeSelection(cakes); // Using the helper function

        clearScreen();

        std::cout<<"---------------------------------------------------------\n"
                 <<"*********************************************************\n"
                 <<"\n     Amazing choice! :)                                \n\n"
                 <<"*********************************************************\n"
                 <<"---------------------------------------------------------\n";

        std::this_thread::sleep_for(std::chrono::seconds(3));

        clearScreen();

        cakes[order_temp - 1].displaySummary();

        //std::this_thread::sleep_for(std::chrono::seconds(10));
        //clearScreen();


        // Collect order details
        std::string deliveryDate;
        std::cout << "\nEnter delivery date (format: MM-DD): ";
        std::cin >> deliveryDate;

        int aux_paymentMethod;
        std::string paymentMethod;
        std::cout << "\nPlease choose a payment method  (Choose just the number)\n"
                  << "(" << cakes[order_temp - 1].CostOfCake(   cakes[order_temp - 1].getPrice() * cakes[order_temp - 1].getWeight()  )<<") ron\n"
                  << "Option 1: Cash on Delivery\n"
                  << "Option 2: Online Payment by Card\n"
                  << "Option 3: Bank Deposit\n";
        std::cin >> aux_paymentMethod;

        while (true) {
            if (aux_paymentMethod == 1 || aux_paymentMethod == 2|| aux_paymentMethod == 3) {
                if (aux_paymentMethod == 1) {
                    paymentMethod = "Cash on Delivery";
                    std::cout << "You chose Cash on Delivery as payment method.\n";
                    break;
                } if (aux_paymentMethod == 2) {
                    paymentMethod = "Online Payment by Card";
                    std::cout << "You chose Online Payment by Card.\n";
                    break;
                }  if (aux_paymentMethod == 3) {
                    paymentMethod = "Bank Deposit";
                    std::cout << "You chose Bank Deposit.\n";
                    break;
                }
            }else {
                clearScreen();
                std::cout << "\n ****** Invalid input.******  \n"
                <<"Please select a valid paying method from 1 to 3: "
                << "Option 1: Cash on Delivery\n"
                << "Option 2: Online Payment by Card\n"
                << "Option 3: Bank Deposit\n";
                std::cin >> aux_paymentMethod;
            }
        }

        const Order newOrder( cakes[order_temp - 1], deliveryDate, paymentMethod );

        this->order = newOrder;

        std::cout << "\nOrder successfully placed! Thank you for supporting our business!\n";
    }

    static int getValidCakeSelection(const std::vector<Cake>& cakes) {
        int order_temp = 0;
        std::cin >> order_temp;

        while (order_temp < 1 || order_temp > static_cast<int>(cakes.size())) {
            std::cout << "\nInvalid selection. Please enter a number between 1 and " << cakes.size() << " :)\n";
            std::cin >> order_temp;
        }

        return order_temp;
    }


    friend std::ostream& operator<<(std::ostream& os, const Client& cust) {
        os << "Customer: " << cust.name << ", Phone: " << cust.phoneNumber << " Email: " << cust.EmailAddress << " Address: " << cust.OrderAddress << std::endl;
        return os;
    }
};

int Order::orderCounter = 0;

void displayWelcomeMessage(  ) {
    std::string line1 = "        Welcome to";
    std::string line2 = "    Sweet Spell Bakery!";
    constexpr int delay = 300;

    std::cout << "---------------------------------------------------------\n";
    std::cout << "*********************************************************\n";
    std::cout << "*                ";
    std::string word = "";

    for (const char caracter : line1) {
        if (caracter == ' ') {
            std::cout << word << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            word.clear();  // reset word for the next
        } else {
            word += caracter; }
    }
    std::cout << word << "                     *\n";
    std::cout << "*                ";
    word = "";

    for (const char caracter : line2) {
        if (caracter == ' ') {
            std::cout << word << " ";
            std::cout.flush();
            std::this_thread::sleep_for( std::chrono::milliseconds(delay) );
            word.clear();
        } else {
            word += caracter;
        }
    }
    std::cout << word << "                *\n";

    std::cout    << "---------------------------------------------------------\n"
                 << "*********************************************************\n"
                 << "*                                                       *\n"
                 << "*                        *   *   *                      *\n"
                 << "*                        |   |   |                      *\n"
                 << "*                     ~~~~~~~~~~~~~~~                   *\n"
                 << "*                    |we all love cake|                 *\n"
                 << "*                    ******************                 *\n"
                 << "*                   |     *      *     |                *\n"
                 << "*                  **********************               *\n"
                 << "*                 |      *   * *   *     |              *\n"
                 << "*                 ************************              *\n"
                 << "*                | *       *     *      * |             *\n"
                 << "*                |     *      *     *     |             *\n"
                 << "*********************************************************\n"
                 << "---------------------------------------------------------\n";
}

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

int main() {
    //init_threads();
    Helper helper;
    helper.help();
    sf::RenderWindow window;
    window.setVerticalSyncEnabled(true);
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


     displayWelcomeMessage();

     clearScreen();

  // Kilograms
    Ornament Almonds = {"almonds", "kilograms",0.0f, 0.1f, 100.0f};  // Price per kg
    Ornament CaramelFudge = {"caramel fudge", "kilograms",0.0f, 0.25f, 200.0f};  // Price per kg
    Ornament ChocolateBites = {"chocolate bites", "kilograms",0.0f, 0.1f, 80.0f};  // Price per kg
    Ornament ChocolateDrizzle = {"chocolate drizzle", "kilograms",0.0f, 0.1f, 150.0f};  // Price per kg
    Ornament CoconutFlakes = {"coconut flakes", "kilograms",0.0f, 0.1f, 100.0f};  // Price per kg
    Ornament EdibleGlitter = {"edible glitter", "grams", 0.0f,0.01f, 500.0f};  // Price per gram
    Ornament PineappleSlices = {"pineapple slices", "kilograms",0.0f, 0.3f, 60.0f};  // Price per kg
    Ornament Pistachios = {"pistachios", "kilograms", 0.0f,0.3f, 120.0f};  // Price per kg
    Ornament Raspberries = {"raspberries", "kilograms",0.0f, 0.15f, 90.0f};  // Price per kg
    Ornament Strawberries = {"strawberries", "kilograms",0.0f, 0.2f, 75.0f};  // Price per kg
    Ornament WhippedCream = {"whipped cream", "kilograms",0.0f, 0.5f, 30.0f};  // Price per kg
    Ornament LemonSlices = {"lemon slices", "kilograms", 0.0f,0.2f, 75.0f};  // Price per kg
    Ornament MintCream = {"mint cream", "kilograms",0.0f, 0.5f, 30.0f};  // Price per kg
    Ornament Sprinkles = {"sprinkles", "kilograms", 0.0f, 0.05f, 60.0f};  // Price per kg
    Ornament WhiteChocolateShavings = {"white chocolate shavings", "kilograms", 0.0f, 0.15f, 120.0f};  // Price per kg
    Ornament MMs = {"M&Ms", "kilograms",0.0f, 0.1f, 80.0f};
    Ornament Cinnamon = {"cinnamon", "kilograms",0.0f, 0.05f, 60.0f};  // Price per kg
// Pieces
    Ornament BiscoffCookies = {"Biscoff cookies", "pieces",0.1f, 3.0f, 1.0f};  // Price per piece
    Ornament CandyCanes = {"candy canes", "pieces", 0.1f, 4.0f, 3.0f};  // Price per piece
    Ornament GummyBears = {"gummy bears", "pieces",0.1f, 5.0f, 2.0f};  // Price per piece
    Ornament KinderBueno = {"kinderbueno", "pieces",0.1f, 2.0f, 2.5f};  // Price per piece
    Ornament JellyBeans = {"jelly beans", "pieces",0.1f, 10.0f, 1.0f};  // Price per piece
    Ornament Macarons = {"macarons", "pieces",0.1f, 3.0f, 5.0f};  // Price per piece
    Ornament Marshmallows = {"marshmallows", "pieces",0.1f, 5.0f, 2.0f};  // Price per piece
    Ornament Oreos = {"oreos", "pieces",0.1f, 2.0f, 1.5f};  // Price per piece
    Ornament SugarRoses = {"sugar roses", "pieces",0.1f, 1.0f, 8.0f};  // Price per piece

    std::vector<Ornament> ChocolateOrnaments = {ChocolateBites, ChocolateDrizzle};
    std::vector<Ornament> VanillaOrnaments = {Sprinkles, WhiteChocolateShavings};
    std::vector<Ornament> CarrotOrnaments = {EdibleGlitter, Almonds};
    std::vector<Ornament> CheesecakeOrnaments = {Raspberries, WhippedCream, EdibleGlitter};
    std::vector<Ornament> ForestFruitOrnaments = {Raspberries, Strawberries, PineappleSlices};
    std::vector<Ornament> LemonOrnaments = {SugarRoses, LemonSlices};
    std::vector<Ornament> RedVelvetOrnaments = {EdibleGlitter, SugarRoses};
    std::vector<Ornament> PistachioOrnaments = {Pistachios, WhiteChocolateShavings};
    std::vector<Ornament> TiramisuOrnaments = {ChocolateBites, EdibleGlitter};
    std::vector<Ornament> MangoCoconutOrnaments = {CoconutFlakes, PineappleSlices};
    std::vector<Ornament> StrawberryShortcakeOrnaments = {Raspberries, WhippedCream};
    std::vector<Ornament> ChocolateMintOrnaments = {ChocolateDrizzle, MintCream};
    std::vector<Ornament> CoffeeWalnutOrnaments = {Pistachios, WhiteChocolateShavings};
    std::vector<Ornament> AppleCinnamonOrnaments = {Cinnamon, EdibleGlitter};
    std::vector<Ornament> PineappleUpsideDownOrnaments = {PineappleSlices, WhippedCream};
    std::vector<Ornament> ChurroOrnaments = {Cinnamon, Sprinkles};
    std::vector<Ornament> PeachMelbaOrnaments = {SugarRoses, Raspberries};

    std::vector<Cake> cakes = {
        Cake("Chocolate", "Chocolate", "Chocolate Ganache", ChocolateOrnaments, 5, 2.0f, 100),
        Cake("Vanilla", "Vanilla", "Buttercream", VanillaOrnaments, 5, 2.0f, 100),
        Cake("Carrot Cake", "Carrot", "Cream Cheese", CarrotOrnaments, 6, 2.0f, 80),
        Cake("Classic Cheesecake", "Biscuit Base", "Cream Cheese", CheesecakeOrnaments, 5, 1.5f, 80),
        Cake("Forest Fruit Cheesecake", "Biscuit Base", "Cream Cheese", CheesecakeOrnaments, 5, 1.5f, 90),
        Cake("Lemon Cake", "Vanilla with Lemon", "Lemon Frosting", LemonOrnaments, 4, 2.0f, 90),
        Cake("Red Velvet", "Red Velvet", "Cream Cheese", RedVelvetOrnaments, 5, 3.0f, 130),
        Cake("Forest Fruit Cake", "Mixed Berries", "Whipped Cream", ForestFruitOrnaments, 4, 2.0f, 110),
        Cake("Pistachio Cake", "Pistachio", "Mascarpone Cream", PistachioOrnaments, 3, 1.8f, 120),
        Cake("Tiramisu", "Coffee", "Mascarpone", TiramisuOrnaments, 6, 2.5f, 150),
        Cake("Mango Coconut Cake", "Mango", "Coconut Cream", MangoCoconutOrnaments, 4, 2.2f, 110),
        Cake("Strawberry Shortcake", "Strawberry", "Whipped Cream", StrawberryShortcakeOrnaments, 5, 1.8f, 100),
        Cake("Chocolate Mint Cake", "Chocolate", "Mint Cream", ChocolateMintOrnaments, 5, 2.0f, 120),
        Cake("Coffee Walnut Cake", "Coffee", "Walnut Cream", CoffeeWalnutOrnaments, 6, 2.5f, 130),
        Cake("Apple Cinnamon Cake", "Apple", "Cinnamon Buttercream", AppleCinnamonOrnaments, 4, 1.7f, 90),
        Cake("Pineapple Upside-Down Cake", "Pineapple", "Buttercream", PineappleUpsideDownOrnaments, 4, 2.0f, 85),
        Cake("Churro Cake", "Cinnamon", "Vanilla Buttercream", ChurroOrnaments, 5, 2.0f, 100),
        Cake("Peach Melba Cake", "Peach", "Raspberry Cream", PeachMelbaOrnaments, 5, 2.0f, 110)
    };

    Order order(cakes[0], "12-12", "Cash on Delivery");
    Client client(order, "Andrei", "0777895645", "str 123 Bucuresti", "andrei@email.com");

    client.placeOrder(cakes);

    return 0;
}