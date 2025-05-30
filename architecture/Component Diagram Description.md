### 1. Component: Inventory:

**Functions:**  
- Stores items: weapons, equipment, potions.  
- Interacts with the Shop: receives purchased items.  

**Interactions:**  
- With the **Shop**: receives items after purchase.  
- With the **Main character**: provides access to items for combat or movement.  

---

## 2. Component: Shop:  

**Functions:**  
- Buying and selling goods (weapons, equipment, potions).  
- Calculating item prices.  

**Interactions:**  
- With the **Inventory**: transfers purchased items.  
- With the **Main character**: via interaction interface (player selects items).  

---

## 3. Component: Main character:  

**Attributes:**  
- Level, health, damage, accuracy, dodge, stun chance.  
- Inventory, money, equipment, weapons, potion belt.  

**Functions:**  
- Fighting opponents.  
- Buying/selling items in the Shop.  
- Moving between Locations.  

**Interactions:**  
- With **Inventory**: manages items.  
- With **Shop**: trading.  
- With **Locations**: navigation.  
- With **Combat**: initiates and participates in battles.  

---

## 4. Component: Locations:

**Types:**  
- **Peaceful**: guaranteed Shop access, no enemies.  
- **Combat**: contains Opponents, no Shop.  

**Functions:**  
- Enables movement between zones.  
- Defines interaction types (trade/combat).  

**Interactions:**  
- With **Main character**: transitioning between locations.  
- With **Opponents**: placement in combat zones.  

---

## 5. Component: Gameplay:  

**Functions:**  
- Manages game state: starting, ending.  
- Coordinates mechanics: combat, movement, trade.  
- Switches states (e.g., exploration to combat).  

**Interactions:**  
- With **Main character**: controls character actions.  
- With **Combat**: starts and ends battles.  
- With **Locations**: loads and switches zones.  

---

## 6. Component: Combat:

**Functions:**  
- Handles battle mechanics: turn order, damage calculation, critical hits, dodge, stun.  
- Calculates victory rewards (money).  

**Interactions:**  
- With **Main character**: uses attributes for damage calculation.  
- With **Opponent**: manages AI actions.  
- With **Locations**: determines current battle zone.  

---

## 7. Component: Opponent:

**Functions:**  
- AI with simple attack/defense algorithms.  
- Participates in battles on combat locations.  

**Interactions:**  
- With **Combat**: provides data for action calculations.  
- With **Locations**: bound to combat zones.  

---

## Component Relationships:  

1. **Main character ↔ Inventory ↔ Shop**  
   - Buying/selling items via Inventory.  
1. **Main character ↔ Locations ↔ Opponent**  
   - Navigating zones and encountering enemies.  
1. **Gameplay → Main character → Combat → Opponent**  
   - Controlling combat through the Main Hero.  
4. **Locations → Shop**  
   - Shop availability limited to peaceful zones.  
1. **Combat → Main character**  
   - Victory rewards (money) affect the Main Hero’s state.  

The diagram illustrates a system where component interactions revolve around the player-controlled Main character. Locations and Gameplay structure the game world, while Combat and Shop implement core mechanics.