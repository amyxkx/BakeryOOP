#include "SeasonalSpecialCakes.h"
#include <chrono>
#include <string>
#include <iomanip>


SeasonalSpecialCake::SeasonalSpecialCake(const int ID, const std::string& name, const std::string& flavor, const std::string& cream, float weight, float basePrice,
                                         const std::string& season, const std::string& availabilityDate, const std::string& message)
    : Product(ID, name, flavor, cream, weight, basePrice), SeasonName(season), availabilityToBuy(availabilityDate), message(message) {}


float SeasonalSpecialCake::FinalPrice() const {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* const localTime = std::localtime(&currentTime);

    std::ostringstream currentDateStream;
    currentDateStream << std::put_time(localTime, "%Y-%m-%d");
    std::string currentDate = currentDateStream.str();

    std::tm availabilityDate = {};
    std::tm currentTm = {};
    std::istringstream availabilityStream(availabilityToBuy);
    std::istringstream currentStream(currentDate);
    availabilityStream >> std::get_time(&availabilityDate, "%Y-%m-%d");
    currentStream >> std::get_time(&currentTm, "%Y-%m-%d");

    auto availabilityTime = std::mktime(&availabilityDate);
    auto currentTimeSec = std::mktime(&currentTm);
    double differenceInDays = std::difftime(availabilityTime, currentTimeSec) / (60 * 60 * 24);

    if (differenceInDays >= 0 && differenceInDays <= 1) {
        return basePrice * weight * 1.5f;
    }

    if (differenceInDays >= 20 && differenceInDays <= 30) {
        return basePrice * weight * 0.8f;
    }

    return basePrice * weight;
}
SeasonalSpecialCake::SeasonalSpecialCake(const SeasonalSpecialCake& other)
    : Product(other), SeasonName(other.SeasonName), availabilityToBuy(other.availabilityToBuy), message(other.message) {}

SeasonalSpecialCake& SeasonalSpecialCake::operator=(const SeasonalSpecialCake& other) {
    if (this != &other) {
        SeasonalSpecialCake temp(other);
        swap(*this, temp);
    }
    return *this;
}

void swap(SeasonalSpecialCake& first, SeasonalSpecialCake& second) noexcept {
    using std::swap;
    swap(first.SeasonName, second.SeasonName);
    swap(first.availabilityToBuy, second.availabilityToBuy);
    swap(first.message, second.message);
}
