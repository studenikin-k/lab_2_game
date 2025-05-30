
## General description:

This system is a game with the ability to move around the place, fear, trade and complete tasks.
The main character has his own equipment, weapons, potions, which can be built in his own fighting style. All this can be bought in the store
The game supports saving and loading the game state, as well as starting a new game.

---
## Key components of the system:

**Main_char** - a class that is the entry point to the game.
**Combat** - a class that manages the battle between two teams.
**Gameplay** - a class that manages the state of the game, including saving, loading and starting (exiting) the game.
**Character** - an abstract class that includes the general characteristics of heroes and heroes.
**Equipment** - an abstract class for all equipment, combining their general characteristics.
**Weapon** - a class for weapons.
**Potion** - an abstract class of potions.
**Location** - an abstract class for locations, making up a map of movements.
**Shop**-class that will be placed in locations, giving the opportunity to purchase the missing items necessary for the main character.
**Bag** - a class that allows you to store items received by the main character by type: weapons, equipment, potions.

---
## Game mechanics:

The player is given the opportunity to choose a team of 3 people from the proposed roles. Another will be formed to connect the team to him. The task is to defeat the other team.
The player has the opportunity to complete quests in locations that can be moved. Also, in world locations, it will be possible to use the store and there will be no opponents, in the same combat locations.

When the Game begins, the player is given the opportunity to choose what to do with his character: he can assemble it in one of four combat styles (damage, dodge, armor and elite). Its main purpose: to complete quests and study the exploration of locations, pumping the character, battles.