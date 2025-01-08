#ifndef CAKEPAGE_H
#define CAKEPAGE_H

#include "ProductPage.h"

class CakePage : public ProductPage {
public:
    explicit CakePage( const std::string& buttonText_)
        : ProductPage( buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaCakes/";
    }
    virtual ~CakePage() = default;
};
#endif // CAKEPAGE_H
