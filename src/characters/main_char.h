#ifndef LAB_2_GAME_MAIN_CHAR_H
#define LAB_2_GAME_MAIN_CHAR_H

#include <memory>
#include <unordered_map>
#include "iostream"
#include "character.h"
#include "../inventory/coins/coins.h"
#include "../utils/slot_of_equipment.h"
#include "../utils/slot_of_potion.h"
#include "../inventory/weapon/weapon.h"
#include "../inventory/bag/bag.h"
#include "../inventory/inventory.h"

class main_char : public character {
public:
    main_char(const std::string &_name, unsigned int _level, unsigned int _health, unsigned int _damage,
              unsigned int _armor, unsigned int _accuracy, unsigned int _stun,
              unsigned int _dodge, const coins &cash);

    ~main_char() = default;

    std::unordered_map<slotOfEquipment, std::unique_ptr<equipment> > Equipment;
    std::unordered_map<slotOfPotion, std::unique_ptr<potion> > Potions;

   static  bag Bag;

    std::unique_ptr<weapon> gun;

    static coins balance;

    void equip(std::unique_ptr<equipment> item);

    void takeOff(const std::unique_ptr<equipment> &);

    void equip(std::unique_ptr<weapon> item);

    void takeOffWeapon();

    void equip(std::unique_ptr<potion> item);

    void takeOff(const std::unique_ptr<potion> &);

    static void buyEquipment(std::unique_ptr<equipment> _item);

    static void buyWeapon(std::unique_ptr<weapon> _weapon);

    static void buyPotion(std::unique_ptr<potion> _potion);

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
