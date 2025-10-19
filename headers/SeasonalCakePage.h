#ifndef SEASONALCAKEPAGE_H
#define SEASONALCAKEPAGE_H

#include "ProductPage.h"

class SeasonalCakePage : public ProductPage {
public:
    explicit SeasonalCakePage( const std::string& buttonText_)
        : ProductPage( buttonText_) {
        assets = "assets/PaginaSeasonalCakes/";
    }
    virtual ~SeasonalCakePage() override= default;
};

#endif // SEASONALCAKEPAGE_H
