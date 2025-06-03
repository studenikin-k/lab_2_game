#include "../../../include/all_headers.h"
#include <iomanip>

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


void opponent::showInfo() const {
    constexpr int totalWidth = 20;

    std::cout << std::string(totalWidth, '*') << '\n';


    std::cout << "* " << "Имя: " << name << '\n';
    std::cout << "* " << "Уровень: " << level << '\n';
    std::cout << "* " << "Здоровье: " << health << '\n';
    std::cout << "* " << "Урон: " << damage << '\n';
    std::cout << "* " << "Броня: " << armor << '\n';
    std::cout << "* " << "Точность: " << accuracy << '\n';
    std::cout << "* " << "Оглушение: " << stun << '\n';
    std::cout << "* " << "Уворот: " << dodge << '\n';

    std::cout << std::string(totalWidth, '*') << "\n\n";
}
