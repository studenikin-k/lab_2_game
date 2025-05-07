#include "main_char.h"
#include <limits>
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


void main_char::equip(equipment *item) {
    slotOfEquipment slot = item->slot;

    if (main_char::getLevel() < item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня предмета: " << item->getName() << std::endl;
        return;
    }

    if (Equipment.contains(slot) && Equipment[slot] != nullptr) {
        main_char::setHealth(main_char::getHealth() - Equipment[slot]->getHealth());
        main_char::setArmor(main_char::getArmor() - Equipment[slot]->getArmor());
        main_char::setDodge(main_char::getDodge() - Equipment[slot]->getDodge());


        std::cout << "Снято: " << Equipment[slot]->getName() << std::endl;

        Bag.inputIntoBag(Equipment[slot]);
    }


    Equipment[slot] = item;

    main_char::setHealth(main_char::getHealth() + Equipment[slot]->getHealth());
    main_char::setArmor(main_char::getArmor() + Equipment[slot]->getArmor());
    main_char::setDodge(main_char::getDodge() + Equipment[slot]->getDodge());

    Bag.outputEquipmentFromBag(item->getName());

    std::cout << "Надето: " << Equipment[slot]->getName() << std::endl;
}

void main_char::takeOff(const equipment *item) {
    const slotOfEquipment slot = item->slot;
    if (Equipment[slot] != nullptr) {
        main_char::setHealth(main_char::getHealth() - Equipment[slot]->getHealth());
        main_char::setArmor(main_char::getArmor() - Equipment[slot]->getArmor());
        main_char::setDodge(main_char::getDodge() - Equipment[slot]->getDodge());

        std::cout << "Снято:" << Equipment[slot]->getName() << std::endl;

        Bag.inputIntoBag(Equipment[slot]);

        Equipment[slot] = nullptr;

        return;
    }
    std::cout << "Ничего не надето. \n";
}

void main_char::equip(weapon *item) {
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

        Bag.inputIntoBag(main_char::gun);
    }


    main_char::setDamage(main_char::getDamage() + item->getDamage());
    main_char::setAccuracy(main_char::getAccuracy() + item->getAccuracy());
    main_char::setStun(main_char::getStun() + item->getStun());

    gun = item;

    Bag.outputWeaponFromBag(item->getName());

    std::cout << "Надето: " << gun->getName() << std::endl;
}

void main_char::takeOffWeapon() {
    if (!main_char::gun) {
        main_char::setHealth(main_char::getDamage() - main_char::gun->getDamage());
        main_char::setArmor(main_char::getAccuracy() - main_char::gun->getAccuracy());
        main_char::setDodge(main_char::getStun() - main_char::gun->getStun());

        std::cout << "Снято:" << main_char::gun->getName() << std::endl;

        Bag.inputIntoBag(main_char::gun);

        return;
    }

    std::cout << "Ничего не надето. \n";
}

void main_char::equip(potion *item) {
    if (main_char::getLevel() < item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня зелья: " << item->getName() << std::endl;

        return;
    }

    const slotOfPotion slot = item->slot;

    if (Potions[slot]) {
        std::cout << "Снято: " << Potions[slot]->getName() << std::endl;

        Bag.inputIntoBag(Potions[slot]);
    }

    Potions[slot] = item;

    std::cout << "Надето: " << Potions[slot]->getName() << std::endl;
}

void main_char::takeOff(potion *item) {
    slotOfPotion slot = item->slot;

    if (Potions[slot] != nullptr) {
        std::cout << "Снято: " << Potions[slot]->getName() << std::endl;

        Bag.inputIntoBag(Potions[slot]);

        Potions[slot] = nullptr;

        return;
    }

    std::cout << "Ничего не надето. \n";
}

void main_char::buyEquipment(equipment *_item) {
    Bag.inputIntoBag(_item);
    main_char::balance.setCopper(main_char::balance.copper - _item->price.getCopper());
}

void main_char::buyWeapon(weapon *_weapon) {
    Bag.inputIntoBag(_weapon);
    main_char::balance.setCopper(main_char::balance.copper - _weapon->price.getCopper());
}

void main_char::buyPotion(potion *_potion) {
    Bag.inputIntoBag(_potion);
    main_char::balance.setCopper(main_char::balance.copper - _potion->price.getCopper());
}

void main_char::showBag() {
    bool exit = false;
    while (!exit) {
        std::cout << "Вы открыли свою сумку, выберите действие:\n"
                << "  1. Просмотреть Снаряжение.\n"
                << "  2. Просмотреть Оружие.\n"
                << "  3. Просмотреть Зелья.\n"
                << "  4. Закрыть сумку.\n\n"
                << "Ваш выбор: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод.\n";
            return;
        }

        unsigned int counter = 1;

        switch (choice) {
            case 1:
                for (const auto &item: Bag.bagEquipment) {
                    std::cout << "-------------------" << std::endl;
                    std::cout << "Предмет номер:" << counter << std::endl;
                    item->showInInventory();
                    std::cout << "-------------------" << std::endl;
                    counter++;
                }

                std::cout << std::endl;
                std::cout << "Выберите действие: \n";
                std::cout << " 1. Надеть предмет.\n"
                        << " 2. Выйти из раздела Снаряжение. \n"
                        << " 3. Закрыть сумку.\n\n"
                        << "Выберите действие:";

                int choiceinEquip;
                if (!(std::cin >> choiceinEquip)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод.\n";
                    return;
                }

                if (choiceinEquip == 1) {
                    int equipLotNum;

                    std::cout << " Выберите предмет, который вы хотели бы надеть. \n\n";
                    std::cout << " Введите порядковый номер предмета: ";
                    std::cin >> equipLotNum;
                    std::cout << std::endl << std::endl;

                    if (equipLotNum >= counter) {
                        std::cout << "Такого предмета нет." << std::endl;
                        break;
                    }

                    counter = 0;

                    for (auto it = Bag.bagEquipment.begin(); it != Bag.bagEquipment.end();) {
                        if (counter + 1 == equipLotNum) {
                            equip(*it);
                            it = Bag.bagEquipment.erase(it);
                        } else {
                            ++it;
                            ++counter;
                        }
                    }
                    break;
                } else if (choiceinEquip == 2) {
                    std::cout << "*Вы вышли из раздела 'Снаряжение'*\n\n";
                    break;
                } else if (choiceinEquip == 3) {
                    std::cout << "*Вы Закрыли сумку* \n\n";
                    exit = true;
                    break;
                } else {
                    std::cout << "*Вы потеряли сознание и выронили сумку*" << std::endl;
                    exit = true;
                    break;
                }

            case 2:

                for (const auto &item: Bag.bagEquipment) {
                    std::cout << "-------------------" << std::endl;
                    std::cout << "Предмет номер:" << counter << std::endl;
                    item->showInInventory();
                    std::cout << "-------------------" << std::endl;
                    counter++;
                }

                std::cout << std::endl;
                std::cout << "Выберите действие: \n";
                std::cout << "1. Взять оружие.\n"
                        << "2. Выйти из раздела 'Оружие'. \n"
                        << "3. Закрыть сумку.\n\n"
                        << "Выберите действие:";

                int choiceinWeapon;
                if (!(std::cin >> choiceinWeapon)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод.\n";
                    return;
                }

                if (choiceinWeapon == 1) {
                    int equipLotNum;

                    std::cout << "Выберите оружие, который вы хотели бы надеть. \n\n";
                    std::cout << "Введите порядковый номер предмета: ";
                    std::cin >> equipLotNum;
                    std::cout << std::endl << std::endl;

                    if (equipLotNum >= counter) {
                        std::cout << "Такого лота нет." << std::endl;
                        break;
                    }

                    counter = 0;

                    for (auto it = Bag.bagWeapon.begin(); it != Bag.bagWeapon.end();) {
                        if (counter + 1 == equipLotNum) {
                            equip(*it);
                            it = Bag.bagWeapon.erase(it);
                        } else {
                            ++it;
                            ++counter;
                        }
                    }
                    break;
                } else if (choiceinWeapon == 2) {
                    std::cout << "*Вы вышли из раздела 'Оружие'*\n\n";
                    break;
                } else if (choiceinWeapon == 3) {
                    std::cout << "*Вы Закрыли сумку* \n\n";
                    exit = true;
                    break;
                } else {
                    std::cout << "*Вы потеряли сознание и выронили сумку*" << std::endl;
                    exit = true;
                    break;
                }

            case 3:

                for (const auto &item: Bag.bagPotion) {
                    std::cout << "-------------------" << std::endl;
                    std::cout << "Предмет номер:" << counter << std::endl;
                    item->showInInventory();
                    std::cout << "-------------------" << std::endl;
                    counter++;
                }

                std::cout << std::endl;
                std::cout << "Выберите действие: \n";
                std::cout << "1. Надеть предмет.\n"
                        << "2. Выйти из раздела 'Зелья'. \n"
                        << "3. Закрыть сумку.\n\n"
                        << "Выберите действие:";

                int choiceInPotion;
                if (!(std::cin >> choiceInPotion)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод.\n";
                    return;
                }

                if (choiceInPotion == 1) {
                    int equipLotNum;

                    std::cout << "Выберите зелье, которое вы хотели бы повесить на пояс. \n\n";
                    std::cout << "Введите порядковый номер зелья: ";
                    std::cin >> equipLotNum;
                    std::cout << std::endl << std::endl;

                    if (equipLotNum >= counter) {
                        std::cout << "Такого лота нет." << std::endl;
                        break;
                    }

                    counter = 0;

                    for (auto it = Bag.bagPotion.begin(); it != Bag.bagPotion.end();) {
                        if (counter + 1 == equipLotNum) {
                            equip(*it);
                            it = Bag.bagPotion.erase(it);
                        } else {
                            ++it;
                            ++counter;
                        }
                    }
                    break;
                } else if (choiceinWeapon == 2) {
                    std::cout << "*Вы вышли из раздела 'Зелья'*\n\n";
                    break;
                } else if (choiceinWeapon == 3) {
                    std::cout << "*Вы Закрыли сумку* \n\n";
                    exit = true;
                    break;
                } else {
                    std::cout << "*Вы потеряли сознание и выронили сумку*" << std::endl;
                    exit = true;
                    break;
                }
            case 4:
                std::cout << "*Вы Закрыли сумку* \n\n";
                exit = true;
                break;
            default:
                std::cout << "Неправильный выбор.\n";
        }
    }
}
