#ifndef LAB_2_GAME_SHOP_H
#define LAB_2_GAME_SHOP_H

#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include "../all_headers.h"


class shop {
public:
    shop()=default;
    ~shop() = default;

    std::array<std::unordered_map<slotOfEquipment,std::unordered_map<warStyle,std::shared_ptr<equipment>>>,5> equipmentShop{};

    std::array<std::unordered_map<slotOfWeapon,std::unordered_map<warStyle,std::shared_ptr<weapon>>>,5>  weaponShop{};

    std::array<std::unordered_map<slotOfPotion, std::shared_ptr<potion>>,5>  potionShop{};



    void showContents(main_char& hero);
};



#endif //LAB_2_GAME_SHOP_H
