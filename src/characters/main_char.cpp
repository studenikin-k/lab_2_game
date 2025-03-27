#include "main_char.h"

unsigned int main_char::level = 0;

coins main_char::balance{};
bag main_char::Bag{};

main_char::main_char(const std::string &_name, const unsigned int _level, const unsigned int _health,
                    const unsigned int _damage,
                     const unsigned int _armor, const unsigned int _accuracy, const unsigned int _stun,
                     const unsigned int _dodge, const coins &cash) : character() {
    setName(_name);
    setLevel(_level);
    setHealth(_health);
    setDamage(_damage);
    setArmor(_armor);
    setAccuracy(_accuracy);
    setStun(_stun);
    setDodge(_dodge);

    balance.copper = cash.copper;

    gun = nullptr;


    Equipment.emplace(slotOfEquipment::Helmet, nullptr);
    Equipment.emplace(slotOfEquipment::Chestplate, nullptr);
    Equipment.emplace(slotOfEquipment::Gloves, nullptr);
    Equipment.emplace(slotOfEquipment::Pants, nullptr);
    Equipment.emplace(slotOfEquipment::Boots, nullptr);

    Potions.emplace(slotOfPotion::Health, nullptr);
    Potions.emplace(slotOfPotion::Damage, nullptr);
    Potions.emplace(slotOfPotion::Armor, nullptr);
    Potions.emplace(slotOfPotion::Accuracy, nullptr);
    Potions.emplace(slotOfPotion::Stun, nullptr);
    Potions.emplace(slotOfPotion::Dodge, nullptr);

}

const std::string &main_char::getName() const {
    return name;
}

void main_char::setName(const std::string &_name) {
    main_char::name = _name;
}
unsigned int main_char::getLevel() {
    return level;
}

void main_char::setLevel(unsigned int _level) {
    main_char::level = _level;
}



void main_char::equip(std::unique_ptr<equipment> item) {
    slotOfEquipment slot = item->slot;

    if (main_char::getLevel() < item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня предмета: " << item->getName() << std::endl;
        return;
    }

    if (Equipment[slot]) {

        main_char::setHealth(main_char::getHealth() - Equipment[slot]->getHealth());
        main_char::setArmor(main_char::getArmor() - Equipment[slot]->getArmor());
        main_char::setDodge(main_char::getDodge() - Equipment[slot]->getDodge());


        std::cout << "Снято: " << Equipment[slot]->getName() << std::endl;

        Bag.inputIntoBag(std::move(Equipment[slot]));
    }



    Equipment[slot] = std::move(item);

    main_char::setHealth(main_char::getHealth() + Equipment[slot]->getHealth());
    main_char::setArmor(main_char::getArmor() + Equipment[slot]->getArmor());
    main_char::setDodge(main_char::getDodge() + Equipment[slot]->getDodge());

    Bag.outputEquipmentFromBag(item->getName());

    std::cout << "Надето: " << Equipment[slot]->getName() << std::endl;
}

void main_char::takeOff(const std::unique_ptr<equipment> &item) {
    const slotOfEquipment slot = item->slot;
    if (Equipment[slot] != nullptr) {

        main_char::setHealth(main_char::getHealth() - Equipment[slot]->getHealth());
        main_char::setArmor(main_char::getArmor() - Equipment[slot]->getArmor());
        main_char::setDodge(main_char::getDodge() - Equipment[slot]->getDodge());

        std::cout << "Снято:" << Equipment[slot]->getName() << std::endl;

        Bag.inputIntoBag(std::move(Equipment[slot]));

        Equipment[slot] = nullptr;

        return;
    }
    std::cout << "Ничего не надето. \n";
}

void main_char::equip(std::unique_ptr<weapon> item) {
    slotOfWeapon slot = item->slot;

    if (main_char::getLevel() < item->getLevel()) {

        std::cout << "Невозможно надеть, ваш уровень ниже уровня предмета: " << item->getName() << std::endl;

        return;
    }

    if (gun->slot == slot) {

        main_char::setDamage(main_char::getDamage() - gun->getDamage());
        main_char::setAccuracy(main_char::getAccuracy() - gun->getAccuracy());
        main_char::setStun(main_char::getStun() - gun->getStun());

        std::cout << "Снято: " << gun->getName() << std::endl;

        Bag.inputIntoBag(std::move(main_char::gun));
    }


    main_char::setDamage(main_char::getDamage() + item->getDamage());
    main_char::setAccuracy(main_char::getAccuracy() + item->getAccuracy());
    main_char::setStun(main_char::getStun() + item->getStun());

    gun = std::move(item);

    Bag.outputWeaponFromBag(item->getName());

    std::cout << "Надето: " << gun->getName() << std::endl;

}

void main_char::takeOffWeapon() {

    if (!main_char::gun) {

        main_char::setHealth(main_char::getDamage() - main_char::gun->getDamage());
        main_char::setArmor(main_char::getAccuracy() - main_char::gun->getAccuracy());
        main_char::setDodge(main_char::getStun() - main_char::gun->getStun());

        std::cout << "Снято:" << main_char::gun->getName() << std::endl;

        Bag.inputIntoBag(std::move(main_char::gun));

        return;
    }

    std::cout << "Ничего не надето. \n";

}

void main_char::equip(std::unique_ptr<potion> item) {

    if (main_char::getLevel()< item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня зелья: " << item->getName() << std::endl;

        return;
    }

    const slotOfPotion slot = item->slot;

    if (Potions[slot]) {
        std::cout << "Снято: " << Potions[slot]->getName() << std::endl;

        Bag.inputIntoBag(std::move(Potions[slot]));
    }

    Potions[slot] = std::move(item);

    std::cout << "Надето: " << Potions[slot]->getName() << std::endl;
}

void main_char::takeOff(const std::unique_ptr<potion> &item) {
    slotOfPotion slot = item->slot;

    if (Potions[slot] != nullptr) {

        std::cout << "Снято: " << Potions[slot]->getName() << std::endl;

        Bag.inputIntoBag(std::move(Potions[slot]));

        Potions[slot] = nullptr;

        return;
    }

    std::cout<< "Ничего не надето. \n";
}

void main_char::buyEquipment(std::unique_ptr<equipment> _item) {
    Bag.inputIntoBag(std::move(_item));
    main_char::balance.setCopper(main_char::balance.copper - _item->price.getCopper());
}

void main_char::buyWeapon(std::unique_ptr<weapon> _weapon) {
    Bag.inputIntoBag(std::move(_weapon));
    main_char::balance.setCopper(main_char::balance.copper - _weapon->price.getCopper());
}

void main_char::buyPotion(std::unique_ptr<potion> _potion) {
    Bag.inputIntoBag(std::move(_potion));
    main_char::balance.setCopper(main_char::balance.copper - _potion->price.getCopper());
}