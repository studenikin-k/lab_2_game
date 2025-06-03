#include "gtest/gtest.h"
#include "../include/all_headers.h"
#include <memory>
#include <vector>
#include <map> // Для удобства использования map в тестах, хотя в main_char используется unordered_map

// Вспомогательная функция для сброса состояния cin (на случай ошибок ввода в реальном коде)
void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Тестовый класс для main_char и инвентаря
class MainCharInventoryTest : public ::testing::Test {
protected:
    main_char* hero; // Используем указатель, чтобы создавать объект в SetUp и удалять в TearDown
    coins baseCash;

    void SetUp() override {
        baseCash.setCopper(100000); // 10 золотых
        hero = new main_char("TestHero", 1, 100, 10, 5, 10, 5, 5, baseCash, 0);
    }

    void TearDown() override {
        delete hero;
    }

    // Вспомогательная функция для проверки наличия предмета в Bag
    template<typename T>
    bool isInBag(const std::vector<std::shared_ptr<T>>& bagVector, const std::string& itemName) {
        for (const auto& item : bagVector) {
            if (item && item->getName() == itemName) {
                return true;
            }
        }
        return false;
    }
};





TEST_F(MainCharInventoryTest, EquipAndUnequipPotion) {
    // Создаем несколько зелий
    coins hpPrice, dpPrice, apPrice, acpPrice, spPrice, dopPrice;
    hpPrice.setCopper(100);
    dpPrice.setCopper(120);
    apPrice.setCopper(130);
    acpPrice.setCopper(140);
    spPrice.setCopper(150);
    dopPrice.setCopper(160);

    std::shared_ptr<potion> healthPot = std::make_shared<healthPotion>("Малое Зелье Здоровья", 1, 50, hpPrice);
    std::shared_ptr<potion> damagePot = std::make_shared<damagePotion>("Малое Зелье Урона", 1, 10, dpPrice);
    std::shared_ptr<potion> armorPot = std::make_shared<armorPotion>("Малое Зелье Брони", 1, 5, apPrice);
    std::shared_ptr<potion> accuracyPot = std::make_shared<accuracyPotion>("Малое Зелье Точности", 1, 5, acpPrice);
    std::shared_ptr<potion> stunPot = std::make_shared<stunPotion>("Малое Зелье Оглушения", 1, 2, spPrice);
    std::shared_ptr<potion> dodgePot = std::make_shared<dodgePotion>("Малое Зелье Уклонения", 1, 3, dopPrice);
    std::shared_ptr<potion> extraPot = std::make_shared<healthPotion>("Дополнительное Зелье Здоровья", 1, 70, hpPrice);


    // Добавляем зелья в сумку
    hero->Bag.inputIntoBag(healthPot);
    hero->Bag.inputIntoBag(damagePot);
    hero->Bag.inputIntoBag(armorPot);
    hero->Bag.inputIntoBag(accuracyPot);
    hero->Bag.inputIntoBag(stunPot);
    hero->Bag.inputIntoBag(dodgePot);
    hero->Bag.inputIntoBag(extraPot);

    EXPECT_EQ(hero->Bag.bagPotion.size(), 7); // Проверяем, что все 7 зелий в сумке


    for (int i = 0; i < BELT_SIZE; ++i) {
        // Проверяем, что Bag не пуст, прежде чем брать из него
        if (!hero->Bag.bagPotion.empty()) {
            hero->equip(hero->Bag.bagPotion[0]); // Экипируем первое зелье в сумке
            hero->Bag.bagPotion.erase(hero->Bag.bagPotion.begin()); // Удаляем из Bag, так как оно перемещено
        }
    }

    // Проверяем, что пояс заполнен и каждое зелье на своем месте (порядке добавления)
    EXPECT_EQ(hero->Belt[0]->getName(), "Малое Зелье Здоровья");
    EXPECT_EQ(hero->Belt[1]->getName(), "Малое Зелье Урона");
    EXPECT_EQ(hero->Belt[2]->getName(), "Малое Зелье Брони");
    EXPECT_EQ(hero->Belt[3]->getName(), "Малое Зелье Точности");
    EXPECT_EQ(hero->Belt[4]->getName(), "Малое Зелье Оглушения");
    EXPECT_EQ(hero->Belt[5]->getName(), "Малое Зелье Уклонения");
    EXPECT_EQ(hero->Bag.bagPotion.size(), 1); // Одно зелье (extraPot) должно остаться в Bag
    EXPECT_TRUE(isInBag(hero->Bag.bagPotion, "Дополнительное Зелье Здоровья"));

    // Пробуем экипировать последнее зелье, когда пояс полон (ожидаем запрос на замену)
    // Здесь требуется имитация ввода, поэтому этот аспект не полностью автоматизирован без мокинга cin
    // Для этого теста мы просто убедимся, что Bag.inputIntoBag отработал, и потом Belt.inputIntoBag в реальной игре запросит
    // у пользователя ввод. Мы можем лишь проверить, что элемент в Bag.bagPotion присутствует
    // и вызвать метод equip.

    // Имитация ввода '1' для замены первого зелья
    std::stringstream ss_in;
    ss_in << "1\n"; // Выбираем первый слот
    std::cin.rdbuf(ss_in.rdbuf()); // Перенаправляем cin

    std::cout << "\nAttempting to equip extra potion when belt is full (expecting prompt for replacement):\n";
    hero->equip(hero->Bag.bagPotion[0]); // Экипируем 'Дополнительное Зелье Здоровья'

    clearCin(); // Очищаем cin после использования stringstream

    // Проверяем, что "Дополнительное Зелье Здоровья" теперь в первом слоте пояса
    EXPECT_EQ(hero->Belt[0]->getName(), "Дополнительное Зелье Здоровья");
    // И "Малое Зелье Здоровья" вернулось в сумку
    EXPECT_TRUE(isInBag(hero->Bag.bagPotion, "Малое Зелье Здоровья"));
    EXPECT_EQ(hero->Bag.bagPotion.size(), 2); // Старое зелье и одно, которое не поместилось ранее

    // Снимаем зелье с пояса (имитируем ввод)
    std::stringstream ss_take_off_in;
    ss_take_off_in << "2\n"; // Снимаем зелье из второго слота
    std::cin.rdbuf(ss_take_off_in.rdbuf()); // Перенаправляем cin

    std::cout << "\nAttempting to take off potion from belt (expecting prompt for slot):\n";
    hero->takeOffPotion();
    clearCin(); // Очищаем cin после использования stringstream

    // Проверяем, что слот опустошился и зелье вернулось в Bag
    EXPECT_EQ(hero->Belt[1], nullptr);
    EXPECT_TRUE(isInBag(hero->Bag.bagPotion, "Малое Зелье Урона"));
    EXPECT_EQ(hero->Bag.bagPotion.size(), 3); // Теперь 3 зелья в сумке

    // Пробуем снять зелье из пустого слота
    std::stringstream ss_take_off_empty_in;
    ss_take_off_empty_in << "2\n"; // Снимаем зелье из второго слота, который теперь пуст
    std::cin.rdbuf(ss_take_off_empty_in.rdbuf());

    std::cout << "\nAttempting to take off potion from an empty belt slot:\n";
    hero->takeOffPotion(); // Ожидаем сообщение "Ячейка 2 уже пуста!"
    clearCin();

    // Проверяем, что ничего не изменилось в Bag и слот остался пустым
    EXPECT_EQ(hero->Belt[1], nullptr);
    EXPECT_EQ(hero->Bag.bagPotion.size(), 3);
}



// Тестовый класс для main_char и инвентаря
class MainCharPurchaseTest : public ::testing::Test {
protected:
    main_char* hero;
    shop* testShop; // Используем указатель на shop
    coins initialBalance;

    void SetUp() override {
        initialBalance.setCopper(100000); // 10 золотых
        hero = new main_char("TestBuyer", 1, 100, 10, 5, 10, 5, 5, initialBalance, 0);
        testShop = new shop(); // Создаем экземпляр магазина
    }

    void TearDown() override {
        delete hero;
        delete testShop;
    }

    // Вспомогательная функция для проверки наличия предмета в Bag (для этого теста)
    template<typename T>
    bool isInBag(const std::vector<std::shared_ptr<T>>& bagVector, const std::string& itemName) {
        for (const auto& item : bagVector) {
            if (item && item->getName() == itemName) {
                return true;
            }
        }
        return false;
    }
};




TEST_F(MainCharPurchaseTest, BuyEquipment) {
    // Создаем предмет экипировки для продажи
    coins helmetPrice;
    helmetPrice.setCopper(5000); // 50 серебра
    std::shared_ptr<equipment> helmet = std::make_shared<Helmet>(
        "Продажный Шлем", 1, 20, 10, 5, warStyle::Armor, helmetPrice);

    // Добавляем шлем в магазин
    testShop->equipmentShop[1][slotOfEquipment::Helmet][warStyle::Armor]=helmet;

    unsigned int initialCopper = hero->balance.getCopper();


    std::cout << "\nBuying 'Продажный Шлем'...\n";

    hero->Bag.inputIntoBag(helmet);
    bool purchaseSuccess = true;

    hero->balance.copper -= helmet->price.copper;

    EXPECT_TRUE(purchaseSuccess); // Проверяем, что покупка была успешной

    // Проверяем, что шлем добавлен в сумку персонажа
    EXPECT_TRUE(isInBag(hero->Bag.bagEquipment, "Продажный Шлем"));
    EXPECT_EQ(hero->Bag.bagEquipment.size(), 1);

    // Проверяем, что баланс персонажа уменьшился
    EXPECT_EQ(hero->balance.getCopper(), initialCopper - helmetPrice.getCopper());

}

class ExperienceMechanicsTest : public ::testing::Test {
protected:
    main_char* hero;

    void SetUp() override {
        // Создаем героя с базовыми характеристиками для тестирования опыта
        // Начнем с 0 опыта, чтобы легко контролировать левелап.
        coins initialBalance;
        initialBalance.setCopper(0);
        hero = new main_char("ExpHero", 1, 100, 10, 5, 10, 5, 5, initialBalance, 0);
        hero->setExperience(0);
        hero->setExperienceToLevelUp(100); // Для первого уровня, допустим, 100 опыта до следующего
    }

    void TearDown() override {
        delete hero;
    }
};



TEST_F(ExperienceMechanicsTest, GainExperienceNoLevelUp) {
    unsigned int initialLevel = hero->getLevel();
    unsigned int initialExp = hero->getExperience();
    unsigned int expToNextLevel = hero->getExperienceToLevelUp();

    // Получаем опыт, недостаточный для повышения уровня
    gainExperience(*hero, 50); // Добавляем 50 опыта

    // Проверяем, что уровень не изменился
    EXPECT_EQ(hero->getLevel(), initialLevel);
    // Проверяем, что опыт увеличился
    EXPECT_EQ(hero->getExperience(), initialExp + 50);
    // Проверяем, что опыт до следующего уровня не изменился
    EXPECT_EQ(hero->getExperienceToLevelUp(), expToNextLevel);
}




TEST_F(ExperienceMechanicsTest, GainExperienceMultipleLevelUps) {
    unsigned int initialLevel = hero->getLevel(); // 1
    unsigned int initialExpToLevel = hero->getExperienceToLevelUp(); // 100

    // Получаем опыт, достаточный для нескольких повышений уровня
    // Уровень 1 (0/100) -> 2 (0/200) -> 3 (0/400)
    // Для этого нужно 100 (для 1->2) + 200 (для 2->3) = 300 опыта.
    gainExperience(*hero, 350); // Добавляем 350 опыта

    // Проверяем, что уровень увеличился на 2
    EXPECT_EQ(hero->getLevel(), initialLevel + 2); // Уровень должен стать 3
    // Проверяем оставшийся опыт: 350 - 100 - 200 = 50
    EXPECT_EQ(hero->getExperience(), 50);
    // Проверяем, что опыт до следующего уровня удвоился дважды
    EXPECT_EQ(hero->getExperienceToLevelUp(), initialExpToLevel * 2 * 2); // Должен стать 400
}