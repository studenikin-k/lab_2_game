#ifndef LAB_2_GAME_POTION_H
#define LAB_2_GAME_POTION_H

#include <iostream>
#include <memory>
#include "../../all_headers.h"

class potion {
    // класс абстракция для всех зелий
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

    virtual std::shared_ptr<potion> clone() const = 0;

private:
    std::string name{};
    unsigned int level{};
};

// зелье здоровья
class healthPotion : public potion {
public:

    healthPotion(const std::string &_name, unsigned int _level, unsigned int _health, coins _price);

    [[nodiscard]] unsigned int getHealth() const;

    void setHealth(unsigned int _health);

    void showInShop() override;

    void showInInventory() override;

    std::shared_ptr<potion> clone() const override;

private:
    unsigned int health{};
};

//класс для зелий урона
class damagePotion : public potion {
public:

    damagePotion(const std::string &_name, unsigned int _level, unsigned int _damage, coins _price);

    [[nodiscard]] unsigned int getDamage() const;

    void setDamage(unsigned int damage);

    void showInShop() override;

    void showInInventory() override;

    std::shared_ptr<potion> clone() const override;

private:
    unsigned int damage{};
};

// класс зелий для брони
class armorPotion : public potion {
public:

    armorPotion(const std::string &_name, unsigned int _level, unsigned int _armor, coins _price);

    [[nodiscard]] unsigned int getArmor() const;

    void setArmor(unsigned int armor);

    void showInShop() override;

    void showInInventory() override;

    std::shared_ptr<potion> clone() const override;

private:
    unsigned int armor{};
};

//класс зелий точности
class accuracyPotion : public potion {
public:
    accuracyPotion(const std::string &_name, unsigned int _level, unsigned int _accuracy);

    accuracyPotion(const std::string &_name, unsigned int _level, unsigned int _accuracy, coins _price);

    [[nodiscard]] unsigned int getAccuracy() const;

    void setAccuracy(unsigned int accuracy);

    void showInShop() override;

    void showInInventory() override;

    std::shared_ptr<potion> clone() const override;

private:
    unsigned int accuracy{};
};

// класс для зелий повышения шанса оглушения
class stunPotion : public potion {
public:

    stunPotion(const std::string &_name, unsigned int _level, unsigned int _stun, coins _price);

    [[nodiscard]] unsigned int getStun() const;

    void setStun(unsigned int _stun);

    void showInShop() override;

    void showInInventory() override;

    std::shared_ptr<potion> clone() const override;

private:
    unsigned int stun{};
};

// класс для повышения зелий уворота
class dodgePotion : public potion {
public:

    dodgePotion(const std::string &_name, unsigned int _level, unsigned int _dodge, coins price);

    [[nodiscard]] unsigned int getDodge() const;

    void setDodge(unsigned int dodge);

    void showInShop() override;

    void showInInventory() override;

    std::shared_ptr<potion> clone() const override;

private:
    unsigned int dodge{};
};

#endif //LAB_2_GAME_POTION_H
