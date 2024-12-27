#ifndef PASTRYPAGE_H
#define PASTRYPAGE_H

#include "ProductPage.h"

class PastryPage : public ProductPage {
public:
    PastryPage(int offsetX, int offsetY, const std::string& buttonText_)
        : ProductPage(offsetX, offsetY, buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaPastries/";
    }

};

#endif // PASTRYPAGE_H
