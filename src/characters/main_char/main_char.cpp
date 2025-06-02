#include "../../include/all_headers.h"
#include <limits>


main_char::main_char(const std::string &_name, const unsigned int _level, const unsigned int _health,
                     const unsigned int _damage,
                     const unsigned int _armor, const unsigned int _accuracy, const unsigned int _stun,
                     const unsigned int _dodge, const coins &cash,
                     const unsigned int position) : level(_level), balance(cash) {
    setName(_name);
    setLevel(_level);
    setHealth(_health);
    setDamage(_damage);
    setArmor(_armor);
    setAccuracy(_accuracy);
    setStun(_stun);
    setDodge(_dodge);
    setCurrentPosition(position);

    gun = nullptr;


    Equipment = {
        {slotOfEquipment::Helmet, nullptr},
        {slotOfEquipment::Chestplate, nullptr},
        {slotOfEquipment::Gloves, nullptr},
        {slotOfEquipment::Pants, nullptr},
        {slotOfEquipment::Boots, nullptr}
    };
}

const std::string &main_char::getName() const {
    return name;
}

void main_char::setName(const std::string &_name) {
    name = _name;
}

unsigned int main_char::getLevel() const {
    return level;
}

void main_char::setLevel(unsigned int _level) {
    level = _level;
}


unsigned int main_char::getExperience() const {
    return experience;
}

void main_char::setExperience(const unsigned int experience) {
    this->experience = experience;
}

unsigned int main_char::getExperienceToLevelUp() const {
    return experienceToLevelUp;
}

void main_char::setExperienceToLevelUp(const unsigned int experience_to_level_up) {
    experienceToLevelUp = experience_to_level_up;
}

unsigned int main_char::getCurrentPosition() const {
    return currentPosition;
}

void main_char::setCurrentPosition(unsigned int current_position) {
    currentPosition = current_position;
}

unsigned int main_char::id1() const {
    return id;
}

void main_char::set_id(unsigned int id) {
    this->id = id;
}

void main_char::equip(std::shared_ptr<equipment> item) {
    if (!item) return;

    slotOfEquipment slot = item->slot;

    if (getLevel() < item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня предмета: " << item->getName() << std::endl;
        return;
    }


    if (Equipment[slot] != nullptr) {
        setHealth(getHealth() - Equipment[slot]->getHealth());
        setArmor(getArmor() - Equipment[slot]->getArmor());
        setDodge(getDodge() - Equipment[slot]->getDodge());

        std::cout << "Снято: " << Equipment[slot]->getName() << std::endl;


        Bag.inputIntoBag(std::move(Equipment[slot]));
    }


    Equipment[slot] = std::move(item);

    setHealth(getHealth() + Equipment[slot]->getHealth());
    setArmor(getArmor() + Equipment[slot]->getArmor());
    setDodge(getDodge() + Equipment[slot]->getDodge());

    std::cout << "Надето: " << Equipment[slot]->getName() << std::endl;
}


void main_char::takeOffEquipment(std::shared_ptr<equipment> item) {
    if (!item) {
        std::cout << "Ошибка: передан пустой предмет!" << std::endl;
        return;
    }

    slotOfEquipment slot = item->slot;

    if (Equipment[slot]) {
        setHealth(getHealth() - Equipment[slot]->getHealth());
        setArmor(getArmor() - Equipment[slot]->getArmor());
        setDodge(getDodge() - Equipment[slot]->getDodge());

        std::cout << "Снято: " << Equipment[slot]->getName() << std::endl;


        Bag.inputIntoBag(std::move(Equipment[slot]));

        Equipment[slot] = nullptr;
    } else {
        std::cout << "В этом слоте ничего не надето.\n";
    }
}


void main_char::equip(std::shared_ptr<weapon> item) {
    if (!item) return;

    if (getLevel() < item->getLevel()) {
        std::cout << "Невозможно надеть, ваш уровень ниже уровня предмета: " << item->getName() << std::endl;
        return;
    }


    if (gun != nullptr) {
        setDamage(getDamage() - gun->getDamage());
        setAccuracy(getAccuracy() - gun->getAccuracy());
        setStun(getStun() - gun->getStun());

        std::cout << "Снято: " << gun->getName() << std::endl;


        Bag.inputIntoBag(std::move(gun));
    }


    gun = std::move(item);

    setDamage(getDamage() + gun->getDamage());
    setAccuracy(getAccuracy() + gun->getAccuracy());
    setStun(getStun() + gun->getStun());

    std::cout << "Надето: " << gun->getName() << std::endl;
}


void main_char::takeOffWeapon() {
    if (gun) {
        setDamage(getDamage() - gun->getDamage());
        setAccuracy(getAccuracy() - gun->getAccuracy());
        setStun(getStun() - gun->getStun());

        std::cout << "Снято: " << gun->getName() << std::endl;


        Bag.inputIntoBag(std::move(gun));
    } else {
        std::cout << "Оружие не экипировано.\n";
    }
}


bool main_char::isBeltFull() const {
    return std::none_of(Belt.begin(), Belt.end(), [](const std::shared_ptr<potion> &p) { return p == nullptr; });
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

void main_char::equip(std::shared_ptr<potion> item) {
    if (!item) return;

    if (getLevel() < item->getLevel()) {
        std::cout << "Недостаточный уровень для зелья, невозможно надеть: " << item->getName() << std::endl;
        return;
    }


    for (size_t i = 0; i < Belt.size(); ++i) {
        if (Belt[i] == nullptr) {
            Belt[i] = std::move(item);
            std::cout << "Зелье добавлено в ячейку " << i + 1 << ": " << Belt[i]->getName() << std::endl;
            return;
        }
    }


    std::cout << "Пояс переполнен! Выберите зелье для замены (1-" << BELT_SIZE << ") или 0 для отмены:" << std::endl;
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
        if (Belt[slot]) {
            std::cout << Belt[slot]->getName() << " заменено на " << item->getName() << std::endl;
            Bag.inputIntoBag(std::move(Belt[slot]));
        }
        Belt[slot] = std::move(item);
    } else if (choice == 0) {
        std::cout << "Действие отменено." << std::endl;
    } else {
        std::cout << "Неверный номер ячейки!" << std::endl;
    }
}

void main_char::takeOffPotion() {
    std::cout << "Введите номер ячейки (1-6) или 0 для отмены: ";
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
        if (Belt[index]) {
            std::cout << "Зелье " << Belt[index]->getName() << " снято с пояса." << std::endl;

            Bag.inputIntoBag(std::move(Belt[index]));
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

void main_char::buyEquipment(const std::shared_ptr<equipment> &original) {
    if (!original) return;

    std::shared_ptr<equipment> copyEquipment(original->clone());

    Bag.inputIntoBag(std::move(copyEquipment));
}

void main_char::buyWeapon(const std::shared_ptr<weapon> &original) {
    if (!original) return;
    std::shared_ptr<weapon> copyWeapon = std::make_shared<weapon>(*original);

    Bag.inputIntoBag(std::move(copyWeapon));
}

void main_char::buyPotion(const std::shared_ptr<potion> &original) {
    if (!original) return;

    std::shared_ptr<potion> copyPotion(original->clone());

    Bag.inputIntoBag(std::move(copyPotion));
}

void main_char::showBag() {
    bool exit = false;

    clearScreen();

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

        clearScreen();

        switch (choice) {
            case 1:
                clearScreen();

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
                            break;
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

                clearScreen();

                for (const auto &item: Bag.bagWeapon) {
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
                            break;
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

                clearScreen();

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
                            break;
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
    clearScreen();
    while (true) {
        std::cout << "\nВыберите часть экипировки, которую хотели бы посмотреть:\n";
        std::cout << "1. Снаряжение\n"
                << "2. Оружие\n"
                << "3. Пояс Зелий\n"
                << "4. Окончить осмотр экипировки\n\n"
                << "Выберите действие: ";

        int choiceInGear;
        std::cin >> choiceInGear;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число!\n";
            continue;
        }

        if (choiceInGear == 1) {
            clearScreen();
            while (true) {
                std::cout << "\nТекущее снаряжение:\n";
                int counter = 1;
                for (const auto &it: Equipment) {
                    std::cout << "[" << counter << "]\n";
                    if (it.second != nullptr) {
                        it.second->showInInventory();
                    } else {
                        std::cout << "Пусто.\n";
                    }
                    counter++;
                }

                std::cout << "\nВыберите действие:\n"
                        << "1. Снять часть экипировки\n"
                        << "2. Вернуться в предыдущее меню\n"
                        << "3. Окончить осмотр экипировки\n"
                        << "Ввод: ";

                int choiceInEquipment;
                std::cin >> choiceInEquipment;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка: введите число!\n";
                    continue;
                }

                if (choiceInEquipment == 1) {
                    std::cout << "Введите порядковый номер экипировки: ";
                    int choiceToTakeOff;
                    std::cin >> choiceToTakeOff;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка: введите число!\n";
                        continue;
                    }

                    if (choiceToTakeOff <= 0 || choiceToTakeOff >= counter) {
                        std::cout << "Ошибка: Введите корректный номер!\n";
                        continue;
                    }

                    int currentCounter = 0;
                    for (auto &it: Equipment) {
                        if (currentCounter + 1 == choiceToTakeOff) {
                            takeOffEquipment(it.second);
                            break;
                        }
                        currentCounter++;
                    }
                    break;
                } else if (choiceInEquipment == 2) {
                    break;
                } else if (choiceInEquipment == 3) {
                    return;
                } else {
                    std::cout << "Введено неверное число!\n";
                }
            }
        } else if (choiceInGear == 2) {
            clearScreen();

            while (true) {
                if (gun != nullptr) {
                    std::cout << "\nТекущее оружие:\n";
                    gun->showInInventory();

                    std::cout << "\nВыберите действие:\n"
                            << "1. Снять " << gun->getName() << "\n"
                            << "2. Вернуться в предыдущее меню\n"
                            << "3. Окончить осмотр экипировки\n"
                            << "Ввод: ";

                    int choiceToTakeOff;
                    std::cin >> choiceToTakeOff;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка: введите число!\n";
                        continue;
                    }

                    if (choiceToTakeOff == 1) {
                        takeOffWeapon();
                        break;
                    } else if (choiceToTakeOff == 2) {
                        break;
                    } else if (choiceToTakeOff == 3) {
                        return;
                    } else {
                        std::cout << "Введено неверное число!\n";
                    }
                } else {
                    std::cout << "\nОружие не экипировано!\n";
                    break;
                }
            }
        } else if (choiceInGear == 3) {
            clearScreen();

            while (true) {
                std::cout << "\nПояс зелий:\n";
                displayBelt();

                std::cout << "\nВыберите действие:\n"
                        << "1. Снять зелье с пояса\n"
                        << "2. Вернуться в предыдущее меню\n"
                        << "3. Окончить осмотр экипировки\n"
                        << "Ввод: ";

                int choiceToTakeOff;
                std::cin >> choiceToTakeOff;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка: введите число!\n";
                    continue;
                }

                if (choiceToTakeOff == 1) {
                    takeOffPotion();
                    break;
                } else if (choiceToTakeOff == 2) {
                    break;
                } else if (choiceToTakeOff == 3) {
                    return;
                } else {
                    std::cout << "Введено неверное число!\n";
                }
            }
        } else if (choiceInGear == 4) {
            return;
        } else {
            std::cout << "Введено неверное число!\n";
        }
    }
}

void main_char::usePotion() {

    std::cout << "Выберите зелье, которое хотите использовать: \n";


    displayBelt();

    std::cout << "Введите номер ячейки (1-6) или 0 для отмены: ";
    int slot;
    std::cin >> slot;


    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите число!" << std::endl;
        return;
    }

    if (slot == 0) {
        std::cout << "Действие отменено." << std::endl;
        return;
    }

    if (slot < 1 || slot > BELT_SIZE) {
        std::cout << "Неверный номер ячейки!" << std::endl;
        return;
    }

    size_t index = static_cast<size_t>(slot - 1);

    if (!Belt[index]) {
        std::cout << "Ячейка " << slot << " пуста!" << std::endl;
        return;
    }

    std::shared_ptr<potion> p = Belt[index];


    if (auto hp = std::dynamic_pointer_cast<healthPotion>(p)) {
        std::cout << "Вы использовали: " << hp->getName() << std::endl;
        health += hp->getHealth();
    } else if (auto dp = std::dynamic_pointer_cast<damagePotion>(p)) {
        std::cout << "Вы использовали: " << hp->getName() << std::endl;
        damage += dp->getDamage();
    } else if (auto ap = std::dynamic_pointer_cast<armorPotion>(p)) {
        std::cout << "Вы использовали: " << hp->getName() << std::endl;
        armor += ap->getArmor();
    } else if (auto acp = std::dynamic_pointer_cast<accuracyPotion>(p)) {
        std::cout << "Вы использовали: " << hp->getName() << std::endl;
        accuracy += acp->getAccuracy();
    } else if (auto sp = std::dynamic_pointer_cast<stunPotion>(p)) {
        std::cout << "Вы использовали: " << hp->getName() << std::endl;
        stun += sp->getStun();
    } else if (auto dpd = std::dynamic_pointer_cast<dodgePotion>(p)) {
        std::cout << "Вы использовали: " << hp->getName() << std::endl;
        dodge += dpd->getDodge();
    } else {
        std::cout << "Неизвестное зелье. Эффект не применён.\n";
        return;
    }

    Belt[index] = nullptr;

    std::cout << "Зелье было использовано и удалено из пояса.\n";
}
