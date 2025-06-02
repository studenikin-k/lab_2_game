#include "../include/all_headers.h"
#include <limits>


void shop::showContents(main_char &hero) {
    bool exit = false;

    clearScreen();

    while (!exit) {
        int action;
        std::cout << "Добро пожаловать в магазин, Воин! А ты как всегда свеж и бодр, чего желаете купить сегодня?\n";
        std::cout << "Выберите что вы хотите купить: \n";
        std::cout << "1. Снаряжение. \n";
        std::cout << "2. Оружие. \n";
        std::cout << "3. Зелья. \n\n";
        std::cout << "4. Выйти из магазина.\n\n";
        std::cout << "Введите число:  ";

        if (!(std::cin >> action)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
            continue;
        }
        std::cout << std::endl << std::endl;

        unsigned level = hero.getLevel();

        unsigned int counter = 1;

        clearScreen();

        switch (action) {
            case 1:
                std::cout << "-О у меня новые товары, присмотрись, думаю ты найдёшь что тебе нужно!" << std::endl;
                std::cout << "Выберите какой тип снаряжения вы хотите купить: \n\n";
                std::cout << "1. Шлем.\n";
                std::cout << "2. Нагрудник.\n";
                std::cout << "3. Перчатки.\n";
                std::cout << "4. Штаны.\n";
                std::cout << "5. Ботинки. \n\n";
                std::cout << "6. Выйти из раздела 'Снаряжение'.\n";
                std::cout << "7. Выйти из магазина. \n\n";

                std::cout << "Введите число: ";

                int typeOfEquip;


                if (!(std::cin >> typeOfEquip)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
                    std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
                    continue;
                }

                if (typeOfEquip == 6) {
                    std::cout << "*Вы вышли из раздела 'Снаряжение'* \n\n";
                    break;
                } else if (typeOfEquip == 7) {
                    std::cout << "Ну, удачной охоты, воин!\n";
                    std::cout << "*Вы вышли из магазина* \n\n";
                    exit = true;
                    break;
                }

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
                        std::cout << "*Вас выгнали с магазина за недостойное поведение* \n" << std::endl;

                        exit = true;
                        break;
                }

                clearScreen();

                for (int i = 0; i <= level; i++) {
                    for (auto &it: equipmentShop[i][slot]) {
                        if (it.second->getSlot() == slot) {
                            std::cout << "-------------------" << std::endl;
                            std::cout << "Лот номер:" << counter << std::endl;
                            it.second->showInShop();
                            std::cout << "-------------------" << std::endl;
                            counter++;
                        }
                    }
                }

                std::cout << std::endl;


                std::cout << "1. Купить снаряжение типа '" << slotOfEquipmentToString(slot) << "'. \n";
                std::cout << "2. Выйти из раздела 'Снаряжение'. \n";
                std::cout << "3. Выйти из магазина. \n\n";


                std::cout << "Выберите действие: ";

                int choiceInEquipment;

                if (!(std::cin >> choiceInEquipment)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
                    std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
                    continue;
                }
                std::cout << std::endl << std::endl;

                if (choiceInEquipment == 1) {
                    int equipLotNum;

                    std::cout << "Ваш баланс: " << hero.balance.showMoney() << "\n";
                    std::cout << "Выберите лот, который вы хотите купить. \n\n";
                    std::cout << "Введите номер лота: ";
                    std::cin >> equipLotNum;
                    std::cout << std::endl << std::endl;

                    if (equipLotNum >= counter || equipLotNum < 1) {
                        std::cout << "Такого лота нет. \n" << std::endl;
                        break;
                    }

                    counter = 0;

                    for (int i = 0; i <= level; i++) {
                        for (auto &it: equipmentShop[i][slot]) {
                            if (counter + 1 == equipLotNum && hero.balance.copper >= it.second->price.
                                copper) {
                                hero.buyEquipment(it.second);
                                std::cout << "Вы купили: " << it.second->getName() << std::endl;
                                std::cout << std::endl;
                                break;
                            } else if (hero.balance.copper < it.second->price.copper) {
                                std::cout << "Недостаточно денег для покупки предмета. \n\n";
                                break;
                            }
                            counter++;
                        }
                    }

                    break;
                } else if (choiceInEquipment == 2) {
                    std::cout << "*Вы вышли из раздела 'Снаряжение'*\n\n";
                    break;
                } else if (choiceInEquipment == 3) {
                    std::cout << "Ну, удачной охоты, воин!\n";
                    std::cout << "*Вы вышли из магазина* \n\n";
                    exit = true;
                    break;
                } else {
                    std::cout << "Пошли вон с моего магазина!" << std::endl;
                    std::cout << "*Вас выгнали с магазина за недостойное поведение* \n" << std::endl;

                    exit = true;
                    break;
                }


            case 2:
                std::cout << "-Оружие всегда хорошо! Выбирай, колющее, режущее, древковое, подлиннее, покороче?\n";
                std::cout << "Выберите какой тип оружия вы хотите купить: \n\n";
                std::cout << "1. Топоры.\n";
                std::cout << "2. Булавы.\n";
                std::cout << "3. Мечи.\n";
                std::cout << "4. Клинки.\n";
                std::cout << "5. Шпаги.\n";
                std::cout << "6. Вилы.\n";
                std::cout << "7. Глефы.\n";
                std::cout << "8. Копья.\n\n";
                std::cout << "9. Выйти из раздела 'Оружие'. \n";
                std::cout << "10. Выйти из магазина. \n\n";

                std::cout << "Введите число: ";

                int typeOfWeapon;

                if (!(std::cin >> typeOfWeapon)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
                    std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
                    continue;
                }

                if (typeOfWeapon == 9) {
                    std::cout << "Вы вышли из раздела 'Оружие'. \n\n";
                    std::cout << std::endl << std::endl;
                    break;
                } else if (typeOfWeapon == 10) {
                    std::cout << "Ну, удачной охоты, воин!\n";
                    std::cout << "Вы вышли из магазина. \n\n";
                    std::cout << std::endl << std::endl;
                    exit = true;
                    break;
                }
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

                        std::cout << "*Вас выгнали с магазина за недостойное поведение* \n" << std::endl;
                        exit = true;
                        break;
                }

                clearScreen();

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

                std::cout << "1. Купить оружие типа '" << slotOfWeaponToString(weapon) << "'. \n";
                std::cout << "2. Выйти из раздела 'Оружие'. \n";
                std::cout << "3. Выйти из магазина. \n\n";


                std::cout << "Выберите действие: ";

                int choiceInWeapon;

                if (!(std::cin >> choiceInWeapon)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
                    std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
                    continue;
                }

                std::cout << std::endl << std::endl;

                if (choiceInWeapon == 1) {
                    int weaponLotNum;

                    std::cout << "Ваш баланс: " << hero.balance.showMoney() << "\n";
                    std::cout << "Выберите лот, который вы хотите купить.\n\n";
                    std::cout << "Введите номер лота: ";
                    std::cin >> weaponLotNum;
                    std::cout << std::endl << std::endl;

                    if (weaponLotNum >= counter || weaponLotNum < 1) {
                        std::cout << "Такого лота нет.\n" << std::endl;
                        break;
                    }

                    counter = 0;

                    for (int i = 0; i <= level; i++) {
                        for (auto &it: weaponShop[i][weapon]) {
                            if (counter + 1 == weaponLotNum && hero.balance.copper >= it.second->price.copper) {
                                hero.buyWeapon(it.second);
                                std::cout << "Вы купили: " << it.second->getName() << std::endl;
                                std::cout << std::endl;
                                break;
                            } else if (hero.balance.copper < it.second->price.copper) {
                                std::cout << "Недостаточно денег для покупки предмета. \n\n";
                                break;
                            }
                            counter++;
                        }
                    }

                    break;
                } else if (choiceInWeapon == 2) {
                    std::cout << "*Вы вышли из раздела 'Оружие'* \n\n";
                    break;
                } else if (choiceInWeapon == 3) {
                    std::cout << "Ну, удачной охоты, воин!\n";
                    std::cout << "*Вы вышли из магазина* \n\n";
                    exit = true;
                    break;
                } else {
                    std::cout << "Пошли вон с моего магазина!\n" << std::endl;
                    std::cout << "*Вас выгнали с магазина за недостойное поведение* \n" << std::endl;

                    exit = true;
                    break;
                }


            case 3:
                std::cout << "-Выбирай, всё только то, что пожелает душа воина.\n";
                std::cout << "Выберите какой тип зелья вы хотите купить: \n\n";
                std::cout << "1. Здоровья.\n";
                std::cout << "2. Урона.\n";
                std::cout << "3. Брони.\n";
                std::cout << "4. Точности.\n";
                std::cout << "5. Олгушения.\n";
                std::cout << "6. Уворота.\n\n";
                std::cout << "7. Выйти из раздела 'Зелья'\n";
                std::cout << "8. Выйти из магазина\n\n";


                std::cout << "Введите число: ";

                int typeOfPotion;

                if (!(std::cin >> typeOfPotion)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
                    std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
                    continue;
                }

                std::cout << std::endl << std::endl;

                if (typeOfPotion == 7) {
                    std::cout << "Вы вышли из раздела 'Зелья'. \n\n";
                    std::cout << std::endl << std::endl;
                    break;
                } else if (typeOfPotion == 8) {
                    std::cout << "Ну, удачной охоты, воин!\n";
                    std::cout << "*Вы вышли из магазина* \n\n";
                    std::cout << std::endl << std::endl;
                    exit = true;
                    break;
                }

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

                        std::cout << "*Вас выгнали с магазина за недостойное поведение.* \n" << std::endl;
                        exit = true;
                        break;
                }

                clearScreen();
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


                std::cout << std::endl;

                std::cout << "1. Купить зелье типа '" << slotOfPotionToString(potion) << "'. \n";
                std::cout << "2. Выйти из раздела 'Зелья'. \n";
                std::cout << "3. Выйти из магазина. \n\n";


                std::cout << "Выберите действие: ";

                int choiceInPotion;

                if (!(std::cin >> choiceInPotion)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
                    std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
                    continue;
                }

                std::cout << std::endl << std::endl;

                if (choiceInPotion == 1) {
                    int potionLotNum;

                    std::cout << "Ваш баланс: " << hero.balance.showMoney() << "\n";
                    std::cout << "Выберите лот, который вы хотите купить. \n\n";
                    std::cout << "Введите номер лота: ";
                    std::cin >> potionLotNum;
                    std::cout << std::endl << std::endl;

                    if (potionLotNum >= counter || potionLotNum < 1) {
                        std::cout << "Такого лота нет. \n" << std::endl;
                        break;
                    }

                    counter = 0;

                    for (int i = 0; i <= level; i++) {
                        for (auto &it: potionShop[i]) {
                            if (counter + 1 == potionLotNum && hero.balance.copper >= it.second->price.copper) {
                                hero.buyPotion(it.second);
                                std::cout << "Вы купили: " << it.second->getName() << std::endl;
                                std::cout << std::endl;
                                break;
                            } else if (hero.balance.copper < it.second->price.copper) {
                                std::cout << "Недостаточно денег для покупки предмета. \n\n";
                                break;
                            }
                            counter++;
                        }
                    }
                    break;
                } else if (choiceInPotion == 2) {
                    std::cout << "*Вы вышли из раздела 'Зелья'* \n\n";
                    break;
                } else if (choiceInPotion == 3) {
                    std::cout << "Ну, удачной охоты, воин!\n";
                    std::cout << "*Вы вышли из магазина* \n\n";
                    exit = true;
                    break;
                } else {
                    std::cout << "Пошли вон с моего магазина! \n" << std::endl;
                    std::cout << "*Вас выгнали с магазина за недостойное поведение* \n" << std::endl;

                    exit = true;
                    break;
                }


            case 4:
                std::cout << "Ну, удачной охоты, воин!\n";
                std::cout << "*Вы вышли из магазина* \n\n";
                exit = true;
                break;
            default:
                std::cout << "Пошли вон с моего магазина! \n\n";
                std::cout << "*Вас выгнали с магазина за недостойное поведение.* \n" << std::endl;
                exit = true;
                break;
        }
    }
}
