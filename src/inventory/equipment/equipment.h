#ifndef LAB_2_GAME_EQUIPMENT_H
#define LAB_2_GAME_EQUIPMENT_H

#include "../inventory.h"
#include "../../utils/slot_of_equipment.h"
#include "../../utils/war_style.h"
#include "../coins/coins.h"

class equipment : public inventory {
public:
    equipment(const std::string &_name, unsigned int _level, unsigned int _health,
              unsigned int _armor, unsigned int _dodge, slotOfEquipment _slot, warStyle _style, coins _price);

    ~equipment() = default;

    [[nodiscard]] unsigned int getHealth() const;

    void setHealth(unsigned int health);

    [[nodiscard]] unsigned int getArmor() const;

    void setArmor(unsigned int armor);

    [[nodiscard]] unsigned int getDodge() const;

    void setDodge(unsigned int dodge);

    void showInShop();
    void showInInventory();

    coins price;
    slotOfEquipment slot;

    [[nodiscard]] slotOfEquipment getSlot() const;

    void setSlot(slotOfEquipment slot);

    [[nodiscard]] warStyle getStyle() const;

    void setStyle(warStyle style);


    void setPrice(const coins &price);

    warStyle style;

private:
    unsigned int health{};
    unsigned int armor{};
    unsigned int dodge{};
};

class Helmet : public equipment {
public:
    Helmet(const std::string &_name, unsigned int _level, unsigned int _health,
           unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price) :
            equipment(_name, _level, _health, _armor, _dodge, slotOfEquipment::Helmet, _style, _price) {};
};

class Chestplate : public equipment {
public:
    Chestplate(const std::string &_name, unsigned int _level, unsigned int _health,
               unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price) :
            equipment(_name, _level, _health, _armor, _dodge, slotOfEquipment::Chestplate, _style, _price) {};
};

class Gloves : public equipment {
public:
    Gloves(const std::string &_name, unsigned int _level, unsigned int _health,
           unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price) :
            equipment(_name, _level, _health, _armor, _dodge, slotOfEquipment::Gloves, _style, _price) {};
};


class Pants : public equipment {
public:
    Pants(const std::string &_name, unsigned int _level, unsigned int _health,
          unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price) :
            equipment(_name, _level, _health, _armor, _dodge, slotOfEquipment::Pants, _style, _price) {};
};


class Boots : public equipment {
public:
    Boots(const std::string &_name, unsigned int _level, unsigned int _health,
          unsigned int _armor, unsigned int _dodge, slotOfEquipment _slot, warStyle _style, coins _price) :
            equipment(_name, _level, _health, _armor, _dodge, slotOfEquipment::Boots, _style, _price) {};
};

#endif
