#include "bag.h"
#include <algorithm>
#include <vector>

void bag::inputIntoBag(std::unique_ptr<equipment> item) {


    bagEquipment.push_back(std::move(item));

}

void bag::inputIntoBag(std::unique_ptr<weapon> Gun) {

    bagWeapon.push_back(std::move(Gun));

}

void bag::inputIntoBag(std::unique_ptr<potion> Potion) {

    bagPotion.push_back(std::move(Potion));

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


