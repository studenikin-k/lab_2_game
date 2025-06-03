#ifndef LAB_2_GAME_SLOT_OF_EQUIPMENT_H
#define LAB_2_GAME_SLOT_OF_EQUIPMENT_H


// данный enum определяет различие между разными типами экипировки
enum class slotOfEquipment {
    Helmet,
    Chestplate,
    Gloves,
    Pants,
    Boots,
};

// данный метод нужен для разыменовывания enum и для метода сохранения
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
// данный метод разыменовывания строки как enum необходим для того, чтобы загружать из БД предметы персонажа
inline slotOfEquipment stringToSlotOfEquipment(const std::string& str) {
    if (str == "Шлем") return slotOfEquipment::Helmet;
    if (str == "Нагрудник") return slotOfEquipment::Chestplate;
    if (str == "Перчатки") return slotOfEquipment::Gloves;
    if (str == "Штаны") return slotOfEquipment::Pants;
    if (str == "Ботинкит") return slotOfEquipment::Boots;
    throw std::invalid_argument("Неизвестный слот экипировки: " + str);
}


#endif //LAB_2_GAME_SLOT_OF_EQUIPMENT_H
