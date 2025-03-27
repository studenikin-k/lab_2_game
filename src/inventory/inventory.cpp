#include "inventory.h"


const std::string & inventory::getName() const {
    return name;
}

void inventory::setName(const std::string &_name) {
    inventory::name = _name;
}

unsigned int inventory::getLevel() const {
    return level;
}

void inventory::setLevel(unsigned int _level) {
    inventory::level = _level;
}

