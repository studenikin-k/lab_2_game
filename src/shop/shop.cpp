#include "shop.h"


void shop::showContents() {

    bool exit = false;

    while (!exit) {
        int action;
        std::cout << "Выберите что вы хотите купить: \n";
        std::cout << "1. Снаряжение. \n";
        std::cout << "2. Оружие. \n";
        std::cout << "3. Зелья. \n\n";
        std::cout << "4. Выйти из магазина.\n\n";
        std::cout << "Введите число:  ";

        std::cin >> action;

        std::cout << std::endl << std::endl;

        static auto level = main_char::getLevel();

        unsigned int counter = 1;

        switch (action) {
            case 1:

                std::cout << "Выберите какой тип снаряжения вы хотите купить: \n\n";
                std::cout << "1. Шлем.\n";
                std::cout << "2. Нагрудник.\n";
                std::cout << "3. Перчатки.\n";
                std::cout << "4. Штаны.\n";
                std::cout << "5. Ботинки. \n\n";

                std::cout << "Введите число: ";

                int typeOfEquip;

                std::cin >> typeOfEquip;

                std::cout << std::endl << std::endl;

                slotOfEquipment slot;

                switch (typeOfEquip) {
                    case 1:
                        slot = slotOfEquipment::Helmet;
                        break;
                    case 2:
                        slot = slotOfEquipment::Chestplate;
                        break;
                    case 3:
                        slot = slotOfEquipment::Gloves;
                        break;
                    case 4:
                        slot = slotOfEquipment::Pants;
                        break;
                    case 5:
                        slot = slotOfEquipment::Boots;
                        break;
                    default:
                        std::cout << "Пошли вон с моего магазина!" << std::endl;
                        std::cout << "*Вас выгнали с магазина за недостойное поведение.*" << std::endl;

                        exit = true;
                        break;
                }

                std::cout << "-------------------" << std::endl;
                for (int i = 0; i <= level; i++) {
                    for (auto &it: equipmentShop[i][slot]) {
                        if (it.second->getSlot() == slot) {
                            std::cout << "Лот номер:" << counter << std::endl;
                            it.second->showInShop();
                            std::cout << "-------------------" << std::endl;
                            counter++;
                        }
                    }
                }
                std::cout << std::endl;
                break;
            case 2:
                std::cout << "Выберите какой тип оружия вы хотите купить: \n\n";
                std::cout << "1. Топоры.\n";
                std::cout << "2. Булавы.\n";
                std::cout << "3. Мечи.\n";
                std::cout << "4. Клинки.\n";
                std::cout << "5. Шпаги.\n";
                std::cout << "6. Вилы.\n";
                std::cout << "7. Глефы.\n";
                std::cout << "8. Копья.\n";


                std::cout << "Введите число: ";

                int typeOfWeapon;

                std::cin >> typeOfWeapon;

                std::cout << std::endl << std::endl;

                slotOfWeapon weapon;

                switch (typeOfWeapon) {

                    case 1:
                        weapon = slotOfWeapon::Axe;
                        break;
                    case 2:
                        weapon = slotOfWeapon::Mace;
                        break;
                    case 3:
                        weapon = slotOfWeapon::Sword;
                        break;
                    case 4:
                        weapon = slotOfWeapon::Blade;
                        break;
                    case 5:
                        weapon = slotOfWeapon::Epee;
                        break;
                    case 6:
                        weapon = slotOfWeapon::Fork;
                        break;
                    case 7:
                        weapon = slotOfWeapon::Glaive;
                        break;
                    case 8:
                        weapon = slotOfWeapon::Spear;
                        break;
                    default:
                        std::cout << "Пошли вон с моего магазина!" << std::endl << std::endl;

                        std::cout << "*Вас выгнали с магазина за недостойное поведение.*" << std::endl;
                        exit = true;
                        break;
                }
                std::cout << "-------------------" << std::endl;
                for (int i = 0; i <= level; i++) {
                    for (auto &it: weaponShop[i][weapon]) {
                        if (it.second->getSlot() == weapon) {
                            std::cout << "Лот номер:" << counter << std::endl;
                            it.second->showInShop();
                            std::cout << "-------------------" << std::endl;
                            counter++;
                        }
                    }
                }
                std::cout << std::endl;
                break;

            case 3:
                std::cout << "Выберите какой тип зелья вы хотите купить: \n\n";
                std::cout << "1. Здоровья.\n";
                std::cout << "2. Урона.\n";
                std::cout << "3. Брони.\n";
                std::cout << "4. Точности.\n";
                std::cout << "5. Олгушения.\n";
                std::cout << "6. Уворота.\n";

                std::cout << "Введите число: ";

                int typeOfPotion;

                std::cin >> typeOfPotion;

                std::cout << std::endl << std::endl;

                slotOfPotion potion;

                switch (typeOfPotion) {

                    case 1:
                        potion = slotOfPotion::Health;
                        break;
                    case 2:
                        potion = slotOfPotion::Damage;
                        break;
                    case 3:
                        potion = slotOfPotion::Armor;
                        break;
                    case 4:
                        potion = slotOfPotion::Accuracy;
                        break;
                    case 5:
                        potion = slotOfPotion::Stun;
                        break;
                    case 6:
                        potion = slotOfPotion::Dodge;
                        break;
                    default:
                        std::cout << "Пошли вон с моего магазина!" << std::endl << std::endl;

                        std::cout << "*Вас выгнали с магазина за недостойное поведение.*" << std::endl;
                        exit = true;
                        break;
                }
                std::cout << "-------------------" << std::endl;
                for (int i = 0; i <= level; i++) {
                    for (auto &it: potionShop[i]) {
                        if (it.second->getSlot() == potion) {
                            std::cout << "Лот номер:" << counter << std::endl;
                            it.second->showInShop();
                            std::cout << "-------------------" << std::endl;
                            counter++;
                        }
                    }
                }
                std::cout << std::endl;

            case 4:
                exit = true;
                break;
            default:
                std::cout << "Пошли вон с моего магазина! \n\n";
                std::cout << "*Вас выгнали с магазина за недостойное поведение.*" << std::endl;
                exit = true;
                break;
        }
    }

}