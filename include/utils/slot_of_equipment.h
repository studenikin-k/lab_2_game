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
        case slotOfEquipment::Boots: return "Ботинкит";
        default: return "Шубы не продаём.";
    }
}

inline slotOfEquipment stringToSlotOfEquipment(const std::string& str) {
    if (str == "Шлем") return slotOfEquipment::Helmet;
    if (str == "Нагрудник") return slotOfEquipment::Chestplate;
    if (str == "Перчатки") return slotOfEquipment::Gloves;
    if (str == "Штаны") return slotOfEquipment::Pants;
    if (str == "Ботинкит") return slotOfEquipment::Boots;
    throw std::invalid_argument("Неизвестный слот экипировки: " + str);
}


#endif //LAB_2_GAME_SLOT_OF_EQUIPMENT_H
