#include "../../include/all_headers.h"

shop_location::shop_location(const std::string &name)
    : location(name) {
    Market.potionShop[0][slotOfPotion::Health] = std::make_shared<healthPotion>(
        "Малое зелье здоровья", 0, 10, coins {5});
    Market.potionShop[0][slotOfPotion::Damage] = std::make_shared<damagePotion>(
        "Малое зелье урона", 0, 5, coins{7});
    Market.potionShop[0][slotOfPotion::Accuracy] = std::make_shared<accuracyPotion>(
        "Малое зелье точности", 0, 3, coins{6});
    Market.potionShop[0][slotOfPotion::Stun] = std::make_shared<stunPotion>(
        "Малое зелье оглушения", 0, 5, coins{9});
    Market.potionShop[0][slotOfPotion::Dodge] = std::make_shared<dodgePotion>(
        "Малое зелье уворота", 0, 7, coins{8});
    Market.potionShop[0][slotOfPotion::Armor] = std::make_shared<armorPotion>(
        "Малое зелье брони", 0, 4, coins{6});


    Market.potionShop[1][slotOfPotion::Health] = std::make_shared<healthPotion>(
        "Зелье здоровья", 1, 25, coins{15});
    Market.potionShop[1][slotOfPotion::Damage] = std::make_shared<damagePotion>(
        "Зелье урона", 1, 10, coins{20});
    Market.potionShop[1][slotOfPotion::Accuracy] = std::make_shared<accuracyPotion>(
        "Зелье точности", 1, 8, coins{18});
    Market.potionShop[1][slotOfPotion::Stun] = std::make_shared<stunPotion>(
        "Зелье оглушения", 1, 10, coins{25});
    Market.potionShop[1][slotOfPotion::Dodge] = std::make_shared<dodgePotion>(
        "Зелье уворота", 1, 14, coins{22});
    Market.potionShop[1][slotOfPotion::Armor] = std::make_shared<armorPotion>(
        "Зелье брони", 1, 8, coins{20});

    Market.potionShop[2][slotOfPotion::Health] = std::make_shared<healthPotion>(
        "Большое зелье здоровья", 1, 40, coins{50});
    Market.potionShop[2][slotOfPotion::Damage] = std::make_shared<damagePotion>(
        " Большое Зелье урона", 1, 18, coins{40});
    Market.potionShop[2][slotOfPotion::Accuracy] = std::make_shared<accuracyPotion>(
        "Большое Зелье точности", 1, 8, coins{45});
    Market.potionShop[2][slotOfPotion::Stun] = std::make_shared<
        stunPotion>("Большое Зелье оглушения", 1, 13, coins{55});
    Market.potionShop[2][slotOfPotion::Dodge] = std::make_shared<
        dodgePotion>("Большое Зелье уворота", 1, 22, coins{60});
    Market.potionShop[2][slotOfPotion::Armor] = std::make_shared<armorPotion>(
        "Большое Зелье брони", 1, 15, coins{40});


    // --- ЭКИПИРОВКА (УРОВНИ 0, 1, 2) ---

    // --- Стиль: DAMAGE (Сила, тяжёлая сталь, железо) ---
    // Достоинства: урон, шанс оглушения, армор | Недостатки: точность, уворот | Средние: здоровье
    // Для экипировки мы акцентируем внимание на арморе и среднем здоровье, низком увороте.
    // Уровень 0
    Market.equipmentShop[0][slotOfEquipment::Helmet][warStyle::Damage] = std::make_shared<Helmet>(
        "Грубый Шлем Бойца", 0, 15, 8, 0, warStyle::Damage, coins{50});
    Market.equipmentShop[0][slotOfEquipment::Chestplate][warStyle::Damage] = std::make_shared<Chestplate>(
        "Кожаный Доспех Силы", 0, 20, 12, 0, warStyle::Damage, coins{70});
    Market.equipmentShop[0][slotOfEquipment::Gloves][warStyle::Damage] = std::make_shared<Gloves>(
        "Ладони Тяжелой Стали", 0, 8, 4, 0, warStyle::Damage, coins{30});
    Market.equipmentShop[0][slotOfEquipment::Pants][warStyle::Damage] = std::make_shared<Pants>(
        "Прочные Штаны Воина", 0, 18, 10, 0, warStyle::Damage, coins{60});
    Market.equipmentShop[0][slotOfEquipment::Boots][warStyle::Damage] = std::make_shared<Boots>(
        "Железные Сапоги Ярости", 0, 12, 6, 0, warStyle::Damage, coins{40});
    // Уровень 1
    Market.equipmentShop[1][slotOfEquipment::Helmet][warStyle::Damage] = std::make_shared<Helmet>(
        "Шлем Стального Быка", 1, 25, 15, 0, warStyle::Damage, coins{120});
    Market.equipmentShop[1][slotOfEquipment::Chestplate][warStyle::Damage] = std::make_shared<Chestplate>(
        "Нагрудник Сокрушителя", 1, 35, 20, 0, warStyle::Damage, coins{180});
    Market.equipmentShop[1][slotOfEquipment::Gloves][warStyle::Damage] = std::make_shared<Gloves>(
        "Перчатки Мощного Удара", 1, 12, 8, 0, warStyle::Damage, coins{80});
    Market.equipmentShop[1][slotOfEquipment::Pants][warStyle::Damage] = std::make_shared<Pants>(
        "Набедренники Разрушения", 1, 30, 18, 0, warStyle::Damage, coins{150});
    Market.equipmentShop[1][slotOfEquipment::Boots][warStyle::Damage] = std::make_shared<Boots>(
        "Сапоги Тяжелой Поступи", 1, 18, 10, 0, warStyle::Damage, coins{100});
    // Уровень 2
    Market.equipmentShop[2][slotOfEquipment::Helmet][warStyle::Damage] = std::make_shared<Helmet>(
        "Корона Титана", 2, 40, 25, 0, warStyle::Damage, coins{250});
    Market.equipmentShop[2][slotOfEquipment::Chestplate][warStyle::Damage] = std::make_shared<Chestplate>(
        "Доспех Древнего Воина", 2, 60, 35, 0, warStyle::Damage, coins{350});
    Market.equipmentShop[2][slotOfEquipment::Gloves][warStyle::Damage] = std::make_shared<Gloves>(
        "Кулаки Адаманта", 2, 25, 15, 0, warStyle::Damage, coins{150});
    Market.equipmentShop[2][slotOfEquipment::Pants][warStyle::Damage] = std::make_shared<Pants>(
        "Поножи Бога Войны", 2, 50, 28, 0, warStyle::Damage, coins{300});
    Market.equipmentShop[2][slotOfEquipment::Boots][warStyle::Damage] = std::make_shared<Boots>(
        "Ботинки Громовержца", 2, 30, 20, 0, warStyle::Damage, coins{200});

    // --- Стиль: DODGE (Уклонение, тишина, спокойствие, кожа, ткань) ---
    // Достоинства: уворот, урон, шанс оглушения | Недостатки: здоровье, броня | Средние: точность
    // Для экипировки акцент на увороте, низком здоровье/броне.
    // Уровень 0
    Market.equipmentShop[0][slotOfEquipment::Helmet][warStyle::Dodge] = std::make_shared<Helmet>(
        "Капюшон Тени", 0, 5, 2, 8, warStyle::Dodge, coins{55});
    Market.equipmentShop[0][slotOfEquipment::Chestplate][warStyle::Dodge] = std::make_shared<Chestplate>(
        "Мягкий Жилет Уклониста", 0, 8, 4, 12, warStyle::Dodge, coins{75});
    Market.equipmentShop[0][slotOfEquipment::Gloves][warStyle::Dodge] = std::make_shared<Gloves>(
        "Перчатки Тишины", 0, 2, 1, 5, warStyle::Dodge, coins{35});
    Market.equipmentShop[0][slotOfEquipment::Pants][warStyle::Dodge] = std::make_shared<Pants>(
        "Легкие Штаны Скрытности", 0, 6, 3, 10, warStyle::Dodge, coins{65});
    Market.equipmentShop[0][slotOfEquipment::Boots][warStyle::Dodge] = std::make_shared<Boots>(
        "Сапоги Шепота", 0, 4, 2, 7, warStyle::Dodge, coins{45});
    // Уровень 1
    Market.equipmentShop[1][slotOfEquipment::Helmet][warStyle::Dodge] = std::make_shared<Helmet>(
        "Маска Неуловимого", 1, 10, 5, 15, warStyle::Dodge, coins{125});
    Market.equipmentShop[1][slotOfEquipment::Chestplate][warStyle::Dodge] = std::make_shared<Chestplate>(
        "Мантия Ветра", 1, 15, 8, 20, warStyle::Dodge, coins{185});
    Market.equipmentShop[1][slotOfEquipment::Gloves][warStyle::Dodge] = std::make_shared<Gloves>(
        "Наручи Скольжения", 1, 5, 3, 10, warStyle::Dodge, coins{85});
    Market.equipmentShop[1][slotOfEquipment::Pants][warStyle::Dodge] = std::make_shared<Pants>(
        "Поножи Призрака", 1, 12, 6, 18, warStyle::Dodge, coins{155});
    Market.equipmentShop[1][slotOfEquipment::Boots][warStyle::Dodge] = std::make_shared<Boots>(
        "Ботинки Тени", 1, 8, 4, 14, warStyle::Dodge, coins{105});
    // Уровень 2
    Market.equipmentShop[2][slotOfEquipment::Helmet][warStyle::Dodge] = std::make_shared<Helmet>(
        "Шлем Тумана", 2, 18, 8, 25, warStyle::Dodge, coins{260});
    Market.equipmentShop[2][slotOfEquipment::Chestplate][warStyle::Dodge] = std::make_shared<Chestplate>(
        "Накидка Небытия", 2, 25, 12, 35, warStyle::Dodge, coins{360});
    Market.equipmentShop[2][slotOfEquipment::Gloves][warStyle::Dodge] = std::make_shared<Gloves>(
        "Перчатки Воздуха", 2, 10, 5, 18, warStyle::Dodge, coins{160});
    Market.equipmentShop[2][slotOfEquipment::Pants][warStyle::Dodge] = std::make_shared<Pants>(
        "Штаны-Призраки", 2, 20, 10, 30, warStyle::Dodge, coins{310});
    Market.equipmentShop[2][slotOfEquipment::Boots][warStyle::Dodge] = std::make_shared<Boots>(
        "Сапоги Сквозь Миры", 2, 15, 7, 25, warStyle::Dodge, coins{210});

    // --- Стиль: ARMOR (Крепость, точность, бронза) ---
    // Достоинства: здоровье, армор, точность | Недостатки: уворот, шанс оглушения | Средние: урон
    // Для экипировки акцент на здоровье и арморе.
    // Уровень 0
    Market.equipmentShop[0][slotOfEquipment::Helmet][warStyle::Armor] = std::make_shared<Helmet>(
        "Бронзовый Шлем Защитника", 0, 20, 10, 0, warStyle::Armor, coins{60});
    Market.equipmentShop[0][slotOfEquipment::Chestplate][warStyle::Armor] = std::make_shared<Chestplate>(
        "Медный Нагрудник Крепости", 0, 30, 15, 0, warStyle::Armor, coins{80});
    Market.equipmentShop[0][slotOfEquipment::Gloves][warStyle::Armor] = std::make_shared<Gloves>(
        "Рукавицы Брони", 0, 10, 5, 0, warStyle::Armor, coins{40});
    Market.equipmentShop[0][slotOfEquipment::Pants][warStyle::Armor] = std::make_shared<Pants>(
        "Поножи Бастиона", 0, 25, 12, 0, warStyle::Armor, coins{70});
    Market.equipmentShop[0][slotOfEquipment::Boots][warStyle::Armor] = std::make_shared<Boots>(
        "Ботинки Непоколебимости", 0, 15, 8, 0, warStyle::Armor, coins{50});
    // Уровень 1
    Market.equipmentShop[1][slotOfEquipment::Helmet][warStyle::Armor] = std::make_shared<Helmet>(
        "Шлем Неуязвимости", 1, 30, 18, 0, warStyle::Armor, coins{130});
    Market.equipmentShop[1][slotOfEquipment::Chestplate][warStyle::Armor] = std::make_shared<Chestplate>(
        "Доспех Стены", 1, 45, 25, 0, warStyle::Armor, coins{190});
    Market.equipmentShop[1][slotOfEquipment::Gloves][warStyle::Armor] = std::make_shared<Gloves>(
        "Перчатки Гвардейца", 1, 15, 10, 0, warStyle::Armor, coins{90});
    Market.equipmentShop[1][slotOfEquipment::Pants][warStyle::Armor] = std::make_shared<Pants>(
        "Поножи Твердыни", 1, 40, 22, 0, warStyle::Armor, coins{160});
    Market.equipmentShop[1][slotOfEquipment::Boots][warStyle::Armor] = std::make_shared<Boots>(
        "Сапоги Защитника", 1, 25, 14, 0, warStyle::Armor, coins{110});
    // Уровень 2
    Market.equipmentShop[2][slotOfEquipment::Helmet][warStyle::Armor] = std::make_shared<Helmet>(
        "Шлем Старой Крепости", 2, 50, 30, 0, warStyle::Armor, coins{270});
    Market.equipmentShop[2][slotOfEquipment::Chestplate][warStyle::Armor] = std::make_shared<Chestplate>(
        "Кираса Горного Короля", 2, 70, 45, 0, warStyle::Armor, coins{380});
    Market.equipmentShop[2][slotOfEquipment::Gloves][warStyle::Armor] = std::make_shared<Gloves>(
        "Рукавицы Стража Врат", 2, 30, 20, 0, warStyle::Armor, coins{170});
    Market.equipmentShop[2][slotOfEquipment::Pants][warStyle::Armor] = std::make_shared<Pants>(
        "Поножи Непробиваемые", 2, 60, 38, 0, warStyle::Armor, coins{330});
    Market.equipmentShop[2][slotOfEquipment::Boots][warStyle::Armor] = std::make_shared<Boots>(
        "Ботинки Земли", 2, 40, 25, 0, warStyle::Armor, coins{230});

    // --- Стиль: ELITE (Необычайность, средние показатели) ---
    // Достоинства: урон, шанс оглушения | Средние: здоровье, армор, уворот, точность
    // Для экипировки - сбалансированные, но чуть выше среднего показатели.
    // Уровень 0
    Market.equipmentShop[0][slotOfEquipment::Helmet][warStyle::Elite] = std::make_shared<Helmet>(
        "Шлем Загадочного Путника", 0, 10, 5, 5, warStyle::Elite, coins{70});
    Market.equipmentShop[0][slotOfEquipment::Chestplate][warStyle::Elite] = std::make_shared<Chestplate>(
        "Мантия Странника Миров", 0, 15, 8, 8, warStyle::Elite, coins{90});
    Market.equipmentShop[0][slotOfEquipment::Gloves][warStyle::Elite] = std::make_shared<Gloves>(
        "Перчатки Тайного Знания", 0, 5, 3, 3, warStyle::Elite, coins{45});
    Market.equipmentShop[0][slotOfEquipment::Pants][warStyle::Elite] = std::make_shared<Pants>(
        "Штаны Искателя Приключений", 0, 12, 6, 6, warStyle::Elite, coins{80});
    Market.equipmentShop[0][slotOfEquipment::Boots][warStyle::Elite] = std::make_shared<Boots>(
        "Сапоги Сумерек", 0, 8, 4, 4, warStyle::Elite, coins{55});
    // Уровень 1
    Market.equipmentShop[1][slotOfEquipment::Helmet][warStyle::Elite] = std::make_shared<Helmet>(
        "Шлем Хранителя Неба", 1, 20, 10, 10, warStyle::Elite, coins{160});
    Market.equipmentShop[1][slotOfEquipment::Chestplate][warStyle::Elite] = std::make_shared<Chestplate>(
        "Доспех Забытых Героев", 1, 30, 15, 15, warStyle::Elite, coins{230});
    Market.equipmentShop[1][slotOfEquipment::Gloves][warStyle::Elite] = std::make_shared<Gloves>(
        "Наручи Избранного", 1, 10, 6, 6, warStyle::Elite, coins{110});
    Market.equipmentShop[1][slotOfEquipment::Pants][warStyle::Elite] = std::make_shared<Pants>(
        "Поножи Древних Тайн", 1, 25, 12, 12, warStyle::Elite, coins{200});
    Market.equipmentShop[1][slotOfEquipment::Boots][warStyle::Elite] = std::make_shared<Boots>(
        "Ботинки Путей Времени", 1, 15, 8, 8, warStyle::Elite, coins{130});
    // Уровень 2
    Market.equipmentShop[2][slotOfEquipment::Helmet][warStyle::Elite] = std::make_shared<Helmet>(
        "Шлем Оракула", 2, 30, 15, 15, warStyle::Elite, coins{350});
    Market.equipmentShop[2][slotOfEquipment::Chestplate][warStyle::Elite] = std::make_shared<Chestplate>(
        "Кираса Небесного Воителя", 2, 50, 25, 25, warStyle::Elite, coins{450});
    Market.equipmentShop[2][slotOfEquipment::Gloves][warStyle::Elite] = std::make_shared<Gloves>(
        "Перчатки Вселенского Разума", 2, 20, 10, 10, warStyle::Elite, coins{220});
    Market.equipmentShop[2][slotOfEquipment::Pants][warStyle::Elite] = std::make_shared<Pants>(
        "Поножи Бесконечного Познания", 2, 40, 20, 20, warStyle::Elite, coins{400});
    Market.equipmentShop[2][slotOfEquipment::Boots][warStyle::Elite] = std::make_shared<Boots>(
        "Сапоги Истины", 2, 25, 12, 12, warStyle::Elite, coins{280});


    // --- ОРУЖИЕ (УРОВНИ 0, 1, 2) ---

    // --- Стиль: DAMAGE (Axe, Glaive) ---
    // Достоинства: урон, шанс оглушения, армор | Недостатки: точность, уворот | Средние: здоровье
    // Для оружия: высокий урон, хороший шанс оглушения, низкая точность.
    // Уровень 0
    Market.weaponShop[0][slotOfWeapon::Axe][warStyle::Damage] = std::make_shared<weapon>(
        "Топор Мясника", 0, 20, 3, 5, slotOfWeapon::Axe, warStyle::Damage, coins{80});
    Market.weaponShop[0][slotOfWeapon::Glaive][warStyle::Damage] = std::make_shared<weapon>(
        "Глефа Разрушителя", 0, 25, 2, 7, slotOfWeapon::Glaive, warStyle::Damage, coins{100});
    // Уровень 1
    Market.weaponShop[1][slotOfWeapon::Axe][warStyle::Damage] = std::make_shared<weapon>(
        "Топор Казни", 1, 35, 5, 10, slotOfWeapon::Axe, warStyle::Damage, coins{180});
    Market.weaponShop[1][slotOfWeapon::Glaive][warStyle::Damage] = std::make_shared<weapon>(
        "Глефа Кровавой Луны", 1, 45, 4, 12, slotOfWeapon::Glaive, warStyle::Damage, coins{230});
    // Уровень 2
    Market.weaponShop[2][slotOfWeapon::Axe][warStyle::Damage] = std::make_shared<weapon>(
        "Топор Опустошения", 2, 50, 8, 15, slotOfWeapon::Axe, warStyle::Damage, coins{350});
    Market.weaponShop[2][slotOfWeapon::Glaive][warStyle::Damage] = std::make_shared<weapon>(
        "Глефа Вечного Раздора", 2, 65, 6, 20, slotOfWeapon::Glaive, warStyle::Damage, coins{450});

    // --- Стиль: DODGE (Epee, Blade) ---
    // Достоинства: уворот, урон, шанс оглушения | Недостатки: здоровье, броня | Средние: точность
    // Для оружия: средний урон, хорошая точность, низкий шанс оглушения.
    // Уровень 0
    Market.weaponShop[0][slotOfWeapon::Epee][warStyle::Dodge] = std::make_shared<weapon>(
        "Облегченная Шпага", 0, 15, 10, 0, slotOfWeapon::Epee, warStyle::Dodge, coins{85});
    Market.weaponShop[0][slotOfWeapon::Blade][warStyle::Dodge] = std::make_shared<weapon>(
        "Тонкий Клинок", 0, 12, 12, 0, slotOfWeapon::Blade, warStyle::Dodge, coins{95});
    // Уровень 1
    Market.weaponShop[1][slotOfWeapon::Epee][warStyle::Dodge] = std::make_shared<weapon>(
        "Шпага Скорости", 1, 25, 18, 0, slotOfWeapon::Epee, warStyle::Dodge, coins{190});
    Market.weaponShop[1][slotOfWeapon::Blade][warStyle::Dodge] = std::make_shared<weapon>(
        "Клинок Ветра", 1, 20, 20, 0, slotOfWeapon::Blade, warStyle::Dodge, coins{220});
    // Уровень 2
    Market.weaponShop[2][slotOfWeapon::Epee][warStyle::Dodge] = std::make_shared<weapon>(
        "Шпага Скрытности", 2, 40, 28, 0, slotOfWeapon::Epee, warStyle::Dodge, coins{380});
    Market.weaponShop[2][slotOfWeapon::Blade][warStyle::Dodge] = std::make_shared<weapon>(
        "Клинок Невидимки", 2, 35, 30, 0, slotOfWeapon::Blade, warStyle::Dodge, coins{420});

    // --- Стиль: ARMOR (Sword, Spear) ---
    // Достоинства: здоровье, армор, точность | Недостатки: уворот, шанс оглушения | Средние: урон
    // Для оружия: средний урон, высокая точность, низкий шанс оглушения.
    // Уровень 0
    Market.weaponShop[0][slotOfWeapon::Sword][warStyle::Armor] = std::make_shared<weapon>(
        "Меч Защитника", 0, 18, 8, 0, slotOfWeapon::Sword, warStyle::Armor, coins{90});
    Market.weaponShop[0][slotOfWeapon::Spear][warStyle::Armor] = std::make_shared<weapon>(
        "Копье Стража", 0, 16, 9, 0, slotOfWeapon::Spear, warStyle::Armor, coins{95});
    // Уровень 1
    Market.weaponShop[1][slotOfWeapon::Sword][warStyle::Armor] = std::make_shared<weapon>(
        "Рыцарский Меч", 1, 28, 15, 0, slotOfWeapon::Sword, warStyle::Armor, coins{200});
    Market.weaponShop[1][slotOfWeapon::Spear][warStyle::Armor] = std::make_shared<weapon>(
        "Копье Крепости", 1, 25, 16, 0, slotOfWeapon::Spear, warStyle::Armor, coins{210});
    // Уровень 2
    Market.weaponShop[2][slotOfWeapon::Sword][warStyle::Armor] = std::make_shared<weapon>(
        "Меч Королевской Гвардии", 2, 45, 25, 0, slotOfWeapon::Sword, warStyle::Armor, coins{400});
    Market.weaponShop[2][slotOfWeapon::Spear][warStyle::Armor] = std::make_shared<weapon>(
        "Копье Непоколебимости", 2, 40, 28, 0, slotOfWeapon::Spear, warStyle::Armor, coins{410});

    // --- Стиль: ELITE (Mace, Fork) ---
    // Достоинства: урон, шанс оглушения | Средние: здоровье, армор, уворот, точность
    // Для оружия: хороший баланс урона, точности и оглушения.
    // Уровень 0
    Market.weaponShop[0][slotOfWeapon::Mace][warStyle::Elite] = std::make_shared<weapon>(
        "Булава Таинства", 0, 18, 6, 3, slotOfWeapon::Mace, warStyle::Elite, coins{100});
    Market.weaponShop[0][slotOfWeapon::Fork][warStyle::Elite] = std::make_shared<weapon>(
        "Вилы Проклятых", 0, 22, 5, 4, slotOfWeapon::Fork, warStyle::Elite, coins{110});
    // Уровень 1
    Market.weaponShop[1][slotOfWeapon::Mace][warStyle::Elite] = std::make_shared<weapon>(
        "Булава Избранного", 1, 30, 10, 6, slotOfWeapon::Mace, warStyle::Elite, coins{250});
    Market.weaponShop[1][slotOfWeapon::Fork][warStyle::Elite] = std::make_shared<weapon>(
        "Трезубец Древних", 1, 38, 9, 8, slotOfWeapon::Fork, warStyle::Elite, coins{280});
    // Уровень 2
    Market.weaponShop[2][slotOfWeapon::Mace][warStyle::Elite] = std::make_shared<weapon>(
        "Булава Божественного Гнева", 2, 45, 15, 10, slotOfWeapon::Mace, warStyle::Elite, coins{500});
    Market.weaponShop[2][slotOfWeapon::Fork][warStyle::Elite] = std::make_shared<weapon>(
        "Вилы Апокалипсиса", 2, 55, 12, 14, slotOfWeapon::Fork, warStyle::Elite, coins{550});
}
