#include "bag.h"
#include <algorithm>
#include <vector>



void bag::inputIntoBag(equipment* item) {


    bagEquipment.push_back(item);

}

void bag::inputIntoBag(weapon* Gun) {

    bagWeapon.push_back(Gun);

}

void bag::inputIntoBag(potion* Potion) {

    bagPotion.push_back(Potion);

}

void bag::outputEquipmentFromBag(const std::string &_name) {
    std::erase_if(bagEquipment, [&_name](const auto &item) {
        return item->getName() == _name;
    });
}

void bag::outputWeaponFromBag(const std::string &_name) {
    std::erase_if(bagWeapon, [&_name](const auto &item) {
        return item->getName() == _name;
    });
}

    void bag::outputPotionFromBag(const std::string &_name) {
        std::erase_if(bagPotion, [&_name](const auto &item) {
            return item->getName() == _name;
        });
    }


