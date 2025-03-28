
### **Main Classes and Their Relationships**

#### **1. Class: `location`**

- **Attributes:**
    
    - `std::string name` — the name of the location.
        
- **Relationships:**
    
    - Parent class for `peaceful_location` and `battle_location`.
        

#### **2. Class: `peaceful_location` (inherits from `location`)**

- **Attributes:**
    
    - `shop Shop` — a shop available in this location.
        
    - `std::vector<std::unique_ptr<location>> connectedLocations` — a list of connected locations.
        

#### **3. Class: `battle_location` (inherits from `location`)**

- **Attributes:**
    
    - `std::array<std::unique_ptr<opponent>, N> opponents` — an array of opponents in this location.
        
    - `std::vector<std::unique_ptr<location>> connectedLocations` — a list of connected locations.
        

#### **4. Class: `Map`**

- **Attributes:**
    
    - `std::array<std::unique_ptr<location>, 2> mapOfLocations` — an array of available locations on the map.
        

---

### **Shop and Items**

#### **5. Class: `shop`**

- **Attributes:**
    
    - `std::unordered_map<slotOfEquipment, std::unique_ptr<equipment>> equipmentShop` — a map of equipment available for purchase.
        
    - `std::unordered_map<slotOfWeapon, std::unique_ptr<weapon>> weaponShop` — a map of weapons available in the shop.
        
    - `std::array<std::unordered_map<std::string, std::unique_ptr<potion>>, S> potionShop` — a map of potions available for purchase.
        

---

### **Game Character and Attributes**

#### **6. Class: `Character`**

- **Attributes:**
    
    - `unsigned int level` — character level.
        
    - `unsigned int health` — health points.
        
    - `unsigned int damage` — damage value.
        
    - `unsigned int armor` — armor value.
        
    - `unsigned int accuracy` — accuracy level.
        
    - `unsigned int stun` — stun effect duration.
        

#### **7. Class: `main_char` (inherits from `Character`)**

- **Attributes:**
    
    - `std::string name` — main character's name.
        
    - `std::unordered_map<slotOfEquipment, std::unique_ptr<equipment>> Equipment` — map of equipped items.
        
    - `std::unordered_map<std::string, std::unique_ptr<potion>> Potions` — map of potions owned.
        
    - `Bag bag` — inventory bag.
        
    - `std::unique_ptr<weapon> gun` — character's weapon.
        
    - `Coins money` — character's money.
        

#### **8. Class: `opponent`**

- **Attributes:**
    
    - `std::string name` — opponent's name.
        

---

### **Inventory and Equipment**

#### **9. Class: `Bag`**

- **Attributes:**
    
    - `std::vector<std::unique_ptr<equipment>> bagEquipment` — stored equipment in the bag.
        
    - `std::vector<std::unique_ptr<weapon>> bagWeapon` — stored weapons in the bag.
        
    - `std::vector<std::unique_ptr<potion>> bagPotion` — stored potions in the bag.
        

#### **10. Class: `Inventory`**

- **Attributes:**
    
    - `std::string name` — inventory item name.
        
    - `unsigned int level` — item level.
        

#### **11. Class: `Equipment`**

- **Attributes:**
    
    - `unsigned int damage` — damage value.
        
    - `unsigned int accuracy` — accuracy level.
        
    - `unsigned int stun` — stun effect duration.
        
    - `slotOfEquipment slot` — equipment slot.
        

##### **Derived Classes (inherit from `Equipment`):**

- `Helmet`
    
- `Chestplate`
    
- `Gloves`
    
- `Pants`
    
- `Boots`
    

#### **12. Enum class: `slotOfEquipment`**

- **Possible values:**
    
    - `Helmet`
        
    - `Chestplate`
        
    - `Gloves`
        
    - `Pants`
        
    - `Boots`
        

#### **13. Class: `Weapon`**

- **Attributes:**
    
    - `unsigned int damage` — weapon damage.
        
    - `unsigned int accuracy` — weapon accuracy.
        
    - `unsigned int stun` — weapon stun effect.
        
    - `slotOfWeapon slot` — weapon slot.
        

#### **14. Enum class: `slotOfWeapon`**

- **Possible values:**
    
    - `Axe`
        
    - `Mace`
        
    - `Sword`
        
    - `Blade`
        
    - `Epee`
        
    - `Fork`
        
    - `Glave`
        
    - `Spear`
        

---

### **Potions and Effects**

#### **15. Class: `Potion`**

- **Attributes:**
    
    - `std::string name` — potion name.
        
    - `unsigned int level` — potion level.
        

##### **Derived Classes (inherit from `Potion`):**

- `healthPotion` — restores health (`unsigned int health`).
    
- `armorPotion` — increases armor (`unsigned int armor`).
    
- `accuracyPotion` — increases accuracy (`unsigned int accuracy`).
    
- `stunPotion` — stuns the enemy (`unsigned int stun`).
    
- `damagePotion` — increases damage (`unsigned int damage`).
    
- `dodgePotion` — increases dodge chance (`unsigned int dodge`).
    

#### **16. Enum class: `slotOfPotion`**

- **Possible values:**
    
    - `Health`
        
    - `Armor`
        
    - `Accuracy`
        
    - `Stun`
        
    - `Damage`
        
    - `Dodge`
        

---

### **Final Summary**

This class diagram represents an RPG game system, including characters, inventory, shops, weapons, and potions. The main character (`main_char`) can move around the map (`Map`), visit peaceful locations (`peaceful_location`), and battle in combat areas (`battle_location`). The character can purchase items in the shop (`shop`) and fight against opponents (`opponent`). The inventory system stores equipment (`Equipment`), weapons (`Weapon`), and potions (`Potion`). Various character attributes, such as damage, armor, accuracy, and stun effects, influence battle outcomes.
