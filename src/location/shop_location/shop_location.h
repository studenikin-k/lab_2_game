#ifndef SHOP_LOCATION_H
#define SHOP_LOCATION_H
#include "../location.h"
#include "../shop/shop.h"

class shop_location : public location {
public:
    explicit shop_location(const std::string &name);

    shop Market;

    ~shop_location() override = default;
};


#endif //SHOP_LOCATION_H
