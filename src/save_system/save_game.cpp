#include "save_game.h"
#include <sqlite3.h>
#include <filesystem>
#include <iostream>
#include <typeinfo> // Для typeid
#include <string>

#define PROJECT_ROOT_PATH PROJECT_ROOT_PATH_DEF

std::string getSavePath() {
    std::string saveDir = std::string(PROJECT_ROOT_PATH) + "/save";
    if (!std::filesystem::exists(saveDir)) {
        try {
            std::filesystem::create_directory(saveDir);
            std::filesystem::permissions(saveDir,
                std::filesystem::perms::owner_all |
                std::filesystem::perms::group_read |
                std::filesystem::perms::others_read,
                std::filesystem::perm_options::replace);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при создании папки save: " << e.what() << std::endl;
            return "";
        }
    }
    return saveDir + "/character_save.db";
}

bool execSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQLite error: " << errMsg << "\nSQL: " << sql << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

void saveCharacterToDatabase(const main_char& character) {
    std::string dbPath = getSavePath();
    if (dbPath.empty()) {
        std::cerr << "Не удалось определить путь для сохранения БД" << std::endl;
        return;
    }

    // Удаляем старую базу данных перед сохранением новой
    if (std::filesystem::exists(dbPath)) {
        try {
            std::filesystem::remove(dbPath);
            std::cout << "Удалена старая база данных: " << dbPath << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при удалении старой базы данных: " << e.what() << std::endl;
            return;
        }
    }

    std::cout << "Сохраняем БД в: " << dbPath << std::endl;

    sqlite3* db;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Создание таблиц (с обновленной схемой)
    const char* createTablesSQL = R"(
        CREATE TABLE IF NOT EXISTS Characters (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            level INTEGER,
            experience INTEGER,
            experienceToLevelUp INTEGER,
            currentPosition INTEGER,
            health INTEGER,
            damage INTEGER,
            armor INTEGER,
            accuracy INTEGER,
            stun INTEGER,
            dodge INTEGER,
            copper INTEGER
        );

        CREATE TABLE IF NOT EXISTS Weapons (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            character_id INTEGER,
            name TEXT,
            level INTEGER,
            damage INTEGER,
            accuracy INTEGER,
            stun INTEGER,
            weapon_slot TEXT,
            weapon_style INTEGER,
            FOREIGN KEY(character_id) REFERENCES Characters(id)
        );

        CREATE TABLE IF NOT EXISTS Equipment (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            character_id INTEGER,
            slot TEXT,
            name TEXT,
            level INTEGER,
            health INTEGER,
            armor INTEGER,
            dodge INTEGER,
            style INTEGER,
            copper INTEGER,
            FOREIGN KEY(character_id) REFERENCES Characters(id)
        );

        CREATE TABLE IF NOT EXISTS Potions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            character_id INTEGER,
            belt_index INTEGER,
            type TEXT,
            name TEXT,
            level INTEGER,
            value INTEGER,
            copper INTEGER,
            FOREIGN KEY(character_id) REFERENCES Characters(id)
        );

        CREATE TABLE IF NOT EXISTS Bag (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            character_id INTEGER,
            item_type TEXT,
            name TEXT,
            level INTEGER,
            attribute1 INTEGER,
            attribute2 INTEGER,
            attribute3 INTEGER,
            slot TEXT,
            style INTEGER,
            copper INTEGER,
            weapon_slot TEXT,     -- Для оружия в сумке
            potion_type_str TEXT, -- Для зелий в сумке
            FOREIGN KEY(character_id) REFERENCES Characters(id)
        );
    )";

    if (!execSQL(db, createTablesSQL)) {
        sqlite3_close(db);
        return;
    }

    // Начало транзакции
    execSQL(db, "BEGIN TRANSACTION;");

    // Сохраняем персонажа с использованием подготовленных запросов
    sqlite3_stmt* stmt_char;
    const char* insertCharSQL = "INSERT INTO Characters (name, level, experience, experienceToLevelUp, currentPosition, health, damage, armor, accuracy, stun, dodge, copper) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    if (sqlite3_prepare_v2(db, insertCharSQL, -1, &stmt_char, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка при подготовке запроса Characters: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt_char, 1, character.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt_char, 2, character.getLevel());
    sqlite3_bind_int(stmt_char, 3, character.getExperience());
    sqlite3_bind_int(stmt_char, 4, character.getExperienceToLevelUp());
    sqlite3_bind_int(stmt_char, 5, character.getCurrentPosition());
    sqlite3_bind_int(stmt_char, 6, character.getHealth());
    sqlite3_bind_int(stmt_char, 7, character.getDamage());
    sqlite3_bind_int(stmt_char, 8, character.getArmor());
    sqlite3_bind_int(stmt_char, 9, character.getAccuracy());
    sqlite3_bind_int(stmt_char, 10, character.getStun());
    sqlite3_bind_int(stmt_char, 11, character.getDodge());
    sqlite3_bind_int(stmt_char, 12, character.balance.getCopper());

    if (sqlite3_step(stmt_char) != SQLITE_DONE) {
        std::cerr << "Ошибка при выполнении запроса Characters: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt_char);
        execSQL(db, "ROLLBACK;"); // Откатываем транзакцию при ошибке
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(stmt_char);

    int char_id = sqlite3_last_insert_rowid(db);

    // Оружие
    if (character.gun) {
        sqlite3_stmt* stmt_weapon;
        const char* insertWeaponSQL = "INSERT INTO Weapons (character_id, name, level, damage, accuracy, stun, weapon_slot, weapon_style) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
        if (sqlite3_prepare_v2(db, insertWeaponSQL, -1, &stmt_weapon, nullptr) != SQLITE_OK) {
            std::cerr << "Ошибка при подготовке запроса Weapons: " << sqlite3_errmsg(db) << std::endl;
            execSQL(db, "ROLLBACK;");
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_int(stmt_weapon, 1, char_id);
        sqlite3_bind_text(stmt_weapon, 2, character.gun->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt_weapon, 3, character.gun->getLevel());
        sqlite3_bind_int(stmt_weapon, 4, character.gun->getDamage());
        sqlite3_bind_int(stmt_weapon, 5, character.gun->getAccuracy());
        sqlite3_bind_int(stmt_weapon, 6, character.gun->getStun());
        sqlite3_bind_text(stmt_weapon, 7, slotOfWeaponToString(character.gun->getSlot()).c_str(), -1, SQLITE_TRANSIENT); // НОВОЕ
        sqlite3_bind_int(stmt_weapon, 8, static_cast<int>(character.gun->style)); // НОВОЕ

        if (sqlite3_step(stmt_weapon) != SQLITE_DONE) {
            std::cerr << "Ошибка при выполнении запроса Weapons: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt_weapon);
            execSQL(db, "ROLLBACK;");
            sqlite3_close(db);
            return;
        }
        sqlite3_finalize(stmt_weapon);
    }

    // Экипировка
    sqlite3_stmt* stmt_equip;
    const char* insertEquipSQL = "INSERT INTO Equipment (character_id, slot, name, level, health, armor, dodge, style, copper) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
    if (sqlite3_prepare_v2(db, insertEquipSQL, -1, &stmt_equip, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка при подготовке запроса Equipment: " << sqlite3_errmsg(db) << std::endl;
        execSQL(db, "ROLLBACK;");
        sqlite3_close(db);
        return;
    }
    for (const auto& [slot, equip] : character.Equipment) {
        if (!equip) continue;
        sqlite3_bind_int(stmt_equip, 1, char_id);
        sqlite3_bind_text(stmt_equip, 2, slotOfEquipmentToString(slot).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt_equip, 3, equip->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt_equip, 4, equip->getLevel());
        sqlite3_bind_int(stmt_equip, 5, equip->getHealth());
        sqlite3_bind_int(stmt_equip, 6, equip->getArmor());
        sqlite3_bind_int(stmt_equip, 7, equip->getDodge());
        sqlite3_bind_int(stmt_equip, 8, static_cast<int>(equip->getStyle()));
        sqlite3_bind_int(stmt_equip, 9, equip->price.getCopper());

        if (sqlite3_step(stmt_equip) != SQLITE_DONE) {
            std::cerr << "Ошибка при выполнении запроса Equipment: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_reset(stmt_equip); // Сбрасываем для следующей итерации или выхода
            execSQL(db, "ROLLBACK;");
            sqlite3_close(db);
            return;
        }
        sqlite3_reset(stmt_equip); // Сбрасываем стейтмент для повторного использования
    }
    sqlite3_finalize(stmt_equip);


    // Пояс
    sqlite3_stmt* stmt_potion;
    const char* insertPotionSQL = "INSERT INTO Potions (character_id, belt_index, type, name, level, value, copper) VALUES (?, ?, ?, ?, ?, ?, ?);";
    if (sqlite3_prepare_v2(db, insertPotionSQL, -1, &stmt_potion, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка при подготовке запроса Potions: " << sqlite3_errmsg(db) << std::endl;
        execSQL(db, "ROLLBACK;");
        sqlite3_close(db);
        return;
    }
    for (int i = 0; i < BELT_SIZE; ++i) {
        if (!character.Belt[i]) continue;
        auto& p = character.Belt[i];
        std::string potionType = typeid(*p).name();
        int value = 0;
        if (auto hp = dynamic_cast<healthPotion*>(p.get())) value = hp->getHealth();
        else if (auto dp = dynamic_cast<damagePotion*>(p.get())) value = dp->getDamage();
        else if (auto ap = dynamic_cast<armorPotion*>(p.get())) value = ap->getArmor();
        else if (auto acp = dynamic_cast<accuracyPotion*>(p.get())) value = acp->getAccuracy();
        else if (auto sp = dynamic_cast<stunPotion*>(p.get())) value = sp->getStun();
        else if (auto dpn = dynamic_cast<dodgePotion*>(p.get())) value = dpn->getDodge();

        sqlite3_bind_int(stmt_potion, 1, char_id);
        sqlite3_bind_int(stmt_potion, 2, i);
        sqlite3_bind_text(stmt_potion, 3, potionType.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt_potion, 4, p->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt_potion, 5, p->getLevel());
        sqlite3_bind_int(stmt_potion, 6, value);
        sqlite3_bind_int(stmt_potion, 7, p->price.getCopper());

        if (sqlite3_step(stmt_potion) != SQLITE_DONE) {
            std::cerr << "Ошибка при выполнении запроса Potions: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_reset(stmt_potion);
            execSQL(db, "ROLLBACK;");
            sqlite3_close(db);
            return;
        }
        sqlite3_reset(stmt_potion);
    }
    sqlite3_finalize(stmt_potion);


    // Портфель (единый подготовленный запрос для всех типов, но с условной привязкой)
    sqlite3_stmt* stmt_bag;
    const char* insertBagSQL = "INSERT INTO Bag (character_id, item_type, name, level, attribute1, attribute2, attribute3, slot, style, copper, weapon_slot, potion_type_str) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    if (sqlite3_prepare_v2(db, insertBagSQL, -1, &stmt_bag, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка при подготовке запроса Bag: " << sqlite3_errmsg(db) << std::endl;
        execSQL(db, "ROLLBACK;");
        sqlite3_close(db);
        return;
    }

    for (auto& e : character.Bag.bagEquipment) {
        sqlite3_bind_int(stmt_bag, 1, char_id);
        sqlite3_bind_text(stmt_bag, 2, "equipment", -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt_bag, 3, e->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt_bag, 4, e->getLevel());
        sqlite3_bind_int(stmt_bag, 5, e->getHealth());
        sqlite3_bind_int(stmt_bag, 6, e->getArmor());
        sqlite3_bind_int(stmt_bag, 7, e->getDodge());
        sqlite3_bind_text(stmt_bag, 8, slotOfEquipmentToString(e->getSlot()).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt_bag, 9, static_cast<int>(e->getStyle()));
        sqlite3_bind_int(stmt_bag, 10, e->price.getCopper());
        sqlite3_bind_null(stmt_bag, 11); // weapon_slot - NULL для экипировки
        sqlite3_bind_null(stmt_bag, 12); // potion_type_str - NULL для экипировки

        if (sqlite3_step(stmt_bag) != SQLITE_DONE) {
            std::cerr << "Ошибка при выполнении запроса Bag (equipment): " << sqlite3_errmsg(db) << std::endl;
            sqlite3_reset(stmt_bag);
            execSQL(db, "ROLLBACK;");
            sqlite3_close(db);
            return;
        }
        sqlite3_reset(stmt_bag);
    }

    for (auto& w : character.Bag.bagWeapon) {
        sqlite3_bind_int(stmt_bag, 1, char_id);
        sqlite3_bind_text(stmt_bag, 2, "weapon", -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt_bag, 3, w->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt_bag, 4, w->getLevel());
        sqlite3_bind_int(stmt_bag, 5, w->getDamage());
        sqlite3_bind_int(stmt_bag, 6, w->getAccuracy());
        sqlite3_bind_int(stmt_bag, 7, w->getStun());
        sqlite3_bind_null(stmt_bag, 8); // slot - NULL для оружия
        sqlite3_bind_int(stmt_bag, 9, static_cast<int>(w->style));
        sqlite3_bind_int(stmt_bag, 10, w->price.getCopper());
        sqlite3_bind_text(stmt_bag, 11, slotOfWeaponToString(w->getSlot()).c_str(), -1, SQLITE_TRANSIENT); // НОВОЕ
        sqlite3_bind_null(stmt_bag, 12); // potion_type_str - NULL для оружия

        if (sqlite3_step(stmt_bag) != SQLITE_DONE) {
            std::cerr << "Ошибка при выполнении запроса Bag (weapon): " << sqlite3_errmsg(db) << std::endl;
            sqlite3_reset(stmt_bag);
            execSQL(db, "ROLLBACK;");
            sqlite3_close(db);
            return;
        }
        sqlite3_reset(stmt_bag);
    }

    for (auto& p : character.Bag.bagPotion) {
        int value = 0;
        // Здесь используем более надежный способ получения строкового имени типа зелья для Bag
        std::string potionTypeStr;
        if (auto hp = dynamic_cast<healthPotion*>(p.get())) { value = hp->getHealth(); potionTypeStr = "healthPotion"; }
        else if (auto dp = dynamic_cast<damagePotion*>(p.get())) { value = dp->getDamage(); potionTypeStr = "damagePotion"; }
        else if (auto ap = dynamic_cast<armorPotion*>(p.get())) { value = ap->getArmor(); potionTypeStr = "armorPotion"; }
        else if (auto acp = dynamic_cast<accuracyPotion*>(p.get())) { value = acp->getAccuracy(); potionTypeStr = "accuracyPotion"; }
        else if (auto sp = dynamic_cast<stunPotion*>(p.get())) { value = sp->getStun(); potionTypeStr = "stunPotion"; }
        else if (auto dpn = dynamic_cast<dodgePotion*>(p.get())) { value = dpn->getDodge(); potionTypeStr = "dodgePotion"; }

        sqlite3_bind_int(stmt_bag, 1, char_id);
        sqlite3_bind_text(stmt_bag, 2, "potion", -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt_bag, 3, p->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt_bag, 4, p->getLevel());
        sqlite3_bind_int(stmt_bag, 5, value);
        sqlite3_bind_null(stmt_bag, 6); // attribute2 - NULL для зелий
        sqlite3_bind_null(stmt_bag, 7); // attribute3 - NULL для зелий
        sqlite3_bind_null(stmt_bag, 8); // slot - NULL для зелий
        sqlite3_bind_null(stmt_bag, 9); // style - NULL для зелий
        sqlite3_bind_int(stmt_bag, 10, p->price.getCopper());
        sqlite3_bind_null(stmt_bag, 11); // weapon_slot - NULL для зелий
        sqlite3_bind_text(stmt_bag, 12, potionTypeStr.c_str(), -1, SQLITE_TRANSIENT); // НОВОЕ

        if (sqlite3_step(stmt_bag) != SQLITE_DONE) {
            std::cerr << "Ошибка при выполнении запроса Bag (potion): " << sqlite3_errmsg(db) << std::endl;
            sqlite3_reset(stmt_bag);
            execSQL(db, "ROLLBACK;");
            sqlite3_close(db);
            return;
        }
        sqlite3_reset(stmt_bag);
    }
    sqlite3_finalize(stmt_bag);


    // Завершаем транзакцию
    execSQL(db, "COMMIT;");
    sqlite3_close(db);
}