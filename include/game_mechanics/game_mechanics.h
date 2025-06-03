#ifndef GAME_MECHANICS_H
#define GAME_MECHANICS_H

#include "../all_headers.h"

void gameLoop(main_char &hero, map &gameMap);
// запускает цикл игры, позволяет
// передвигаться, торговать, воевать, осматривать свою экипировку и т.д.

void gainExperience(main_char &player, unsigned int expGained);
// функция используется в цикле игры для того, чтобы персонаж получал опыт после боя и если
// достигает нужного числа, то в таком случае срабатывает notifyLevelUp

void notifyLevelUp(main_char &hero);
// функция используется для повышения уровня персонажа, а также увеличения характеристик




#endif //GAME_MECHANICS_H
