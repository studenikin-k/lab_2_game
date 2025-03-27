#include "character.h"

character::character(){
    setHealth(20);
    setDamage(5);
    setArmor(3);
    setAccuracy(3);
    setStun(3);
    setDodge(2);
}




unsigned int character::getHealth() const {
    return health;
}

void character::setHealth(unsigned int _health) {
    character::health = _health;
}

unsigned int character::getDamage() const {
    return damage;
}

void character::setDamage(unsigned int _damage) {
    character::damage = _damage;
}

unsigned int character::getArmor() const {
    return armor;
}

void character::setArmor(unsigned int _armor) {
    character::armor = _armor;
}

unsigned int character::getAccuracy() const {
    return accuracy;
}

void character::setAccuracy(unsigned int _accuracy) {
    character::accuracy = _accuracy;
}

unsigned int character::getStun() const {
    return stun;
}

void character::setStun(unsigned int _stun) {
    character::stun = _stun;
}

unsigned int character::getDodge() const {
    return dodge;
}

void character::setDodge(unsigned int _dodge) {
    character::dodge = _dodge;
}

