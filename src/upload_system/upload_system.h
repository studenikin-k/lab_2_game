#ifndef UPLOAD_SYSTEM_H
#define UPLOAD_SYSTEM_H
#include <sqlite3.h>
#include "characters/main_char/main_char.h"
#include "../weapon/weapon.h"
#include "../equipment/equipment.h"
#include "../potion/potion.h"
#include "../coins/coins.h"
#include "../../utils/slot_of_equipment.h"
#include "../../utils/slot_of_weapon.h"
#include "../../utils/war_style.h"
#include "../save_system/save_game.h"

bool loadCharacterFromDatabase(main_char& character);

#endif //UPLOAD_SYSTEM_H
