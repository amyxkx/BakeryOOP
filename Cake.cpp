#include "Cake.h"
#include "Ornament.h"

Cake::Cake(const int ID, const std::string& cknm, const std::string& flv, const std::string& cr,
           const std::vector<Ornament>& ornm, const int days, const float w, const float price)
    : cakeID(ID), cakeName(cknm), flavor(flv), cream(cr), ornaments(ornm),
      days_until_expiration(days), weight_without_ornaments(w), price_per_kg(price) {}

[[nodiscard]] int Cake::getCakeID() const {
    return cakeID;
}

[[nodiscard]] const std::string Cake::getCakeName() const {
    return cakeName;
}

[[nodiscard]]  float Cake::getPrice() const {
    return price_per_kg;
}

[[nodiscard]]  float Cake::getWeight() const {
    return weight_without_ornaments;
}

[[nodiscard]] float Cake::TotalWeight( ) const {
    float total_weight = weight_without_ornaments;
    for( const auto& ornm: ornaments) {

        if( ornm.getAmountType() == "kilograms")
            total_weight+=ornm.getAmount();
        else
            total_weight+=ornm.getAmount()*ornm.getPieceWeight();
    }
    return total_weight;
};

float Cake::FinalPrice() const {
    float final_price = price_per_kg*weight_without_ornaments;
    for( const auto& ornm: ornaments) {
        final_price+=ornm.getPrice()*ornm.getAmount();
    }
    return final_price;

};

std::vector<Cake> cakes = {
    Cake(1, "Chocolate", "Chocolate", "Chocolate Ganache", ChocolateOrnaments, 5, 2.0f, 100),
    Cake(2, "Vanilla", "Vanilla", "Buttercream", VanillaOrnaments, 5, 2.0f, 100),
    Cake(3, "Carrot Cake", "Carrot", "Cream Cheese", CarrotOrnaments, 6, 2.0f, 80),
    Cake(4, "Classic Cheesecake", "Biscuit Base", "Cream Cheese", CheesecakeOrnaments, 5, 1.5f, 80),
    Cake(5, "Forest Fruit Cheesecake", "Biscuit Base", "Cream Cheese", CheesecakeOrnaments, 5, 1.5f, 90),
    Cake(6, "Lemon Cake", "Vanilla with Lemon", "Lemon Frosting", LemonOrnaments, 4, 2.0f, 90),
    Cake(7, "Red Velvet", "Red Velvet", "Cream Cheese", RedVelvetOrnaments, 5, 3.0f, 130),
    Cake(8, "Forest Fruit Cake", "Mixed Berries", "Whipped Cream", ForestFruitOrnaments, 4, 2.0f, 110),
    Cake(9, "Pistachio Cake", "Pistachio", "Mascarpone Cream", PistachioOrnaments, 3, 1.8f, 120),
    Cake(10, "Tiramisu", "Coffee", "Mascarpone", TiramisuOrnaments, 6, 2.5f, 150),
    Cake(11, "Mango Coconut Cake", "Mango", "Coconut Cream", MangoCoconutOrnaments, 4, 2.2f, 110),
    Cake(12, "Strawberry Shortcake", "Strawberry", "Whipped Cream", StrawberryShortcakeOrnaments, 5, 1.8f, 100),
    Cake(13, "Chocolate Mint Cake", "Chocolate", "Mint Cream", ChocolateMintOrnaments, 5, 2.0f, 120),
    Cake(14, "Coffee Walnut Cake", "Coffee", "Walnut Cream", CoffeeWalnutOrnaments, 6, 2.5f, 130),
    Cake(15, "Apple Cinnamon Cake", "Apple", "Cinnamon Buttercream", AppleCinnamonOrnaments, 4, 1.7f, 90),
    Cake(16, "Pineapple Upside-Down Cake", "Pineapple", "Buttercream", PineappleUpsideDownOrnaments, 4, 2.0f, 85),
    Cake(17, "Churro Cake", "Cinnamon", "Vanilla Buttercream", ChurroOrnaments, 5, 2.0f, 100),
    Cake(18, "Peach Melba Cake", "Peach", "Raspberry Cream", PeachMelbaOrnaments, 5, 2.0f, 110)
};



