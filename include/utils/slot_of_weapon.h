#ifndef LAB_2_GAME_SLOT_OF_WEAPON_H
#define LAB_2_GAME_SLOT_OF_WEAPON_H

// данный enum определяет различие между разными типами оружия
enum class slotOfWeapon {
    Axe,
    Mace,
    Sword,
    Blade,
    Epee,
    Fork,
    Glaive,
    Spear,
};

// данный метод нужен для разыменовывания enum и для метода сохранения
inline std::string slotOfWeaponToString(slotOfWeapon slot) {
    switch (slot) {
        case slotOfWeapon::Sword: return "Меч";
        case slotOfWeapon::Blade: return "Клинок";
        case slotOfWeapon::Axe: return "Топор";
        case slotOfWeapon::Glaive: return "Глефа";
        case slotOfWeapon::Mace: return "Булава";
        case slotOfWeapon::Epee: return "Шпага";
        case slotOfWeapon::Fork: return "Вилы";
        case slotOfWeapon::Spear: return "Копьё";
        default: return "Палками в другой игре махай, а луком в арбузы стреляй. "
                    "Тут игра про воинов, настоящих мужиков. \n";
    }
}

// данный метод разыменовывания строки как enum необходим для того, чтобы загружать из БД предметы персонажа
inline slotOfWeapon stringToSlotOfWeapon(const std::string &str) {
    if (str == "Топор") return slotOfWeapon::Axe;
    if (str == "Булава") return slotOfWeapon::Mace;
    if (str == "Меч") return slotOfWeapon::Sword;
    if (str == "Клинок") return slotOfWeapon::Blade;
    if (str == "Шпага") return slotOfWeapon::Epee;
    if (str == "Вилы") return slotOfWeapon::Fork;
    if (str == "Глефа") return slotOfWeapon::Glaive;
    if (str == "Копьё") return slotOfWeapon::Spear;
    throw std::invalid_argument("Неизвестный тип оружия: " + str);
}


#endif //LAB_2_GAME_SLOT_OF_WEAPON_H
