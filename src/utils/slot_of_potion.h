#ifndef LAB_2_GAME_SLOT_OF_POTION_H
#define LAB_2_GAME_SLOT_OF_POTION_H
#include "iostream"
#include "unordered_map"

enum class slotOfPotion{
    Health,
    Damage,
    Armor,
    Accuracy,
    Stun,
    Dodge
};

inline std::string slotOfPotionToString(slotOfPotion slot) {
    switch (slot) {
        case slotOfPotion::Health: return "Здоровье";
        case slotOfPotion::Damage: return "Урон";
        case slotOfPotion::Armor: return "Броня";
        case slotOfPotion::Accuracy: return "Точность";
        case slotOfPotion::Stun: return "Оглушение";
        case slotOfPotion::Dodge: return "Уворот";
        default: return "Водки здесь не будет, не ждите";
    }
}
#endif //LAB_2_GAME_SLOT_OF_POTION_H
