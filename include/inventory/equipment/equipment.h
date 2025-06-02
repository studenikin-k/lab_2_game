#ifndef LAB_2_GAME_EQUIPMENT_H
#define LAB_2_GAME_EQUIPMENT_H


#include "memory"
#include "../../all_headers.h"

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

    [[nodiscard]] virtual std::shared_ptr<equipment> clone() const = 0;

    void setDodge(unsigned int dodge);

    void showInShop() const;

    void showInInventory() const;

    coins price;
    slotOfEquipment slot;
    unsigned int armor_;

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
           unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price);

    std::shared_ptr<equipment> clone() const override;
};

class Chestplate : public equipment {
public:
    Chestplate(const std::string &_name, unsigned int _level, unsigned int _health,
               unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price);

    std::shared_ptr<equipment> clone() const override;
};

class Gloves : public equipment {
public:
    Gloves(const std::string &_name, unsigned int _level, unsigned int _health,
           unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price);

    std::shared_ptr<equipment> clone() const override;
};

class Pants : public equipment {
public:
    Pants(const std::string &_name, unsigned int _level, unsigned int _health,
          unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price);

    std::shared_ptr<equipment> clone() const override;
};

class Boots : public equipment {
public:
    Boots(const std::string &_name, unsigned int _level, unsigned int _health,
          unsigned int _armor, unsigned int _dodge, warStyle _style, coins _price);

    std::shared_ptr<equipment> clone() const override;
};

#endif
