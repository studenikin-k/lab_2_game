#include "equipment.h"

equipment::equipment(const std::string &_name, const unsigned int _level, const unsigned int _health,
                     const unsigned int _armor, const unsigned int _dodge,
                     const slotOfEquipment _slot, const warStyle _style, const coins _price)
        : inventory(), price(_price), slot(_slot), armor_(_armor), style(_style) {
    setName(_name);
    setLevel(_level);
    setHealth(_health);
    setArmor(_armor);
    setDodge(_dodge);
}

unsigned int equipment::getHealth() const {
    return health;
}

void equipment::setHealth(unsigned int _health) {
    health = _health;
}

unsigned int equipment::getArmor() const {
    return armor;
}

void equipment::setArmor(unsigned int _armor) {
    armor = _armor;
}

unsigned int equipment::getDodge() const {
    return dodge;
}

void equipment::setDodge(unsigned int _dodge) {
    dodge = _dodge;
}

slotOfEquipment equipment::getSlot() const {
    return slot;
}

void equipment::setSlot(slotOfEquipment _slot) {
    equipment::slot = _slot;
}

warStyle equipment::getStyle() const {
    return style;
}

void equipment::setStyle(warStyle _style) {
    equipment::style = _style;
}


void equipment::setPrice(const coins &_price) {
    equipment::price = _price;
}

void equipment::showInShop() const {
    std::cout << "Название: " << equipment::getName() << std::endl <<
              "Тип предмета: " << slotOfEquipmentToString(equipment::slot) << std::endl <<
              "Уровень премета: " << equipment::getLevel() << std::endl <<
              "Бонус к здоровью: " << equipment::getHealth() << std::endl <<
              "Бонус к броне: " <<  equipment::getArmor() << std::endl <<
              "Бонус к Увороту: " << equipment::getDodge() << std::endl <<
              "Стиль боя: " << warStyleToString(equipment::style) << std::endl <<
              "Цена покупки: " << equipment::price.showMoney()<<
              "Цена продажи: " << equipment::price.showSellPrice();


}
void equipment::showInInventory() const {
    std::cout << "Название: " << equipment::getName() << std::endl <<
              "Тип предмета: " << slotOfEquipmentToString(equipment::slot) << std::endl <<
              "Уровень премета: " << equipment::getLevel() << std::endl <<
              "Бонус к здоровью: " << equipment::getHealth() << std::endl <<
              "Бонус к броне: " <<  equipment::getArmor() << std::endl <<
              "Бонус к Увороту: " << equipment::getDodge() << std::endl <<
              "Стиль боя: " << warStyleToString(equipment::style) << std::endl <<
              "Цена продажи: " << equipment::price.showSellPrice() << std::endl << std::endl;


}

