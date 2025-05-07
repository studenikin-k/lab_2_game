#ifndef MAP_H
#define MAP_H

#include "location/location.h"
#include "../battle_location/battle_location.h"
#include "../shop_location/shop_location.h"
#include <array>

class map {
public:
    map();
    ~map() = default;

    void startTravel(int currentLocationIndex) const;

private:
    std::array<std::unique_ptr<location>, 10> locationMap;
    std::array<std::array<int, 4>, 10> locationConnections{};

    void displayTravelOptions(int currentLocationIndex) const;
};



#endif //MAP_H
