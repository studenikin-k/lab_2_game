#ifndef LAB_2_GAME_SLOT_OF_WEAPON_H
#define LAB_2_GAME_SLOT_OF_WEAPON_H

enum class slotOfWeapon{
    Axe,
    Mace,
    Sword,
    Blade,
    Epee,
    Fork,
    Glaive,
    Spear
};

inline std::string slotOfWeaponToString(slotOfWeapon slot) {
    switch (slot) {
        case slotOfWeapon::Sword: return "Меч";
        case slotOfWeapon::Blade: return "Клинок";
        case slotOfWeapon::Axe: return "Топор";
        case slotOfWeapon::Glaive: return "Глефа";
        case slotOfWeapon::Mace: return "Булава";
        case slotOfWeapon::Epee:return "Шпага";
        case slotOfWeapon::Fork: return "Вилы";
        case slotOfWeapon::Spear: return "Копьё";
        default: return "Палками в другой игре махай, а луком в арбузы стреляй. "
                        "Тут игра про воинов, настоящих мужиков. \n";
    }
}

#endif //LAB_2_GAME_SLOT_OF_WEAPON_H
