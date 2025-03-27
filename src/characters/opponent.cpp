#include "opponent.h"

opponent::opponent(std::string &_name, unsigned int _level, unsigned int _health, unsigned int _damage,
                   unsigned int _armor, unsigned int _accuracy, unsigned int _stun, unsigned int _dodge):character() {
    setName(_name);
    setLevel(_level);
    setHealth(_health);
    setDamage(_damage);
    setArmor(_armor);
    setAccuracy(_accuracy);
    setStun(_stun);
    setDodge(_dodge);
}

const std::string &opponent::getName() const {
    return name;
}

void opponent::setName(const std::string &_name) {
    opponent::name = _name;
}

unsigned int opponent::getLevel() const {
    return level;
}

void opponent::setLevel(unsigned int _level) {
    opponent::level = _level;
}
