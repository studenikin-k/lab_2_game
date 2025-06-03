#ifndef LAB_2_GAME_SLOT_OF_POTION_H
#define LAB_2_GAME_SLOT_OF_POTION_H
#include "iostream"
#include "unordered_map"

// данный enum определяет различие между разными типами зелий
enum class slotOfPotion{
    Health,
    Damage,
    Armor,
    Accuracy,
    Stun,
    Dodge
};

// данный метод нужен для разыменовывания enum и для метода сохранения
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
// данный метод разыменовывания строки как enum необходим для того, чтобы загружать из БД предметы персонажа
inline slotOfPotion stringToSlotOfPotion(const std::string& str) {
    if (str == "Здоровье") return slotOfPotion::Health;
    if (str == "Урон") return slotOfPotion::Damage;
    if (str == "Броня") return slotOfPotion::Armor;
    if (str == "Точность") return slotOfPotion::Accuracy;
    if (str == "Оглушение") return slotOfPotion::Stun;
    if (str == "Уворот") return slotOfPotion::Dodge;
    throw std::invalid_argument("Неизвестный слот зелья: " + str);
}

#endif //LAB_2_GAME_SLOT_OF_POTION_H
