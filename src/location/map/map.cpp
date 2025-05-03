#include "map.h"


map::map() {
    locationMap[0] = std::make_unique<battle_location>("Школа воинов", std::array<opponent *, 3>{});
    locationMap[1] = std::make_unique<battle_location>("Вирастоль", std::array<opponent *, 3>{});
    locationMap[2] = std::make_unique<shop_location>("Ярмарка");
    locationMap[3] = std::make_unique<battle_location>("Просёлок", std::array<opponent *, 3>{});
    locationMap[4] = std::make_unique<battle_location>("Чернолесье", std::array<opponent *, 3>{});
    locationMap[5] = std::make_unique<battle_location>("Ящеркин Хутор", std::array<opponent *, 3>{});
    locationMap[6] = std::make_unique<shop_location>("Стагород");
    locationMap[7] = std::make_unique<battle_location>("Зябкое Ущелье", std::array<opponent *, 3>{});
    locationMap[8] = std::make_unique<battle_location>("Мавкина роща", std::array<opponent *, 3>{});
    locationMap[9] = std::make_unique<battle_location>("Лес Духов", std::array<opponent *, 3>{});

    locationConnections = {
        {
            {1, -1, -1, -1}, // Школа воинов -> Вирастоль
            {2, 3, -1, -1},  // Вирастоль -> Ярмарка, Просёлок
            {1, 8, 7, 5},    // Ярмарка -> Вирастоль, Мавкина роща, Зябкое ущелье, Ящеркин хутор
            {8, 1, 9, 4},    // Просёлок -> Мавкина роща, Вирастоль, Лес Духов, Чернолесье
            {3, 9, 6, 5},    // Чернолесье -> Просёлок, Лес духов, Стагород, Ящеркин хутор
            {6, 4, 7, 2},    // Хутор -> Стагород, Чернолесье, ущелье, ярмарка
            {4, 5, -1, -1},  // Стагород -> Чернолесье, хутор
            {2, 5, -1, -1},  // Ущелье -> ярмарка, хутор
            {2, 3, -1, -1},  // Роща -> ярмарка, просёлок
            {3, 4, -1, -1}   // Лес духов -> просёлок, Чернолесье
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

void map::startTravel(int currentLocationIndex) const {


    while (true) {
        std::cout << "\nВы находитесь в локации: "
                << locationMap[currentLocationIndex]->getName() << "\n";
        std::cout << "Перейти на: \n";
        displayTravelOptions(currentLocationIndex);

        std::cout << "Введите число: " ;
        int userChoice;
        std::cin >> userChoice;

        std::cout << "\n";

        int availableOptions = 0;
        for (int i = 0; i < 4; ++i) {
            if (locationConnections[currentLocationIndex][i] != -1) {
                ++availableOptions;
            }
        }

        if (userChoice == availableOptions + 1) {
            std::cout << "Перемещение завершено.\n";
            break;
        }

        if (userChoice >= 1 && userChoice <= availableOptions) {
            int counter = 0;
            for (int i = 0; i < 4; ++i) {
                if (locationConnections[currentLocationIndex][i] != -1) {
                    ++counter;
                    if (counter == userChoice) {
                        currentLocationIndex = locationConnections[currentLocationIndex][i];
                        break;
                    }
                }
            }
        } else {
            std::cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    }
}
