#ifndef LAB_2_GAME_MAIN_CHAR_H
#define LAB_2_GAME_MAIN_CHAR_H

#include <memory>
#include <unordered_map>
#include <iostream>
#include "character.h"
#include "../inventory/coins/coins.h"
#include "../utils/slot_of_equipment.h"
#include "../utils/slot_of_potion.h"
#include "../inventory/weapon/weapon.h"
#include "../inventory/bag/bag.h"
#include "../inventory/inventory.h"

constexpr int BELT_SIZE = 6;

class main_char : public character {
public:
    main_char(const std::string &_name, unsigned int _level, unsigned int _health, unsigned int _damage,
              unsigned int _armor, unsigned int _accuracy, unsigned int _stun,
              unsigned int _dodge, const coins &cash);

    ~main_char() = default;

    std::unordered_map<slotOfEquipment, equipment *> Equipment;
    std::array<potion *, BELT_SIZE> Belt{};

    static bag Bag;

    weapon *gun;

    static coins balance;

    void equip(equipment *item);

    void takeOffEquipment(const equipment *item);

    void equip(weapon *item);

    void takeOffWeapon();

    bool isBeltFull() const;

    void displayBelt() const;

    void equip(potion *item);

    void takeOffPotion();

    static void buyEquipment(equipment *_item);

    static void buyWeapon(weapon *_weapon);

    static void buyPotion(potion *_potion);

    void showBag();

    void showGear();

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &name);

    static unsigned int getLevel();

    static void setLevel(unsigned int level);

private:
    static unsigned int level;

private:
    std::string name{};
};

std::ostream &operator<<(std::ostream &os, const main_char &pers);

#endif //LAB_2_GAME_MAIN_CHAR_H
