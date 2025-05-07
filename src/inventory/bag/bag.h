#ifndef LAB_2_GAME_BAG_H
#define LAB_2_GAME_BAG_H
#include "../equipment/equipment.h"
#include "../weapon/weapon.h"
#include <vector>
#include <memory>
#include <algorithm>
#include "../potion/potion.h"
#include <unordered_map>

class bag {
public:
    bag() = default;

    void inputIntoBag(equipment *item);

    void inputIntoBag(weapon *gun);

    void inputIntoBag(potion *potion);

    void outputEquipmentFromBag(const std::string &name);

    void outputWeaponFromBag(const std::string &name);

    void outputPotionFromBag(const std::string &name);

    void showBag() ;

    std::vector<equipment *> bagEquipment;
    std::vector<weapon *> bagWeapon;
    std::vector<potion *> bagPotion;

};



#endif //LAB_2_GAME_BAG_H
