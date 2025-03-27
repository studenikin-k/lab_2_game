#include "opponent.h"

opponent::opponent(const std::string &_name, const unsigned int _level,
                   const unsigned int _health, const unsigned int _damage,
                   const unsigned int _armor, const unsigned int _accuracy,
                   const unsigned int _stun, const unsigned int _dodge): character() {
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
