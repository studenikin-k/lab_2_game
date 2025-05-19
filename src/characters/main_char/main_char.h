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

    std::unordered_map<slotOfEquipment, std::shared_ptr<equipment> > Equipment;
    std::array<std::shared_ptr<potion>, BELT_SIZE> Belt{};

    bag Bag{};

    std::shared_ptr<weapon> gun;

    coins balance{};

    void equip(std::shared_ptr<equipment> item);

    void takeOffEquipment(std::shared_ptr<equipment> item);

    void equip(std::shared_ptr<weapon>);

    void takeOffWeapon();

    bool isBeltFull() const;

    void displayBelt() const;

    void equip(std::shared_ptr<potion> item);

    void takeOffPotion();

    void buyEquipment(const std::shared_ptr<equipment> &_item);

    void buyWeapon(const std::shared_ptr<weapon> &);

    void buyPotion(const std::shared_ptr<potion> &);

    void showBag();

    void showGear();

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &name);

    unsigned int getLevel();

    void setLevel(unsigned int level);

private:
     unsigned int level{};

private:
    std::string name{};
};

std::ostream &operator<<(std::ostream &os, const main_char &pers);

#endif //LAB_2_GAME_MAIN_CHAR_H
