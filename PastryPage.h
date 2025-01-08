#ifndef PASTRYPAGE_H
#define PASTRYPAGE_H

#include "ProductPage.h"

class PastryPage : public ProductPage {
public:
    explicit PastryPage( const std::string& buttonText_)
        : ProductPage( buttonText_) {
        assets = "D:/BakeryOOP/assets/PaginaPastries/";
    }
    virtual ~PastryPage() = default;
};

#endif // PASTRYPAGE_H
