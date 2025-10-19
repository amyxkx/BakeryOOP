#include "../headers/Pastry.h"


Pastry::Pastry(const int ID, const std::string& name, const std::string& flavor, const std::string& cream,
               float weight_without_ornaments, float price_per_kg, const std::string& specific, const std::string& flavorProfile)
    : Product(ID, name, flavor, cream, weight_without_ornaments, price_per_kg),
      Specific(specific), FlavorProfile(flavorProfile) {}

float Pastry::FinalPrice() const {

    float localbasePrice = getBasePrice();

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    const std::tm* localTime = std::localtime(&currentTime);

    int currentHour = localTime->tm_hour;

    if (closingHour - currentHour == 1) {
        return basePrice * 0.5f; // 50% off
    }
    return localbasePrice;
}
int Pastry::closingHour = 20;


