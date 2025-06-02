#ifndef MAP_H
#define MAP_H


#include <array>
#include "../../all_headers.h"
    class map {
    public:
        map();

        ~map() = default;

        std::vector<std::shared_ptr<opponent>> allOpponents;

        void startTravel(main_char &hero) const; // важный метод, принимает персонажа как входной аргумент
        // позволяет путешествовать по карте.

        bool isShopLocation(const main_char &hero) const;

        bool isBattleLocation(const main_char &hero) const;

        std::vector<opponent *> getOpponents(const main_char &hero) const;


        std::array<std::unique_ptr<location>, 10> locationMap; // карта

        shop getShop(const main_char &hero) const;

        std::array<std::array<int, 4>, 10> locationConnections{}; // точки передвижения

        void displayTravelOptions(int currentLocationIndex) const; // метод, при помощи которого можно понять куда
        // персонаж может передвинуться, вшит в startTravel.
    };


#endif //MAP_H
