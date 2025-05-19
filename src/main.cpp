#include <iostream>
#include "./equipment/equipment.h"
#include "./weapon/weapon.h"
#include "./characters/main_char/main_char.h"
#include "shop/shop.h"
#include "bag/bag.h"
#include "potion/potion.h"
#include "characters/opponent/opponent.h"
#include "location/map/map.h"


int main() {
    coins cash(2323213321222);

    main_char character("Hero", 1, 10, 15, 12, 11, 2, 3, cash);

    Helmet elmet("Shlem", 1, 11, 1, 2, warStyle::Damage, {123});


    std::shared_ptr<Helmet> shlem = std::make_shared<Helmet>(elmet);

    character.equip(shlem);

    weapon gun("Gun", 11, 2, 2, 3, slotOfWeapon::Blade, warStyle::Damage, {123123});

    std::shared_ptr<weapon> oruzhie = std::make_shared<weapon>(gun);


    shop magaz;

    magaz.equipmentShop[1][slotOfEquipment::Helmet][warStyle::Damage] = shlem;
    magaz.weaponShop[1][slotOfWeapon::Blade][warStyle::Damage] = oruzhie;


    magaz.showContents(character);

    character.showBag();

    character.showGear();

    map Road{};

    Road.startTravel(0);

    /* character.Bag.showBag();

     opponent Vrag("Vrag",1,2,3,4,5,6,7);

     Vrag.showInfo();

     map Road{};

     Road.startTravel(0); */
}
