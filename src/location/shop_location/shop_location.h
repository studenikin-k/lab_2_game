#ifndef SHOP_LOCATION_H
#define SHOP_LOCATION_H
#include "../location.h"
#include "../shop/shop.h"
#include "../potion/potion.h"
#include "../utils/slot_of_equipment.h"
#include "../utils/slot_of_weapon.h"
#include "../utils/slot_of_potion.h"
#include "../utils/war_style.h"


class shop_location : public location {
public:
    explicit shop_location(const std::string &name);

    shop Market;

    ~shop_location() override = default;
};


#endif //SHOP_LOCATION_H
