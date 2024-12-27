#ifndef CAKEPAGE_H
#define CAKEPAGE_H

#include "ProductPage.h"

class CakePage : public ProductPage {
    std::string assets;
public:
    CakePage(int offsetX, int offsetY, const std::string& buttonText_)
        : ProductPage(offsetX, offsetY, buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaCakes/";
    }

};

#endif // CAKEPAGE_H
