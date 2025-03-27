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

     void inputIntoBag(std::unique_ptr<equipment> item);

     void inputIntoBag(std::unique_ptr<weapon> gun);

     void inputIntoBag(std::unique_ptr<potion> potion);

    void outputEquipmentFromBag(const std::string &name);

    void outputWeaponFromBag(const std::string &name);

    void outputPotionFromBag(const std::string &name);

    std::vector<std::unique_ptr<equipment> > bagEquipment;
    std::vector<std::unique_ptr<weapon> > bagWeapon;
    std::vector<std::unique_ptr<potion> > bagPotion;
};


#endif //LAB_2_GAME_BAG_H
