#include "battle_location.h"


battle_location::battle_location(const std::string &name, const std::array<opponent *, 3> &opponents) : location(name) {
    _opponents = opponents;
}

