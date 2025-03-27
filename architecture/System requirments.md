# System Requirements and Use Cases

## General System Reqruiments
Operating System
Ubuntu 24.04 LTS or better (64-bit)
or
Windows 7 or better

Compiler & Build Tools
any compiler that supports C++ (gcc, clang, cmake and other).

C++ Standard: C++20 or newer

Build System: make

---

## Hardware Requirements
CPU: Dual-core 1.5 GHz or higher

RAM: 512 MB minimum (4 GB recommended)

Terminal:

Supports UTF-8 encoding.

Minimum terminal size: 800x600 characters.

Supports ANSI escape codes for colors (e.g., gnome-terminal, konsole, xterm).

Input
Keyboard: Standard QWERTY keyboard with arrow keys.

Mouse: No needfull

---
## General Game Requirements

1. The game must support the behavior of the main character, taking into account the capabilities that have been defined in it.
2. Each player has the opportunity to decide how his main character will be played.
3. Battles between the main character and the opponent must take into account such characteristics as: health, armor, damage, accuracy, chance of stunning, chance of dodging.
4. The system must support saving and loading the state of the game.
5. The player must be able to start a new game.

---
# Use Cases:

## Use Case 1: Creating a New Game:

1. The player starts the game.
2.  Two teams, each consisting of three players, are created.
3. Each player is assigned a role and receives corresponding characteristics.
4. The game begins.


---
## Use Case 2: Saving the Game:

1. The player ends the game session.
2. The system saves the current state of the game, including the main character's inventory, location, and all characteristics of the main character.
3. The player can load the game later.


---

## Use Case 3: Battle Between Main character and opponent:

1. The main character enters a battle against an AI opponent.
2. The main character and opponent take turns attacking each other based on their stats and chances of making a critical hit, stunning, or dodging.
3. The battle continues until one of the opponents' health is depleted.

---
## Use Case 4: Exit the Game:

1. The player should be able to exit the game when in the main menu. 
2. Game data should be saved based on the player's choice.







