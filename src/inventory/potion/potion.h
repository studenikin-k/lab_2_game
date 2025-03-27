#ifndef LAB_2_GAME_POTION_H
#define LAB_2_GAME_POTION_H

#include <iostream>
#include "../../utils/slot_of_potion.h"
#include "../coins/coins.h"

class potion {
public:

    potion() = default;

   virtual ~potion() = default;

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &name);

    [[nodiscard]] unsigned int getLevel() const;

    void setLevel(unsigned int level);

    slotOfPotion slot{};

    virtual void showInShop() = 0;

    virtual void showInInventory() = 0;

    [[nodiscard]] slotOfPotion getSlot() const;

    void setSlot(slotOfPotion slot);

    coins price{};

private:
    std::string name{};
    unsigned int level{};

};

class healthPotion : public potion {
public:
    healthPotion(const std::string &_name, unsigned int _level, slotOfPotion _slot, unsigned int _health);

    [[nodiscard]] unsigned int getHealth() const;

    void setHealth(unsigned int _health);

    void showInShop() override;

    void showInInventory() override;


private:
    unsigned int health{};
};

class damagePotion : public potion {
public:
    damagePotion(const std::string &_name, unsigned int _level, slotOfPotion _slot, unsigned int _damage);

    [[nodiscard]] unsigned int getDamage() const;

    void setDamage(unsigned int damage);

    void showInShop() override;

    void showInInventory() override;
private:
    unsigned int damage{};
};

class armorPotion : public potion {
public:
    armorPotion(const std::string &_name, unsigned int _level, slotOfPotion slot, unsigned int _armor);

    [[nodiscard]] unsigned int getArmor() const;

    void setArmor(unsigned int armor);

    void showInShop() override;

    void showInInventory() override;

private:
    unsigned int armor{};
};

class accuracyPotion : public potion {
public:
    accuracyPotion(const std::string &_name, unsigned int _level, slotOfPotion slot, unsigned int _accuracy);

    [[nodiscard]] unsigned int getAccuracy() const;

    void setAccuracy(unsigned int accuracy);

    void showInShop() override;

    void showInInventory() override;

private:
    unsigned int accuracy{};
};

class stunPotion : public potion {
public:
    stunPotion(const std::string &_name, unsigned int _level, slotOfPotion slot, unsigned int _stun);

    [[nodiscard]] unsigned int getStun() const;

    void setStun(unsigned int _stun);

    void showInShop() override;

    void showInInventory() override;

private:

    unsigned int stun{};
};

class dodgePotion : public potion {
public:
    dodgePotion(const std::string &_name, unsigned int _level, slotOfPotion slot, unsigned int _dodge);

    [[nodiscard]] unsigned int getDodge() const;

    void setDodge(unsigned int dodge);

    void showInShop() override;

    void showInInventory() override;

private:
    unsigned int dodge{};

};


#endif //LAB_2_GAME_POTION_H
