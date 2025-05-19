#include "bag.h"
#include <algorithm>
#include <vector>
#include <limits>
#include "../../characters/main_char/main_char.h"


void bag::inputIntoBag(std::shared_ptr<equipment> item) {
    bagEquipment.push_back(std::move(item));
}

void bag::inputIntoBag(std::shared_ptr<weapon> Gun) {
    bagWeapon.push_back(std::move(Gun));
}

void bag::inputIntoBag(std::shared_ptr<potion> Potion) {
    bagPotion.push_back(std::move(Potion));
}



