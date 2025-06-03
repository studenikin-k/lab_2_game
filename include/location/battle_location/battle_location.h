#ifndef BATTLE_LOCATION_H
#define BATTLE_LOCATION_H

#include "array"
#include "../../all_headers.h"

// класс боевых локаций как шаблон для объектов локации
class battle_location : public location {
public:
    battle_location(const std::string &name, const std::array<opponent*, 3> &opponents);
    // конструктор принимает на вход массив оппонентов с которыи можно будет вступить в бой.
    ~battle_location() override = default;

    std::array<opponent*,3> _opponents{}; // массив оппонентов


};



#endif //BATTLE_LOCATION_H

