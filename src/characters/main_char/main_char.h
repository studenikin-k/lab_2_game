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
#include "../../features/clear_screen.h"

constexpr int BELT_SIZE = 6;

class main_char : public character {
public:
    [[nodiscard]] unsigned int getExperience() const;

    void setExperience(const unsigned int experience);

    [[nodiscard]] unsigned int getExperienceToLevelUp() const;

    void setExperienceToLevelUp(const unsigned int experience_to_level_up);

    [[nodiscard]] unsigned int getCurrentPosition() const;

    void setCurrentPosition(unsigned int current_position);

    main_char(const std::string &_name, unsigned int _level, unsigned int _health, unsigned int _damage,
              unsigned int _armor, unsigned int _accuracy, unsigned int _stun,
              unsigned int _dodge, const coins &cash, const unsigned int position);

    ~main_char() = default;

    std::unordered_map<slotOfEquipment, std::shared_ptr<equipment> > Equipment; // снаряжение персонажа
    std::array<std::shared_ptr<potion>, BELT_SIZE> Belt{}; // пояс зелий персонажа

    bag Bag{}; // портфель персонажа, содержит в себе векторы оружия, снаряжения и зелий

    std::shared_ptr<weapon> gun; // оружие персонажа

    coins balance{}; // баланс персонажа, содержит в себе медяки, перерасчитываемое алгортимом: 1 золото 100 серебра
    // 1 серебро, 100 медяков

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

    void showBag(); //метод осмотра портфеля, проходим по векторам снаряжения, оружия, зелий, позволяет
    // надевать нужные предметы в экипировку

    void showGear(); // метод осмотра экипировки, позволяет снять предметы с экипировки, снять оружие,
    // снять элемент пояса зелий

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &name);

    unsigned int getLevel() const;

    void setLevel(unsigned int level);

    void usePotion();

private:
    unsigned int id{};

public:
    [[nodiscard]] unsigned int id1() const;

    void set_id(unsigned int id);

private:
    unsigned int experience = 0;
    unsigned int experienceToLevelUp = 100;
    unsigned int currentPosition;
    unsigned int level{};
    std::string name{};
};

std::ostream &operator<<(std::ostream &os, const main_char &pers);

#endif //LAB_2_GAME_MAIN_CHAR_H
