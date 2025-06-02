#include "include/all_headers.h"
#include <sqlite3.h>
#include <iostream>
#include <memory>    // Хотя shared_ptr не используется для character, он может быть нужен для членов Bag
#include <stdexcept> // Для std::invalid_argument
#include <filesystem>
#include <algorithm> // Для std::fill


std::shared_ptr<potion> createPotionByType(const std::string &type_str, const std::string &name, unsigned int level,
                                           unsigned int value, unsigned int copper) {
    coins itemPrice;
    itemPrice.setCopper(copper);

    if (type_str.find("healthPotion") != std::string::npos) {
        auto p = std::make_shared<healthPotion>(name, level, value, itemPrice);
        return p;
    } else if (type_str.find("damagePotion") != std::string::npos) {
        auto p = std::make_shared<damagePotion>(name, level, value, itemPrice);
        return p;
    } else if (type_str.find("armorPotion") != std::string::npos) {
        auto p = std::make_shared<armorPotion>(name, level, value, itemPrice);
        return p;
    } else if (type_str.find("accuracyPotion") != std::string::npos) {
        auto p = std::make_shared<accuracyPotion>(name, level, value, itemPrice);
        return p;
    } else if (type_str.find("stunPotion") != std::string::npos) {
        auto p = std::make_shared<stunPotion>(name, level, value, itemPrice);
        return p;
    } else if (type_str.find("dodgePotion") != std::string::npos) {
        auto p = std::make_shared<dodgePotion>(name, level, value, itemPrice);
        return p;
    }
    std::cerr << "Неизвестный тип зелья при загрузке: " << type_str << std::endl;
    return nullptr;
}

// Вспомогательная функция для создания объектов экипировки по слоту
std::shared_ptr<equipment> createEquipmentBySlot(const std::string &slotStr, const std::string &name,
                                                 unsigned int level, unsigned int health, unsigned int armor,
                                                 unsigned int dodge, warStyle style, unsigned int copper) {
    slotOfEquipment slot = stringToSlotOfEquipment(slotStr);
    coins itemPrice;
    itemPrice.setCopper(copper);

    switch (slot) {
        case slotOfEquipment::Helmet:
            return std::make_shared<Helmet>(name, level, health, armor, dodge, style, itemPrice);
        case slotOfEquipment::Chestplate:
            return std::make_shared<Chestplate>(name, level, health, armor, dodge, style, itemPrice);
        case slotOfEquipment::Gloves:
            return std::make_shared<Gloves>(name, level, health, armor, dodge, style, itemPrice);
        case slotOfEquipment::Pants:
            return std::make_shared<Pants>(name, level, health, armor, dodge, style, itemPrice);
        case slotOfEquipment::Boots:
            return std::make_shared<Boots>(name, level, health, armor, dodge, style, itemPrice);
        default:
            std::cerr << "Неизвестный слот экипировки при загрузке: " << slotStr << std::endl;
            return nullptr;
    }
}


bool loadCharacterFromDatabase(main_char &character) {
    // Принимаем main_char по ссылке
    std::string dbPath = getSavePath();
    if (dbPath.empty()) {
        std::cerr << "Не удалось определить путь для загрузки БД" << std::endl;
        return false;
    }

    if (!std::filesystem::exists(dbPath)) {
        std::cerr << "Файл сохранения не найден: " << dbPath << std::endl;
        return false;
    }

    std::cout << "Загружаем БД из: " << dbPath << std::endl;

    sqlite3 *db;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_stmt *stmt;
    int rc;
    int char_id = -1; // Идентификатор персонажа для связи с другими таблицами

    // 1. Загрузка данных персонажа
    const char *selectCharSQL =
            "SELECT id, name, level, experience, experienceToLevelUp, currentPosition, health, damage, armor, accuracy, stun, dodge, copper FROM Characters ORDER BY id DESC LIMIT 1;";
    rc = sqlite3_prepare_v2(db, selectCharSQL, -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            char_id = sqlite3_column_int(stmt, 0); // Получаем ID персонажа
            std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            unsigned int level = static_cast<unsigned int>(sqlite3_column_int64(stmt, 2));
            unsigned int experience = static_cast<unsigned int>(sqlite3_column_int64(stmt, 3));
            unsigned int experienceToLevelUp = static_cast<unsigned int>(sqlite3_column_int64(stmt, 4));
            unsigned int currentPosition = static_cast<unsigned int>(sqlite3_column_int64(stmt, 5));
            unsigned int health = static_cast<unsigned int>(sqlite3_column_int64(stmt, 6));
            unsigned int damage = static_cast<unsigned int>(sqlite3_column_int64(stmt, 7));
            unsigned int armor = static_cast<unsigned int>(sqlite3_column_int64(stmt, 8));
            unsigned int accuracy = static_cast<unsigned int>(sqlite3_column_int64(stmt, 9));
            unsigned int stun = static_cast<unsigned int>(sqlite3_column_int64(stmt, 10));
            unsigned int dodge = static_cast<unsigned int>(sqlite3_column_int64(stmt, 11));
            unsigned int copper = static_cast<unsigned int>(sqlite3_column_int64(stmt, 12));

            coins charBalance;
            charBalance.setCopper(copper);

            // Обновляем поля существующего объекта character
            character.setName(name);
            character.setLevel(level);
            character.setHealth(health);
            character.setDamage(damage);
            character.setArmor(armor);
            character.setAccuracy(accuracy);
            character.setStun(stun);
            character.setDodge(dodge);
            character.balance = charBalance;
            character.setCurrentPosition(currentPosition);
            character.setExperience(experience);
            character.setExperienceToLevelUp(experienceToLevelUp);
            character.set_id(char_id); // Устанавливаем ID для дальнейшего использования
        } else {
            std::cerr << "Нет сохраненных персонажей." << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при подготовке запроса Characters: " << sqlite3_errmsg(db) << std::endl;
    }

    if (char_id == -1) {
        // Если ID персонажа не был загружен, значит, персонаж не найден.
        sqlite3_close(db);
        return false;
    }

    // 2. Загрузка оружия (с новыми полями weapon_slot и weapon_style)
    // Очищаем существующее оружие
    character.gun = nullptr;
    const char *selectWeaponSQL =
            "SELECT name, level, damage, accuracy, stun, weapon_slot, weapon_style FROM Weapons WHERE character_id = ?;";
    rc = sqlite3_prepare_v2(db, selectWeaponSQL, -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, char_id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            unsigned int level = static_cast<unsigned int>(sqlite3_column_int64(stmt, 1));
            unsigned int damage = static_cast<unsigned int>(sqlite3_column_int64(stmt, 2));
            unsigned int accuracy = static_cast<unsigned int>(sqlite3_column_int64(stmt, 3));
            unsigned int stun = static_cast<unsigned int>(sqlite3_column_int64(stmt, 4));
            std::string weaponSlotStr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
            warStyle weaponStyle = static_cast<warStyle>(sqlite3_column_int(stmt, 6));

            character.gun = std::make_shared<weapon>(name, level, damage, accuracy, stun,
                                                     stringToSlotOfWeapon(weaponSlotStr), weaponStyle, coins{});
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при подготовке запроса Weapons: " << sqlite3_errmsg(db) << std::endl;
    }

    // 3. Загрузка экипировки
    // Очищаем существующую экипировку перед загрузкой, чтобы избежать дублирования
    character.Equipment.clear();
    const char *selectEquipmentSQL =
            "SELECT slot, name, level, health, armor, dodge, style, copper FROM Equipment WHERE character_id = ?;";
    rc = sqlite3_prepare_v2(db, selectEquipmentSQL, -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, char_id);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string slotStr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            unsigned int level = static_cast<unsigned int>(sqlite3_column_int64(stmt, 2));
            unsigned int health = static_cast<unsigned int>(sqlite3_column_int64(stmt, 3));
            unsigned int armor = static_cast<unsigned int>(sqlite3_column_int64(stmt, 4));
            unsigned int dodge = static_cast<unsigned int>(sqlite3_column_int64(stmt, 5));
            warStyle style = static_cast<warStyle>(sqlite3_column_int(stmt, 6));
            unsigned int copper = static_cast<unsigned int>(sqlite3_column_int64(stmt, 7));

            std::shared_ptr<equipment> equip_item = createEquipmentBySlot(
                slotStr, name, level, health, armor, dodge, style, copper);
            if (equip_item) {
                character.Equipment[stringToSlotOfEquipment(slotStr)] = equip_item;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при подготовке запроса Equipment: " << sqlite3_errmsg(db) << std::endl;
    }

    // 4. Загрузка зелий с пояса
    // Очищаем существующий пояс
    std::fill(character.Belt.begin(), character.Belt.end(), nullptr);
    const char *selectPotionsSQL =
            "SELECT belt_index, type, name, level, value, copper FROM Potions WHERE character_id = ?;";
    rc = sqlite3_prepare_v2(db, selectPotionsSQL, -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, char_id);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int belt_index = sqlite3_column_int(stmt, 0);
            std::string type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            unsigned int level = static_cast<unsigned int>(sqlite3_column_int64(stmt, 3));
            unsigned int value = static_cast<unsigned int>(sqlite3_column_int64(stmt, 4));
            unsigned int copper = static_cast<unsigned int>(sqlite3_column_int64(stmt, 5));

            if (belt_index >= 0 && belt_index < BELT_SIZE) {
                character.Belt[belt_index] = createPotionByType(type, name, level, value, copper);
            }
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при подготовке запроса Potions: " << sqlite3_errmsg(db) << std::endl;
    }


    const char *selectBagSQL =
            "SELECT item_type, name, level, attribute1, attribute2, attribute3, slot, style, copper, weapon_slot, potion_type_str FROM Bag WHERE character_id = ?;";
    rc = sqlite3_prepare_v2(db, selectBagSQL, -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, char_id);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string item_type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            unsigned int level = static_cast<unsigned int>(sqlite3_column_int64(stmt, 2));
            unsigned int attribute1 = static_cast<unsigned int>(sqlite3_column_int64(stmt, 3));
            unsigned int attribute2 = static_cast<unsigned int>(sqlite3_column_int64(stmt, 4));
            unsigned int attribute3 = static_cast<unsigned int>(sqlite3_column_int64(stmt, 5));
            std::string slotStr = (sqlite3_column_type(stmt, 6) != SQLITE_NULL)
                                      ? reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6))
                                      : "";
            warStyle style = static_cast<warStyle>(sqlite3_column_int(stmt, 7));
            unsigned int copper = static_cast<unsigned int>(sqlite3_column_int64(stmt, 8));
            std::string weaponSlotStr = (sqlite3_column_type(stmt, 9) != SQLITE_NULL)
                                            ? reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9))
                                            : "";
            std::string potionTypeStr = (sqlite3_column_type(stmt, 10) != SQLITE_NULL)
                                            ? reinterpret_cast<const char *>(sqlite3_column_text(stmt, 10))
                                            : "";

            if (item_type == "equipment") {
                std::shared_ptr<equipment> equip_item = createEquipmentBySlot(
                    slotStr, name, level, attribute1, attribute2, attribute3, style, copper);
                if (equip_item) {
                    character.Bag.inputIntoBag(equip_item);
                }
            } else if (item_type == "weapon") {
                std::shared_ptr<weapon> loadedWeapon = std::make_shared<weapon>(
                    name, level, attribute1, attribute2, attribute3, stringToSlotOfWeapon(weaponSlotStr), style,
                    coins{});
                loadedWeapon->price.setCopper(copper);
                character.Bag.inputIntoBag(loadedWeapon);
            } else if (item_type == "potion") {
                std::shared_ptr<potion> loadedPotion = createPotionByType(
                    potionTypeStr, name, level, attribute1, copper);
                if (loadedPotion) {
                    character.Bag.inputIntoBag(loadedPotion);
                }
            }
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при подготовке запроса Bag: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_close(db);
    return true;
}
