#ifndef LAB_2_GAME_WEAPON_H
#define LAB_2_GAME_WEAPON_H

#include <iostream>
#include <array>
#include "../inventory.h"
#include "weapon.h"
#include "../../utils/slot_of_weapon.h"
#include "../../utils/war_style.h"
#include "../coins/coins.h"

class weapon : public inventory{
public:
    weapon(const std::string &_name, unsigned int _level, unsigned int _damage,
           unsigned int _accuracy, unsigned int _stun, slotOfWeapon _weapon, warStyle _style, coins _price);

    weapon()= default;


    ~weapon() = default;

    slotOfWeapon slot = {};

    slotOfWeapon getSlot() const;

    void setSlot(slotOfWeapon slot);

    warStyle style{};

    [[nodiscard]] unsigned int getStun() const;

    void setStun(unsigned int stun);

    [[nodiscard]] unsigned int getAccuracy() const;

    void setAccuracy(unsigned int accuracy);

    [[nodiscard]] unsigned int getDamage() const;

    void showInShop();
    void showInInventory();
    coins price{};

    void setDamage(unsigned int damage);
private:
    unsigned int damage{};
    unsigned int accuracy{};
    unsigned int stun{};
};


#endif
