#include "Cake.h"
#include "Ornament.h"

Cake::Cake(const std::string& cknm, const std::string& flv, const std::string& cr,
           const std::vector<Ornament>& ornm, const int days, const float w, const float price)
    : cakeName(cknm), flavor(flv), cream(cr), ornaments(ornm),
      days_until_expiration(days), weight_without_ornaments(w), price_per_kg(price) {}

[[nodiscard]] const std::string Cake::getCakeName() const {
    return cakeName;
}

[[nodiscard]] const float Cake::getPrice() const { // !!!!!CAKE::
    return price_per_kg;
}

[[nodiscard]] const float Cake::getWeight() const {
    return weight_without_ornaments;
}

[[nodiscard]] float Cake::TotalWeight( ) {
    float total_weight = weight_without_ornaments;
    for( const auto& ornm: ornaments) {

        if( ornm.getAmountType() == "kilograms")
            total_weight+=ornm.getAmount();
        else
            total_weight+=ornm.getAmount()*ornm.getPieceWeight();
    }
    return total_weight;
};

float Cake::FinalPrice() {
    float final_price = price_per_kg*weight_without_ornaments;
    for( const auto& ornm: ornaments) {
        final_price+=ornm.getPrice()*ornm.getAmount();
    }
    return final_price;
};


