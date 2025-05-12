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
}

const std::string &main_char::getName() const {
    return name;
}

void main_char::setName(const std::string &_name) {
    name = _name;
}

unsigned int main_char::getLevel() {
    return level;
}

void main_char::setLevel(unsigned int _level) {
    level = _level;
}


void main_char::equip(equipment *item) {
    slotOfEquipment slot = item->slot;

    if (getLevel() < item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня предмета: " << item->getName() << std::endl;
        return;
    }

    if (Equipment.contains(slot) && Equipment[slot] != nullptr) {
        setHealth(getHealth() - Equipment[slot]->getHealth());
        setArmor(getArmor() - Equipment[slot]->getArmor());
        setDodge(getDodge() - Equipment[slot]->getDodge());


        std::cout << "Снято: " << Equipment[slot]->getName() << std::endl;

        Bag.inputIntoBag(Equipment[slot]);
    }


    Equipment[slot] = item;

    setHealth(getHealth() + Equipment[slot]->getHealth());
    setArmor(getArmor() + Equipment[slot]->getArmor());
    setDodge(getDodge() + Equipment[slot]->getDodge());

    Bag.outputEquipmentFromBag(item->getName());

    std::cout << "Надето: " << Equipment[slot]->getName() << std::endl;
}

void main_char::takeOff(const equipment *item) {
    const slotOfEquipment slot = item->slot;
    if (Equipment[slot] != nullptr) {
        setHealth(main_char::getHealth() - Equipment[slot]->getHealth());
        setArmor(main_char::getArmor() - Equipment[slot]->getArmor());
        setDodge(main_char::getDodge() - Equipment[slot]->getDodge());

        std::cout << "Снято:" << Equipment[slot]->getName() << std::endl;

        Bag.inputIntoBag(Equipment[slot]);

        Equipment[slot] = nullptr;

        return;
    }
    std::cout << "Ничего не надето. \n";
}

void main_char::equip(weapon *item) {
    slotOfWeapon slot = item->slot;

    if (getLevel() < item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня предмета: " << item->getName() << std::endl;

        return;
    }

    if (gun->slot == slot) {
        setDamage(getDamage() - gun->getDamage());
        setAccuracy(getAccuracy() - gun->getAccuracy());
        setStun(getStun() - gun->getStun());

        std::cout << "Снято: " << gun->getName() << std::endl;

        Bag.inputIntoBag(gun);
    }


    setDamage(getDamage() + item->getDamage());
    setAccuracy(getAccuracy() + item->getAccuracy());
    setStun(getStun() + item->getStun());

    gun = item;

    Bag.outputWeaponFromBag(item->getName());

    std::cout << "Надето: " << gun->getName() << std::endl;
}

void main_char::takeOffWeapon() {
    if (!gun) {
        setHealth(getDamage() - gun->getDamage());
        setArmor(getAccuracy() - gun->getAccuracy());
        setDodge(getStun() - gun->getStun());

        std::cout << "Снято:" << gun->getName() << std::endl;

        Bag.inputIntoBag(gun);

        return;
    }

    std::cout << "Ничего не надето. \n";
}


bool main_char::isBeltFull() const {
    return std::none_of(Belt.begin(), Belt.end(), [](potion *p) { return p == nullptr; });
}


void main_char::displayBelt() const {
    std::cout << "=== Содержимое пояса ===" << std::endl;
    for (size_t i = 0; i < Belt.size(); ++i) {
        std::cout << "[" << i + 1 << "] \n";
        if (Belt[i]) {
            Belt[i]->showInInventory();
        } else {
            std::cout << "Пусто";
        }
        std::cout << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

void main_char::equip(potion *item) {
    if (getLevel() < item->getLevel()) {
        std::cout << "Недостаточный уровень для зелья, невозможно надеть: " << item->getName() << std::endl;
        return;
    }

    if (!isBeltFull()) {
        for (size_t i = 0; i < Belt.size(); ++i) {
            if (Belt[i] == nullptr) {
                Belt[i] = item;
                std::cout << "Зелье " << item->getName() << " добавлено в ячейку " << i + 1 << std::endl;
                return;
            }
        }
    }

    std::cout << " Пояс переполнен! Выберите зелье для замены (1-10) или 0 для отмены:" << std::endl;
    displayBelt();

    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите число!" << std::endl;
        return;
    }


    if (choice >= 1 && choice <= BELT_SIZE) {
        size_t slot = choice - 1;
        std::cout << Belt[slot]->getName() << " заменено на " << item->getName() << std::endl;
        Bag.inputIntoBag(Belt[slot]);
        Belt[slot] = item;
    } else if (choice == 0) {
        std::cout << "Действие отменено." << std::endl;
    } else {
        std::cout << "Неверный номер ячейки!" << std::endl;
    }
}

void main_char::takeOff() {
    std::cout << "Введите номер ячейки (1-10) или 0 для отмены: ";
    int slot;
    std::cin >> slot;


    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите число!" << std::endl;
        return;
    }


    if (slot >= 1 && slot <= BELT_SIZE) {
        size_t index = slot - 1;
        if (Belt[index] != nullptr) {
            std::cout << "Зелье " << Belt[index]->getName() << " снято с пояса." << std::endl;
            Bag.inputIntoBag(Belt[index]);
            Belt[index] = nullptr;
        } else {
            std::cout << "Ячейка " << slot << " уже пуста!" << std::endl;
        }
    } else if (slot == 0) {
        std::cout << "Действие отменено." << std::endl;
    } else {
        std::cout << "Неверный номер ячейки!" << std::endl;
    }
}

void main_char::buyEquipment(equipment *_item) {
    Bag.inputIntoBag(_item);
    balance.setCopper(balance.copper - _item->price.getCopper());
}

void main_char::buyWeapon(weapon *_weapon) {
    Bag.inputIntoBag(_weapon);
    balance.setCopper(balance.copper - _weapon->price.getCopper());
}

void main_char::buyPotion(potion *_potion) {
    Bag.inputIntoBag(_potion);
    balance.setCopper(balance.copper - _potion->price.getCopper());
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

void main_char::showGear() {
    std::cout << "Выберите часть экипировки, которую хотели бы посмотреть:\n";
    std::cout << "1. Снаряжение.\n" <<
            "2. Оружие.\n" <<
            "3. Пояс Зелий.\n\n" <<
            "4. Окончить осмотр экипировки. \n\n";
    std::cout << "Выберите действие: ";

    int choiceInGear;

    std::cin >> choiceInGear;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите число!" << std::endl;
        return;
    }

    if (choiceInGear == 1) {
        int counter = 1;
        for (const auto &it: Equipment) {
            std::cout << "[" << counter << "]\n";
            if (it.second != nullptr) {
                it.second->showInInventory();
            } else {
                std::cout << "Пусто." << std::endl;
            }
            counter++;
        }
        std::cout << std::endl;
        std::cout << "Выберите Действие: \n";
        std::cout << "1. Снять часть экипировки.\n";
        std::cout << "2. Выйти из раздела\n";
        std::cout << "3. Окончить осмотр экипировки \n";

        int choiceInEquipment;

        std::cin >> choiceInEquipment;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число!" << std::endl;
            return;
        }

        if (choiceInEquipment == 1) {
            std::cout << "Введите порядковый номер экипировки: ";

            int choiceToTakeOff;

            std::cin >> choiceToTakeOff;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: введите число!" << std::endl;
                return;
            } else if (choiceToTakeOff <= 0 || choiceToTakeOff >= counter) {
                std::cout << "Ошибка: Введите корректный номер!\n";
                return;
            }

            std::cout<<std::endl;

            counter = 0;

            for (int i = 0; i <= level; i++) {
                for (auto &it: Equipment) {
                    if (counter + 1 == choiceToTakeOff) {
                        takeOff(it.second);
                        std::cout << "Вы убрали в портфель: " << it.second->getName() << std::endl;
                        std::cout << std::endl;
                        it.second = nullptr;
                        break;
                        }
                    counter++;
                }
            }
        }
    }
}
