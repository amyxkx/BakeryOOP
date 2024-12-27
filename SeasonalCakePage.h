#ifndef SEASONALCAKEPAGE_H
#define SEASONALCAKEPAGE_H

#include "ProductPage.h"

class SeasonalCakePage : public ProductPage {
public:
    SeasonalCakePage(int offsetX, int offsetY, const std::string& buttonText_)
        : ProductPage(offsetX, offsetY, buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaSeasonalCakes/";
    }

};

#endif // SEASONALCAKEPAGE_H
