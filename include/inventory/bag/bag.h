#ifndef LAB_2_GAME_BAG_H
#define LAB_2_GAME_BAG_H
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include "../../all_headers.h"

    class bag {
    public:
        bag() = default;

         void inputIntoBag(std::shared_ptr<equipment> item);

         void inputIntoBag(std::shared_ptr<weapon> gun);

         void inputIntoBag(std::shared_ptr<potion> potion);

        void outputEquipmentFromBag(const std::string &name);

        void outputWeaponFromBag(const std::string &name);

        void outputPotionFromBag(const std::string &name);

        std::vector<std::shared_ptr<equipment> > bagEquipment; // контейнер снаряжения
        std::vector<std::shared_ptr<weapon> > bagWeapon; // контейнер оружия
        std::vector<std::shared_ptr<potion> > bagPotion; // контейнер зелья
    };


#endif //LAB_2_GAME_BAG_H
