# Test Report 

## General Information

This report describes specific test scenarios aimed at verifying inventory mechanics (potion equipping), purchase system (equipment), and experience progression (gaining experience without leveling up and with multiple level-ups). The tests are written using the **Google Test** framework.

---

## Test: Equipping and Unequipping Potions (`EquipAndUnequipPotion`)

* **Test Goal**: To verify the functionality of equipping potions to the character's belt (`Belt`) and their subsequent un-equipping, including scenarios of belt filling and potion replacement.
* **Test Scenario**:
    1.  Initialize a `main_char` and create a set of various potions.
    2.  Add all created potions to the character's bag (`hero->Bag.bagPotion`).
    3.  Verify the initial number of potions in the bag.
    4.  Equip potions from the bag to the belt (`hero->Belt`) in a loop until it's full (`BELT_SIZE`). Each equipped potion is removed from the bag.
    5.  Verification:
        * That all 6 belt slots are filled with the expected potions in the correct order.
        * That only one "extra" potion (`extraPot`) remains in the bag.
    6.  Simulate user input (`"1\n"`) to replace the potion in the first belt slot with the "extra" potion from the bag.
    7.  Verification:
        * That "Дополнительное Зелье Здоровья" (Extra Health Potion) is now in the first belt slot.
        * That "Малое Зелье Здоровья" (Small Health Potion, which was replaced) returned to the bag.
        * Verify the correct bag size.
    8.  Simulate user input (`"2\n"`) to unequip a potion from the second belt slot.
    9.  Verification:
        * That the second belt slot became `nullptr` (empty).
        * That the unequipped "Малое Зелье Урона" (Small Damage Potion) returned to the bag.
        * Verify the correct bag size.
    10. Simulate user input (`"2\n"`) to attempt unequipping a potion from the now empty second belt slot.
    11. Verification:
        * That the slot remained empty.
        * That the number of potions in the bag did not change.
* **Expected Result**: The potion equipping and unequipping mechanics should correctly manage the belt and bag contents, and adequately handle scenarios of filling/replacement and unequipping from empty slots, including simulated user input.

---

## Test: Equipment Purchase (`BuyEquipment`)

* **Test Goal**: To verify the basic logic of equipment purchase, including adding the item to inventory and deducting funds, without considering insufficient funds checks (as this aspect was removed from the provided snippet).
* **Test Scenario**:
    1.  Initialize a `main_char` with sufficient balance and a `shop`.
    2.  Create an equipment item ("Продажный Шлем" - Sellable Helmet) with a specific price.
    3.  Add this helmet to the shop's presumed inventory (`testShop->equipmentShop`).
    4.  Record the hero's initial copper balance.
    5.  Manually add the helmet to the hero's bag (`hero->Bag.inputIntoBag`) and manually deduct the cost from the hero's balance. (***Note:*** *In the original test, this logic should have been encapsulated within the shop's purchase method `testShop->buyItem_Equipment(*hero, 0)`, which would itself perform these actions and return `true`/`false`. The current test implementation bypasses this encapsulation by directly manipulating the hero's state.*)
    6.  Manually set `purchaseSuccess = true`.
    7.  Verification:
        * That `purchaseSuccess` is `true`.
        * That "Продажный Шлем" (Sellable Helmet) is present in the hero's bag (`hero->Bag.bagEquipment`).
        * That the number of items in the bag is 1.
        * That the hero's copper balance decreased exactly by the helmet's price.
* **Expected Result**: The item should be added to the bag, and the cost correctly deducted from the hero's balance. (The limitations of this test are that it does not verify the decision-making logic of the shop's purchase method, but only the final state after a "successful" purchase).

---

## Test: Gaining Experience without Leveling Up (`GainExperienceNoLevelUp`)

* **Test Goal**: To ensure that the `gainExperience` function correctly processes experience gain when the amount is insufficient to reach the next level.
* **Test Scenario**:
    1.  Initialize a `main_char` with an initial level of 1, 0 experience, and an `experienceToLevelUp` threshold of 100.
    2.  Call `gainExperience(*hero, 50)` to add 50 experience.
    3.  Verification:
        * That the character's level remained the same (1).
        * That the character's current experience increased to 50.
        * That the `experienceToLevelUp` threshold remained 100.
* **Expected Result**: Only the character's current experience should be updated; the level and next level threshold should remain unchanged.

---

## Test: Gaining Experience with Multiple Level Ups (`GainExperienceMultipleLevelUps`)

* **Test Goal**: To verify the `gainExperience` function in a scenario where the gained experience is sufficient to level up more than once.
* **Test Scenario**:
    1.  Initialize a `main_char` with an initial level of 1, 0 experience, and an `experienceToLevelUp` threshold of 100.
    2.  Call `gainExperience(*hero, 350)` to add a large amount of experience.
        * *Expected Process*:
            * 100 experience for level 1->2 (remaining 250). `expToLevelUp` will become 200.
            * 200 experience for level 2->3 (remaining 50). `expToLevelUp` will become 400.
    3.  Verification:
        * That the character's level increased by 2 (became 3).
        * That the character's remaining experience is 50.
        * That the `experienceToLevelUp` threshold updated twice (became 400).
* **Expected Result**: The function should correctly handle multiple level-ups, update the character's level, reset current experience, and appropriately increase the experience threshold for the next level.