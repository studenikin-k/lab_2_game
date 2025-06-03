#ifndef LAB_2_GAME_SHOP_H
#define LAB_2_GAME_SHOP_H

#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include "../all_headers.h"

// класс магазин, который содержит в себе три раздела
class shop {
public:
    shop()=default;
    ~shop() = default;

    // сложная структура, которая позволяет взять в себя снаряжение разного уровня, разного стиля боя, и разного типа
    std::array<std::unordered_map<slotOfEquipment,std::unordered_map<warStyle,std::shared_ptr<equipment>>>,5> equipmentShop{};

    // сложная структура, которая позволяет хранить в себе оружие разного уровня, разного стиля боя и разного типа
    std::array<std::unordered_map<slotOfWeapon,std::unordered_map<warStyle,std::shared_ptr<weapon>>>,5>  weaponShop{};

    // сложная структура, которая позволяет храниить в себе зелья разного уровня и разного назначения
    std::array<std::unordered_map<slotOfPotion, std::shared_ptr<potion>>,5>  potionShop{};


    // метод для интерактивного взаимодействия с магазином
    void showContents(main_char& hero);
};



#endif //LAB_2_GAME_SHOP_H
