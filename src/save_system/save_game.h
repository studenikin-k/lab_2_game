#ifndef SAVE_GAME_H
#define SAVE_GAME_H
#include "../characters/main_char/main_char.h"
#include "../weapon/weapon.h"
#include "../equipment/equipment.h"
#include "../potion/potion.h"
#include "../coins/coins.h"
#include "../../utils/slot_of_equipment.h"
#include "../../utils/slot_of_weapon.h"
#include "../../utils/war_style.h"
#include <sqlite3.h>

void saveCharacterToDatabase(const main_char &character);

std::string getSavePath();

bool execSQL(sqlite3 *db, const std::string &sql);


#endif //SAVE_GAME_H
