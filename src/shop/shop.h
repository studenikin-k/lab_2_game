#ifndef LAB_2_GAME_SHOP_H
#define LAB_2_GAME_SHOP_H

#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include "../inventory/equipment/equipment.h"
#include "../inventory/weapon/weapon.h"
#include "../inventory/potion/potion.h"
#include "../utils/war_style.h"
#include "../utils/slot_of_potion.h"
#include "../utils/slot_of_equipment.h"
#include "../utils/slot_of_weapon.h"
#include "../characters/main_char.h"


class shop {
public:
    shop()=default;
    ~shop() = default;

    std::array<std::unordered_map<slotOfEquipment,std::unordered_map<warStyle,std::unique_ptr<equipment>>>,5> equipmentShop{};

    std::array<std::unordered_map<slotOfWeapon,std::unordered_map<warStyle,std::unique_ptr<weapon>>>,5>  weaponShop{};

    std::array<std::unordered_map<slotOfPotion, std::unique_ptr<potion>>,5>  potionShop{};



    void showContents();
};



#endif //LAB_2_GAME_SHOP_H
