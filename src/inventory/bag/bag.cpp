#include "bag.h"
#include <algorithm>
#include <vector>
#include <limits>


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

void bag::showBag() const {
    std::cout << "Что показать?\n"
              << "  1) Снаряжение\n"
              << "  2) Оружие\n"
              << "  3) Зелья\n"
              << "Ваш выбор: ";

    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод.\n";
        return;
    }

    switch (choice) {
        case 1:
            printCategory(bagEquipment, "Снаряжение");
        break;
        case 2:
            printCategory(bagWeapon, "Оружие");
        break;
        case 3:
            printCategory(bagPotion, "Зелья");
        break;
        default:
            std::cout << "Неправильный выбор.\n";
    }
}
