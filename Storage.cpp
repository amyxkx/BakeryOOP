#include "Storage.h"

int updateStock(int stock) {
    auto lambda = [](int value) {
        if (value > 1000) {
            return static_cast<int>(value * 0.80);
        }
        if (value < 500) {
            return value -100;
        }
        return value + 200;
    };

    return lambda(stock);
}


std::string changeState(const std::string& state) {
    if (state == "Stoc complet")
        return "Stoc suficient";

    if (state == "Stoc suficient")
        return "Stoc mic";

    if (state == "Stoc mic")
        return "Stoc epuizat";

    if (state == "Stoc epuizat")
        return "Stocul se reface";

    return "Stoc complet";
}