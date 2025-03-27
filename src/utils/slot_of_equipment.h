#ifndef LAB_2_GAME_SLOT_OF_EQUIPMENT_H
#define LAB_2_GAME_SLOT_OF_EQUIPMENT_H

enum class slotOfEquipment {
    Helmet,
    Chestplate,
    Gloves,
    Pants,
    Boots,
};

inline std::string slotOfEquipmentToString(slotOfEquipment slot) {
    switch (slot) {
        case slotOfEquipment::Helmet: return "Шлем";
        case slotOfEquipment::Chestplate: return "Нагрудник";
        case slotOfEquipment::Gloves: return "Перчатки";
        case slotOfEquipment::Pants: return "Штаны";
        case slotOfEquipment::Boots: return "Обувь";
        default: return "Шубы не продаём.";
    }
}

#endif //LAB_2_GAME_SLOT_OF_EQUIPMENT_H
