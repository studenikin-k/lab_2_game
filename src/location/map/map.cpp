#include "../../include/all_headers.h"


map::map() {
    // 1. Инициализация всех уникальных оппонентов и их добавление в allOpponents.

    // Локация 0: Школа воинов
    allOpponents.push_back(std::make_unique<opponent>("Гоблин-Ученик", 0, 38, 13, 8, 15, 3, 10));
    allOpponents.push_back(std::make_unique<opponent>("Молодой Кабан", 0, 50, 18, 10, 13, 3, 8));
    allOpponents.push_back(std::make_unique<opponent>("Орк-Надзиратель", 1, 70, 25, 15, 20, 5, 13));

    // Локация 1: Вирастоль
    allOpponents.push_back(std::make_unique<opponent>("Бродячий Волк", 0, 45, 15, 8, 18, 3, 8));
    allOpponents.push_back(std::make_unique<opponent>("Старый Гоблин", 1, 63, 23, 13, 18, 5, 10));
    allOpponents.push_back(std::make_unique<opponent>("Пещерный Тролль", 1, 88, 30, 20, 15, 8, 5));

    // Локация 3: Просёлок
    allOpponents.push_back(std::make_unique<opponent>("Деревенский Разбойник", 0, 50, 20, 10, 15, 5, 10));
    allOpponents.push_back(std::make_unique<opponent>("Гигантский Паук", 1, 55, 25, 10, 25, 3, 18));
    allOpponents.push_back(std::make_unique<opponent>("Безумный Крестьянин", 1, 75, 35, 18, 23, 8, 10));

    // Локация 4: Чернолесье
    allOpponents.push_back(std::make_unique<opponent>("Лесной Огр", 1, 75, 38, 20, 15, 8, 8));
    allOpponents.push_back(std::make_unique<opponent>("Древесный Дух", 1, 70, 30, 15, 30, 5, 20));
    allOpponents.push_back(std::make_unique<opponent>("Опытный Охотник", 2, 95, 45, 23, 25, 10, 15));

    // Локация 5: Ящеркин Хутор
    allOpponents.push_back(std::make_unique<opponent>("Ящер-Рекрут", 1, 63, 25, 18, 20, 5, 15));
    allOpponents.push_back(std::make_unique<opponent>("Ящер-Воин", 1, 80, 35, 23, 25, 8, 18));
    allOpponents.push_back(std::make_unique<opponent>("Болотный Гигант", 2, 113, 50, 30, 20, 13, 10));

    // Локация 7: Зябкое Ущелье
    allOpponents.push_back(std::make_unique<opponent>("Горный Бандит", 1, 88, 40, 20, 25, 8, 13));
    allOpponents.push_back(std::make_unique<opponent>("Снежный Человек", 2, 105, 50, 25, 30, 13, 18));
    allOpponents.push_back(std::make_unique<opponent>("Каменный Голем", 2, 138, 63, 38, 23, 15, 8));

    // Локация 8: Мавкина роща
    allOpponents.push_back(std::make_unique<opponent>("Лесная Мавка", 1, 75, 38, 18, 30, 8, 23));
    allOpponents.push_back(std::make_unique<opponent>("Древний Эн", 2, 100, 55, 28, 25, 10, 15));
    allOpponents.push_back(std::make_unique<opponent>("Теневой Демон", 2, 125, 70, 35, 38, 20, 25));

    // Локация 9: Лес Духов
    allOpponents.push_back(std::make_unique<opponent>("Дух Воина", 2, 100, 50, 25, 30, 13, 20));
    allOpponents.push_back(std::make_unique<opponent>("Призрак Командира", 2, 125, 63, 30, 38, 18, 25));
    allOpponents.push_back(std::make_unique<opponent>("Древний Лич", 2, 163, 88, 45, 45, 25, 30));


    // 2. Инициализация локаций (боевых и магазинов)
    // Теперь передаем std::array<opponent*, 3> в конструктор battle_location

    // Локация 0: Школа воинов
    locationMap[0] = std::make_unique<battle_location>(
        "Школа воинов",
        std::array<opponent *, 3>{allOpponents[0].get(), allOpponents[1].get(), allOpponents[2].get()}
    );

    // Локация 1: Вирастоль
    locationMap[1] = std::make_unique<battle_location>(
        "Вирастоль",
        std::array<opponent *, 3>{allOpponents[3].get(), allOpponents[4].get(), allOpponents[5].get()}
    );

    // Локация 2: Ярмарка (Магазин)
    locationMap[2] = std::make_unique<shop_location>("Ярмарка");

    // Локация 3: Просёлок
    locationMap[3] = std::make_unique<battle_location>(
        "Просёлок",
        std::array<opponent *, 3>{allOpponents[6].get(), allOpponents[7].get(), allOpponents[8].get()}
    );

    // Локация 4: Чернолесье
    locationMap[4] = std::make_unique<battle_location>(
        "Чернолесье",
        std::array<opponent *, 3>{allOpponents[9].get(), allOpponents[10].get(), allOpponents[11].get()}
    );

    // Локация 5: Ящеркин Хутор
    locationMap[5] = std::make_unique<battle_location>(
        "Ящеркин Хутор",
        std::array<opponent *, 3>{allOpponents[12].get(), allOpponents[13].get(), allOpponents[14].get()}
    );

    // Локация 6: Стагород (Магазин)
    locationMap[6] = std::make_unique<shop_location>("Стагород");

    // Локация 7: Зябкое Ущелье
    locationMap[7] = std::make_unique<battle_location>(
        "Зябкое Ущелье",
        std::array<opponent *, 3>{allOpponents[15].get(), allOpponents[16].get(), allOpponents[17].get()}
    );

    // Локация 8: Мавкина роща
    locationMap[8] = std::make_unique<battle_location>(
        "Мавкина роща",
        std::array<opponent *, 3>{allOpponents[18].get(), allOpponents[19].get(), allOpponents[20].get()}
    );

    // Локация 9: Лес Духов
    locationMap[9] = std::make_unique<battle_location>(
        "Лес Духов",
        std::array<opponent *, 3>{allOpponents[21].get(), allOpponents[22].get(), allOpponents[23].get()}
    );

    // 3. Инициализация соединений локаций (без изменений)
    locationConnections = {
        {
            {1, -1, -1, -1}, // Школа воинов -> Вирастоль
            {2, 3, -1, -1}, // Вирастоль -> Ярмарка, Просёлок
            {1, 8, 7, 5}, // Ярмарка -> Вирастоль, Мавкина роща, Зябкое ущелье, Ящеркин хутор
            {8, 1, 9, 4}, // Просёлок -> Мавкина роща, Вирастоль, Лес Духов, Чернолесье
            {3, 9, 6, 5}, // Чернолесье -> Просёлок, Лес духов, Стагород, Ящеркин хутор
            {6, 4, 7, 2}, // Хутор -> Стагород, Чернолесье, ущелье, ярмарка
            {4, 5, -1, -1}, // Стагород -> Чернолесье, хутор
            {2, 5, -1, -1}, // Ущелье -> ярмарка, хутор
            {2, 3, -1, -1}, // Роща -> ярмарка, просёлок
            {3, 4, -1, -1} // Лес духов -> просёлок, Чернолесье
        }
    };
}
void map::displayTravelOptions(const int currentLocationIndex) const {
    int optionNumber = 1;
    for (int i = 0; i < 4; ++i) {
        int destinationIndex = locationConnections[currentLocationIndex][i];
        if (destinationIndex != -1) {
            std::cout << optionNumber++ << ". " << locationMap[destinationIndex]->getName() << "\n";
        }
    }
    std::cout << optionNumber << ". Завершить перемещение\n";
}

void map::startTravel(main_char &hero) const {
    while (true) {
        clearScreen();
        std::cout << "\nВы находитесь в локации: "
                << locationMap[hero.getCurrentPosition()]->getName() << "\n";
        std::cout << "Перейти на: \n";
        displayTravelOptions(hero.getCurrentPosition());

        std::cout << "Введите число: ";
        int userChoice;
        std::cin >> userChoice;

        std::cout << "\n";

        int availableOptions = 0;
        for (int i = 0; i < 4; ++i) {
            if (locationConnections[hero.getCurrentPosition()][i] != -1) {
                ++availableOptions;
            }
        }

        if (userChoice == availableOptions + 1) {
            std::cout << "Перемещение завершено.\n";
            return;
        }

        if (userChoice >= 1 && userChoice <= availableOptions) {
            int counter = 0;
            for (int i = 0; i < 4; ++i) {
                if (locationConnections[hero.getCurrentPosition()][i] != -1) {
                    ++counter;
                    if (counter == userChoice) {
                        hero.setCurrentPosition(locationConnections[hero.getCurrentPosition()][i]);
                        break;
                    }
                }
            }
        } else {
            std::cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    }
}

bool map::isShopLocation(const main_char &hero) const {
    unsigned int pos = hero.getCurrentPosition();
    if (pos >= locationMap.size() || !locationMap[pos])
        return false;

    return dynamic_cast<shop_location *>(locationMap[pos].get()) != nullptr;
}

bool map::isBattleLocation(const main_char &hero) const {
    unsigned int pos = hero.getCurrentPosition();
    if (pos >= locationMap.size() || !locationMap[pos])
        return false;
    return dynamic_cast<battle_location *>(locationMap[pos].get()) != nullptr;
}


std::vector<opponent *> map::getOpponents(const main_char &hero) const {
    std::vector<opponent *> result;
    unsigned int pos = hero.getCurrentPosition();
    if (pos >= locationMap.size() || !locationMap[pos])
        return result;

    if (auto *bLoc = dynamic_cast<battle_location *>(locationMap[pos].get())) {
        for (auto *opp: bLoc->_opponents) {
            if (opp)
                result.push_back(opp);
        }
    }
    return result;
}

shop map::getShop(const main_char &hero) const {
    shop result;
    unsigned int pos = hero.getCurrentPosition();

    if (pos >= locationMap.size() || !locationMap[pos]) {
        return result;
    }

    if (auto *bLoc = dynamic_cast<shop_location *>(locationMap[pos].get())) {
        result = bLoc->Market;
    }

    return result;
}
