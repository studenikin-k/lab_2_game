
## 1. Unit tests:

Testing individual components such as: Main character, opponent, currency, briefcase, equipment (outfit), weapons, potions, shop, location, quests, combat.

____

## 2. Testing strategy:

All tests will be conducted using our main character, since all the connections will go through him.

___

## 3. Player creation testing: 

Make sure that the player object is created correctly, all required parameters are transferred correctly, the inventory will be empty, the balance will be zero, the equipment will contain simple items that give minimal characteristics, the same with weapons and potions (only presence, without use).

___

## 4. Player action testing: 

Check the ability of the character to interact with the inventory, equipment and weapons and potions (the briefcase will also be checked at the same time for correct operation) for adding and subtracting characteristics (for weapons and equipment). Output of equipment with indication of characteristics (also with weapons and potions).
Next will be a check for interaction of the main character with the store (at the same time the store will be checked for correct operation (example: put some specific item in the cell of each type of item, and try to buy them specifically)), in addition, the correct operation of the currency in the store will be checked (as an example, an example with an item that can be bought will be implemented, and an example for which the character will have an insufficient balance).

---
## 5.Check the ability to move around locations:

The main character will be offered the opportunity to choose where he will move, each location will offer the opportunity to move to other locations. In peaceful locations, it will be necessary to check the ability to open a store, in combat locations it will be necessary to check that it is possible to start a fight with an opponent.
___
## 6. Check the mechanics of the fight: 

It will be necessary to check that the opponent's data was loaded correctly, then it will be necessary to check the start of the fight: The main character will always attack first. Check the attack of the main character and the opponent taking into account the characteristics:
	1. *If the main character (opponent) attacked and hit the opponent (main character), then he receives damage equal to his personal damage characteristics + weapon damage with a possible deviation of +-10% of the total damage.
	2. If the accuracy of the main character (opponent) is lower than the dodge chance of the opponent (main character), then the opponent will dodge and will not receive damage.
	3. If the main character (opponent) has a stun chance, then the opponent (main character) receives a debuff and misses one turn without the ability to attack
	4. If the health of the main character (opponent) has reached zero, then the battle ends in defeat (victory).

