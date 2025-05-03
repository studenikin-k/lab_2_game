#include "battle_location.h"


battle_location::battle_location(const std::string &name, const std::array<opponent *, 3> &opponents) : location(name) {
    _opponents = opponents;
}

void battle_location::showOpponents() const {
    std::cout << "   ***Список врагов***   \n\n";
    for (const auto opponent: _opponents) {
        opponent->showInfo();
    }
}
