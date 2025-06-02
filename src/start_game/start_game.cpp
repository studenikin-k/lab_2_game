#include "../include/all_headers.h"
#include <iostream>
#include <string>
#include <memory>
#include <limits>






void startGameMenu() {
    main_char hero("Default Hero", 1, 15, 10, 5, 10, 0, 5, coins{300}, 0);
    map gameMap;


    bool gameStarted = false;
    while (!gameStarted) {
        std::cout << "\n=== ДОБРО ПОЖАЛОВАТЬ! ===\n";
        std::cout << "1. Новая игра\n";
        std::cout << "2. Загрузить игру\n";
        std::cout << "3. Выход из игры\n\n\n";

        std::cout << "Powered by Studenikin Kirill\n";
        std::cout << "Выберите действие (1-3): ";

        int choice;
        std::cin >> choice;


        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 3.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер после ввода числа

        switch (choice) {
            case 1: {
                std::cout << "Начинаем новую игру...\n";

                hero = main_char("Boss_of_game", 0, 15, 5, 3, 5, 1, 4, coins{100}, 0);

                hero.equip(std::make_shared<Helmet>(
                    "Шлем Школы Воинов", 0, 15, 8, 0, warStyle::Non_style, coins{50}));
                hero.equip(std::make_shared<Chestplate>(
                    "Нагрудник Школы Воинов", 0, 20, 12, 0, warStyle::Non_style, coins{70}));
                hero.equip(std::make_shared<Gloves>(
                    "Перчатки Школы Воинов", 0, 8, 4, 0, warStyle::Non_style, coins{30}));
                hero.equip(std::make_shared<Pants>(
                    "Штаны школы воинов", 0, 13, 10, 0, warStyle::Non_style, coins{60}));
                hero.equip(std::make_shared<Boots>("Ботинки школы воинов", 0, 5, 12, 6, warStyle::Non_style, coins {40}));
                gameStarted = true;
                hero.equip(std::make_shared<weapon>(
                    "Меч Школы воинов", 0, 10, 7, 0, slotOfWeapon::Sword, warStyle::Elite, coins{80}));
                break;
            }
            case 2: {
                std::cout << "Попытка загрузить игру...\n";
                if (loadCharacterFromDatabase(hero)) {
                    std::cout << "Игра успешно загружена!\n";
                    gameStarted = true;
                } else {
                    std::cout << "Не удалось загрузить игру. Файл сохранения не найден или поврежден.\n";
                    std::cout << "Рекомендуется начать новую игру.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Выход из игры. До свидания!\n";
                return;
            }
            default: {
                std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
                break;
            }
        }
    }

    if (gameStarted) {
        gameLoop(hero, gameMap); // Передаем подготовленного персонажа и карту
    }
}
