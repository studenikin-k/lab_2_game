#include "game_mechanics.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "../characters/main_char/main_char.h"
#include "../map/map.h"
#include "../characters/opponent/opponent.h"


void gameLoop(main_char &hero, map &gameMap) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool exitGame = false;
    while (!exitGame) {
        // Вывод главного меню
        std::cout << "\n=== Главное меню ===\n";
        std::cout << "1. Путешествовать по карте\n";
        std::cout << "2. Открыть снаряжение\n";
        std::cout << "3. Открыть портфель\n";
        std::cout << "4. Начать бой с оппонентом\n";
        std::cout << "5. Войти в магазин\n";
        std::cout << "6. Выйти из игры\n";
        std::cout << "Выберите действие (1-6): ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                gameMap.startTravel(hero);
                break;
            case 2:
                hero.showGear();
                break;
            case 3:
                hero.showBag();
                break;
            case 4: {
                if (!gameMap.isBattleLocation(hero)) {
                    std::cout << "Сейчас здесь нельзя начать бой (торговая локация).\n";
                    break;
                }

                auto opponents = gameMap.getOpponents(hero);

                if (opponents.empty()) {
                    std::cout << "На этой локации нет оппонентов.\n";
                    break;
                }

                std::cout << "\n===Список оппонентов===\n";

                for (size_t i = 0; i < opponents.size(); ++i) {
                    std::cout << (i + 1) << ". " << opponents[i]->getName() << "\n";
                }

                std::cout << "Выберите оппонента (номер) или 0 для отмены: ";

                int oppChoice;
                std::cin >> oppChoice;

                if (oppChoice <= 0 || oppChoice > opponents.size()) {
                    std::cout << "Возврат в главное меню.\n";
                    break;
                }

                opponents[oppChoice - 1]->showInfo();
                // Предлагаем начать бой или вернуться
                std::cout << "Начать бой с " << opponents[oppChoice - 1]->getName() <<
                        "? \n\n(1 - согласиться, 2 - уйти): ";
                int fightConfirm;
                std::cin >> fightConfirm;

                if (fightConfirm != 1) {
                    std::cout << "Возврат к списку оппонентов.\n";
                    break;
                }

                unsigned int heroHealthBefore = hero.getHealth();
                unsigned int oppHealthBefore = opponents[oppChoice - 1]->getHealth();
                // Флаги пропуска хода из-за оглушения
                bool heroStunned = false;
                bool oppStunned = false;
                std::cout << "\n=== Бой с " << opponents[oppChoice - 1]->getName() << " начался ===\n";
                // Основной цикл боя
                int turn = 1;
                bool battleOver = false;
                // За один ход герой может использовать одно зелье с пояса
                bool potionUsedThisTurn = false;
                while (!battleOver) {
                    std::cout << "\n-- Ход " << turn << " --\n";
                    // Ход героя
                    if (heroStunned) {
                        std::cout << "Герой оглушен и пропускает свой ход.\n";
                        heroStunned = false; // снимаем оглушение
                    } else {
                        // Предложение использовать зелье (если еще не использовано в этом ходу)
                        if (!potionUsedThisTurn) {
                            std::cout << "Выпить зелье с пояса? (1 - да, 2 - нет): ";
                            int usePotionChoice;
                            std::cin >> usePotionChoice;
                            if (usePotionChoice == 1) {
                                hero.usePotion(); // метод применения зелья
                                potionUsedThisTurn = true;
                            }
                        }
                        // Выбор типа удара
                        std::cout << "Выберите тип удара:\n";
                        std::cout << "1. Удар сверху\n";
                        std::cout << "2. Удар прямо\n";
                        std::cout << "3. Удар снизу\n";
                        std::cout << "Ваш выбор (1-3): ";
                        int hitType;
                        std::cin >> hitType;
                        std::cout << "Герой наносит ";
                        switch (hitType) {
                            case 1: std::cout << "удар сверху.\n";
                                break;
                            case 2: std::cout << "прямой удар.\n";
                                break;
                            case 3: std::cout << "удар снизу.\n";
                                break;
                            default: std::cout << "удар.\n";
                                break;
                        }
                        // Логика попадания
                        int heroAcc = hero.getAccuracy();
                        int oppDodge = opponents[oppChoice - 1]->getDodge();
                        bool hit = false;
                        if (heroAcc >= oppDodge) {
                            hit = true; // стопроцентное попадание
                        } else {
                            // вероятность попадания зависит от разницы
                            int diff = oppDodge - heroAcc;
                            int hitChance = std::max(0, 100 - diff);
                            int roll = std::rand() % 100;
                            if (roll < hitChance) {
                                hit = true;
                            }
                        }
                        if (hit) {
                            std::cout << "Попадание!\n";
                            // Шанс оглушения (например, 20%)
                            int stunRoll = std::rand() % 100;
                            if (stunRoll < 20) {
                                oppStunned = true;
                                std::cout << "Оппонент оглушен!\n";
                            }
                            // Расчет урона
                            int baseDmg = hero.getDamage();
                            int damage = 0;
                            if (oppStunned) {
                                // Усиленный урон при оглушении (на 25-35%)
                                int extraPercent = std::rand() % 11 + 25; // 25..35
                                damage = baseDmg + baseDmg * extraPercent / 100;
                                std::cout << "Усиленный удар: ";
                            } else {
                                // Урон варьируется от -10% до +10%
                                int variation = std::rand() % 21 - 10; // -10..10
                                damage = baseDmg + baseDmg * variation / 100;
                                std::cout << "Нанесено ";
                            }
                            // Наносим урон оппоненту
                            int oppHP = opponents[oppChoice - 1]->getHealth();
                            opponents[oppChoice - 1]->setHealth(oppHP - damage);
                            std::cout << damage << " урона " << opponents[oppChoice - 1]->getName() << " ("
                                    << opponents[oppChoice - 1]->getHealth() << " здоровья " << opponents[
                                        oppChoice - 1]->getName() << ").\n";
                        } else {
                            std::cout << hero.getName() << " промахивается.\n";
                        }
                        // Задержка между действиями
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    // Проверяем окончание боя после хода героя
                    if (opponents[oppChoice - 1]->getHealth() <= 0) {
                        std::cout << opponents[oppChoice - 1]->getName() << " повержен!\n";
                        gainExperience(hero, opponents[oppChoice - 1]->getLevel() * 4);
                        hero.balance.copper += opponents[oppChoice - 1]->getLevel() * 1232;
                        battleOver = true;
                        break;
                    }
                    // Ход оппонента
                    if (oppStunned) {
                        std::cout << "Оппонент оглушен и пропускает свой ход.\n";
                        oppStunned = false;
                    } else {
                        std::cout << "Оппонент наносит удар по герою.\n";
                        // Аналогичная логика для оппонента
                        unsigned int oppAcc = opponents[oppChoice - 1]->getAccuracy();
                        unsigned int heroDodge = hero.getDodge();
                        bool hitOpp = false;
                        if (oppAcc >= heroDodge) {
                            hitOpp = true;
                        } else {
                            int diff = heroDodge - oppAcc;
                            int hitChance = std::max(0, 100 - diff);
                            int roll = std::rand() % 100;
                            if (roll < hitChance) {
                                hitOpp = true;
                            }
                        }
                        if (hitOpp) {
                            std::cout << "Попадание по герою!\n";
                            // Шанс оглушения героя (например, 10%)
                            int stunRoll = std::rand() % 100;
                            if (stunRoll < 10) {
                                heroStunned = true;
                                std::cout << "Герой оглушен!\n";
                            }
                            int baseDmg = opponents[oppChoice - 1]->getDamage();
                            int damage = 0;
                            if (heroStunned) {
                                int extraPercent = std::rand() % 11 + 25;
                                damage = baseDmg + baseDmg * extraPercent / 100;
                                std::cout << "Усиленный удар: ";
                            } else {
                                int variation = std::rand() % 21 - 10;
                                damage = baseDmg + baseDmg * variation / 100;
                                std::cout << "Нанесено ";
                            }
                            int heroHP = hero.getHealth();
                            hero.setHealth(heroHP - damage);
                            std::cout << damage << " урона герою (";
                            std::cout << hero.getHealth() << " HP у героя осталось).\n";
                        } else {
                            std::cout << "Оппонент промахивается.\n";
                        }
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    // Проверяем окончание боя после хода оппонента
                    if (hero.getHealth() <= 0) {
                        std::cout << "Вас победил" << opponents[oppChoice - 1]->getName() << "\n";
                        battleOver = true;
                        break;
                    }
                    // Подготовка к следующему ходу
                    turn++;
                    potionUsedThisTurn = false; // в новом ходу можно снова использовать зелье
                }
                std::cout << "=== Бой окончен ===\n";
                // Восстановление здоровья после боя
                hero.setHealth(heroHealthBefore);
                opponents[oppChoice - 1]->setHealth(oppHealthBefore);

                std::cout << "Здоровье восстановлено. Эффекты зелий исчезли.\n";
                break;
            }
            case 5:

                if (!gameMap.isShopLocation(hero)) {
                    std::cout << "В этой локации нет магазина.\n";
                } else {
                    shop Market = gameMap.getShop(hero);
                    Market.showContents(hero);
                }
                break;
            case 6:
                // Выход из игры
                std::cout << "Выход из игры. До новых встреч!\n";
                exitGame = true;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

void gainExperience(main_char &hero, unsigned int expGained) {
    unsigned int totalExp = hero.getExperience();
    unsigned int expToLevel = hero.getExperienceToLevelUp();
    unsigned int level = hero.getLevel();

    totalExp += expGained;

    bool leveledUp = false;

    while (totalExp >= expToLevel) {
        totalExp -= expToLevel;
        level++;
        expToLevel *= 2;
        leveledUp = true;
    }

    hero.setExperience(totalExp);
    hero.setExperienceToLevelUp(expToLevel);
    hero.setLevel(level);

    std::cout << "Вы получили " << expGained << " опыта. "
            << "Текущий опыт: " << totalExp << "/" << expToLevel << ".\n";

    if (leveledUp) {
        notifyLevelUp(hero);
    }
}

void notifyLevelUp(main_char &hero) {
    std::cout << "\n===== ПОЗДРАВЛЯЕМ! =====\n";
    std::cout << hero.getName() << " достиг уровня " << hero.getLevel() << "!\n";


    int oldHealth = hero.getHealth();
    int oldDamage = hero.getDamage();
    int oldArmor = hero.getArmor();
    int oldAccuracy = hero.getAccuracy();
    int oldStun = hero.getStun();
    int oldDodge = hero.getDodge();

    hero.setHealth(static_cast<int>(hero.getHealth() * 1.3f));
    hero.setDamage(static_cast<int>(hero.getDamage() * 1.2f));
    hero.setArmor(static_cast<int>(hero.getArmor() * 1.4f));
    hero.setAccuracy(static_cast<int>(hero.getAccuracy() * 1.3f));
    hero.setStun(static_cast<int>(hero.getStun() * 1.1f));
    hero.setDodge(static_cast<int>(hero.getDodge() * 1.3f));

    std::cout << "\nУлучшены характеристики:\n";
    std::cout << "Здоровье: " << oldHealth << " → " << hero.getHealth() << "\n";
    std::cout << "Урон:     " << oldDamage << " → " << hero.getDamage() << "\n";
    std::cout << "Броня:    " << oldArmor << " → " << hero.getArmor() << "\n";
    std::cout << "Точность: " << oldAccuracy << " → " << hero.getAccuracy() << "\n";
    std::cout << "Оглушение:" << oldStun << " → " << hero.getStun() << "\n";
    std::cout << "Уклонение:" << oldDodge << " → " << hero.getDodge() << "\n";
    std::cout << "=========================\n";
}
