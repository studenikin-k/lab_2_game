#include "potion.h"


const std::string &potion::getName() const {
    return name;
}

void potion::setName(const std::string &_name) {
    potion::name = _name;
}

unsigned int potion::getLevel() const {
    return level;
}

void potion::setLevel(unsigned int _level) {
    potion::level = _level;
}

slotOfPotion potion::getSlot() const {
    return slot;
}

void potion::setSlot(slotOfPotion _slot) {
    potion::slot = _slot;
}


healthPotion::healthPotion(const std::string &_name, unsigned int _level,
                           slotOfPotion _slot, unsigned int _health) : potion() {
    setName(_name);
    setLevel(_level);
    setSlot(_slot);
    setHealth(_health);

}

unsigned int healthPotion::getHealth() const {
    return health;
}

void healthPotion::setHealth(unsigned int _health) {
    healthPotion::health = _health;
}

void healthPotion::showInShop() {
    std::cout << "Название: " << healthPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(healthPotion::slot) << std::endl <<
              "Уровень премета: " << healthPotion::getLevel() << std::endl <<
              "Бонус к здоровью: " << healthPotion::getHealth() << std::endl <<
              "Цена покупки: " << healthPotion::price.showMoney()<<
              "Цена продажи: " << healthPotion::price.showSellPrice();


}
void healthPotion::showInInventory() {
    std::cout << "Название: " << healthPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(healthPotion::slot) << std::endl <<
              "Уровень премета: " << healthPotion::getLevel() << std::endl <<
              "Бонус к здоровью: " << healthPotion::getHealth() << std::endl <<
              "Цена продажи: " << healthPotion::price.showSellPrice();


}

damagePotion::damagePotion(const std::string &_name, unsigned int _level,
                           slotOfPotion _slot, unsigned int _damage) : potion(){
    setName(_name);
    setLevel(_level);
    setSlot(_slot);
    setDamage(_damage);
}

unsigned int damagePotion::getDamage() const {
    return damage;
}

void damagePotion::setDamage(unsigned int _damage) {
    damagePotion::damage = _damage;
}

void damagePotion::showInShop() {
    std::cout << "Название: " << damagePotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(damagePotion::slot) << std::endl <<
              "Уровень премета: " << damagePotion::getLevel() << std::endl <<
              "Бонус к Урону: " << damagePotion::getDamage() << std::endl <<
              "Цена покупки: " << damagePotion::price.showMoney()<<
              "Цена продажи: " << damagePotion::price.showSellPrice();
}
void damagePotion::showInInventory() {
    std::cout << "Название: " << damagePotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(damagePotion::slot) << std::endl <<
              "Уровень премета: " << damagePotion::getLevel() << std::endl <<
              "Бонус к Урону: " << damagePotion::getDamage() << std::endl <<
              "Цена продажи: " << damagePotion::price.showSellPrice();
}

armorPotion::armorPotion(const std::string &_name, unsigned int _level,
                         slotOfPotion _slot, unsigned int _armor) : potion() {
    setName(_name);
    setLevel(_level);
    setSlot(_slot);
    setArmor(_armor);
}

unsigned int armorPotion::getArmor() const {
    return armor;
}

void armorPotion::setArmor(unsigned int _armor) {
    armorPotion::armor = _armor;
}

void armorPotion::showInShop() {
    std::cout << "Название: " << armorPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(armorPotion::slot) << std::endl <<
              "Уровень премета: " << armorPotion::getLevel() << std::endl <<
              "Бонус к броне: " << armorPotion::getArmor() << std::endl <<
              "Цена покупки: " << armorPotion::price.showMoney()<<
              "Цена продажи: " << armorPotion::price.showSellPrice();
}
void armorPotion::showInInventory() {
    std::cout << "Название: " << armorPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(armorPotion::slot) << std::endl <<
              "Уровень премета: " << armorPotion::getLevel() << std::endl <<
              "Бонус к броне: " << armorPotion::getArmor() << std::endl <<
              "Цена продажи: " << armorPotion::price.showSellPrice();
}

accuracyPotion::accuracyPotion(const std::string &_name, unsigned int _level,
                               slotOfPotion _slot, unsigned int _accuracy) : potion() {
    setName(_name);
    setLevel(_level);
    setSlot(_slot);
    setAccuracy(_accuracy);
}

unsigned int accuracyPotion::getAccuracy() const {
    return accuracy;
}

void accuracyPotion::setAccuracy(unsigned int _accuracy) {
    accuracyPotion::accuracy = _accuracy;
}

void accuracyPotion::showInShop() {
    std::cout << "Название: " << accuracyPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(accuracyPotion::slot) << std::endl <<
              "Уровень премета: " << accuracyPotion::getLevel() << std::endl <<
              "Бонус к точности: " << accuracyPotion::getAccuracy() << std::endl <<
              "Цена покупки: " << accuracyPotion::price.showMoney()<<
              "Цена продажи: " << accuracyPotion::price.showSellPrice();


}
void accuracyPotion::showInInventory() {
    std::cout << "Название: " << accuracyPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(accuracyPotion::slot) << std::endl <<
              "Уровень премета: " << accuracyPotion::getLevel() << std::endl <<
              "Бонус к точности: " << accuracyPotion::getAccuracy() << std::endl <<
              "Цена продажи: " << accuracyPotion::price.showSellPrice();

}

stunPotion::stunPotion(const std::string &_name, unsigned int _level,
                       slotOfPotion _slot, unsigned int _stun) : potion(){
    setName(_name);
    setLevel(_level);
    setSlot(_slot);
    setStun(_stun);
}

unsigned int stunPotion::getStun() const {
    return stun;
}

void stunPotion::setStun(unsigned int _stun) {
    stunPotion::stun = _stun;
}

void stunPotion::showInShop() {
    std::cout << "Название: " << stunPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(stunPotion::slot) << std::endl <<
              "Уровень премета: " << stunPotion::getLevel() << std::endl <<
              "Бонус к оглушению: " << stunPotion::getStun() << std::endl <<
              "Цена покупки: " << stunPotion::price.showMoney()<<
              "Цена продажи: " << stunPotion::price.showSellPrice();


}
void stunPotion::showInInventory() {
    std::cout << "Название: " << stunPotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(stunPotion::slot) << std::endl <<
              "Уровень премета: " << stunPotion::getLevel() << std::endl <<
              "Бонус к оглушению: " << stunPotion::getStun() << std::endl <<
              "Цена продажи: " << stunPotion::price.showSellPrice();

}

dodgePotion::dodgePotion(const std::string &_name, unsigned int _level,
                         slotOfPotion _slot, unsigned int _dodge) : potion() {
    setName(_name);
    setLevel(_level);
    setSlot(_slot);
    setDodge(_dodge);

}

unsigned int dodgePotion::getDodge() const {
    return dodge;
}

void dodgePotion::setDodge(unsigned int _dodge) {
    dodgePotion::dodge = _dodge;
}

void dodgePotion::showInShop() {
    std::cout << "Название: " << dodgePotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(dodgePotion::slot) << std::endl <<
              "Уровень премета: " << dodgePotion::getLevel() << std::endl <<
              "Бонус к увороту: " << dodgePotion::getDodge() << std::endl <<
              "Цена покупки: " << dodgePotion::price.showMoney()<<
              "Цена продажи: " << dodgePotion::price.showSellPrice();


}
void dodgePotion::showInInventory() {
    std::cout << "Название: " << dodgePotion::getName() << std::endl <<
              "Тип предмета: " << slotOfPotionToString(dodgePotion::slot) << std::endl <<
              "Уровень премета: " << dodgePotion::getLevel() << std::endl <<
              "Бонус к увороту: " << dodgePotion::getDodge() << std::endl <<
              "Цена продажи: " << dodgePotion::price.showSellPrice();
}