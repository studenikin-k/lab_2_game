#include "weapon.h"

weapon::weapon(const std::string &_name, unsigned int _level, unsigned int _damage,
                      unsigned int _accuracy,unsigned int _stun,
                      slotOfWeapon _weapon, warStyle _style, coins _price):
                      inventory(), slot(_weapon), style(_style), price(_price) {
    setName(_name);
    setLevel(_level);
    setDamage(_damage);
    setAccuracy(_accuracy);
    setStun(_stun);
}


unsigned int weapon::getStun() const {
    return stun;
}

void weapon::setStun(unsigned int _stun) {
    weapon::stun = _stun;
}

unsigned int weapon::getAccuracy() const {
    return accuracy;
}

void weapon::setAccuracy(unsigned int _accuracy) {
    weapon::accuracy = _accuracy;
}

unsigned int weapon::getDamage() const {
    return damage;
}

void weapon::setDamage(unsigned int _damage) {
    weapon::damage = _damage;
}

void weapon::showInShop() {
    std::cout << "Название: " << weapon::getName() << std::endl <<
              "Тип предмета: " << slotOfWeaponToString(weapon::slot) << std::endl <<
              "Уровень премета: " << weapon::getLevel() << std::endl <<
              "Бонус к урону: " << weapon::getDamage() << std::endl <<
              "Бонус к точности: " <<  weapon::getAccuracy() << std::endl <<
              "Бонус к Оглушению: " << weapon::getStun()<< std::endl <<
              "Стиль боя: " << warStyleToString(weapon::style) << std::endl <<
              "Цена покупки: " << weapon::price.showMoney()<<
              "Цена продажи: " << weapon::price.showSellPrice();


}
void weapon::showInInventory() {
    std::cout << "Название: " << weapon::getName() << std::endl <<
              "Тип предмета: " << slotOfWeaponToString(weapon::slot) << std::endl <<
              "Уровень премета: " << weapon::getLevel() << std::endl <<
              "Бонус к урону: " << weapon::getDamage() << std::endl <<
              "Бонус к точности: " <<  weapon::getAccuracy() << std::endl <<
              "Бонус к Оглушению: " << weapon::getStun()<< std::endl <<
              "Стиль боя: " << warStyleToString(weapon::style) << std::endl <<
              "Цена продажи: " << weapon::price.showSellPrice();

}

slotOfWeapon weapon::getSlot() const {
    return slot;
}

void weapon::setSlot(slotOfWeapon _slot) {
    weapon::slot = _slot;
}
