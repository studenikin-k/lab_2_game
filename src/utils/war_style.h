#ifndef LAB_2_GAME_WAR_STYLE_H
#define LAB_2_GAME_WAR_STYLE_H

enum class warStyle{
    Damage,
    Dodge,
    Armor,
    Elite
};

inline std::string warStyleToString(warStyle style) {
    switch (style) {
        case warStyle::Damage: return "Урон";
        case warStyle::Armor: return "Броня";
        case warStyle::Dodge: return "Уворот";
        case warStyle::Elite: return "Элита";
        default: return "Если вы собрались играть за орду, вы ошиблись игрой, тут уже победил альянс \n";
    }
}


#endif //LAB_2_GAME_WAR_STYLE_H
