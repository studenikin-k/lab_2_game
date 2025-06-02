#include "include/all_headers.h"
#include <memory>
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

Helmet::Helmet(const std::string &_name, unsigned int _level, unsigned int _health,
       unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price)
    : equipment(_name, _level, _health, _armor, _dodge,
                slotOfEquipment::Helmet, _style, _price) {}

std::shared_ptr<equipment> Helmet::clone() const {
    return std::make_shared<Helmet>(*this);
}

Chestplate::Chestplate(const std::string &_name, unsigned int _level, unsigned int _health,
           unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price)
    : equipment(_name, _level, _health, _armor, _dodge,
                slotOfEquipment::Chestplate, _style, _price) {}

std::shared_ptr<equipment> Chestplate::clone() const {
    return std::make_shared<Chestplate>(*this);
}

Gloves::Gloves(const std::string &_name, unsigned int _level, unsigned int _health,
       unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price)
    : equipment(_name, _level, _health, _armor, _dodge,
                slotOfEquipment::Gloves, _style, _price) {}

std::shared_ptr<equipment> Gloves::clone() const {
    return std::make_shared<Gloves>(*this);
}

Pants::Pants(const std::string &_name, unsigned int _level, unsigned int _health,
      unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price)
    : equipment(_name, _level, _health, _armor, _dodge,
                slotOfEquipment::Pants, _style, _price) {}

std::shared_ptr<equipment> Pants::clone() const {
    return std::make_shared<Pants>(*this);
}

Boots::Boots(const std::string &_name, unsigned int _level, unsigned int _health,
      unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price)
    : equipment(_name, _level, _health, _armor, _dodge,
                slotOfEquipment::Boots, _style, _price) {}

std::shared_ptr<equipment> Boots::clone() const {
    return std::make_shared<Boots>(*this);
}

