#ifndef BATTLE_LOCATION_H
#define BATTLE_LOCATION_H
#include "../location.h"
#include "../../characters/opponent.h"
#include "array"

class battle_location : public location {
public:
    battle_location(const std::string &name, const std::array<opponent*, 3> &opponents);
    ~battle_location() = default;

    std::array<opponent*,3> _opponents{};
    void showOpponents() const;

};



#endif //BATTLE_LOCATION_H

