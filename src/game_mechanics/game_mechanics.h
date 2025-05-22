#ifndef GAME_MECHANICS_H
#define GAME_MECHANICS_H

#include "../characters/main_char/main_char.h"
#include "../map/map.h"
#include "../characters/opponent/opponent.h"

void gameLoop(main_char &hero, map &gameMap);
void gainExperience(main_char &player, unsigned int expGained);
void notifyLevelUp(main_char &hero);



#endif //GAME_MECHANICS_H
