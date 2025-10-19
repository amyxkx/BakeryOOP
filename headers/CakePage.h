#ifndef CAKEPAGE_H
#define CAKEPAGE_H

#include "ProductPage.h"

class CakePage : public ProductPage {
public:
    explicit CakePage( const std::string& buttonText_)
        : ProductPage( buttonText_) {
        assets = "assets/PaginaCakes/";
    }
    virtual ~CakePage() override = default;
};
#endif // CAKEPAGE_H
