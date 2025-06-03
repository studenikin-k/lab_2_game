#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include <sqlite3.h>
#include "../all_headers.h"

void saveCharacterToDatabase(const main_char &character);

std::string getSavePath();

bool execSQL(sqlite3 *db, const std::string &sql);


#endif //SAVE_GAME_H
