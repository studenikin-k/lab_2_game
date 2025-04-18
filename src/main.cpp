#include <iostream>
#include "./equipment/equipment.h"
#include "./weapon/weapon.h"
#include "./characters/main_char.h"
#include "shop/shop.h"
#include "bag/bag.h"
#include "potion/potion.h"



int main (){

    coins cash(2222);

    main_char character("Hero",1,10,15,12,11,2,3,cash);

    equipment helmet("Shlem",1,11,1,2,slotOfEquipment::Helmet,warStyle::Damage,{123});

    std::unique_ptr<equipment> shlem = std::make_unique<equipment>(helmet);

    weapon gun("Gun",11,2,2,3,slotOfWeapon::Blade,warStyle::Damage,{123123});

    std::unique_ptr<weapon> oruzhie = std::make_unique<weapon>(gun);

    shop magaz;

    magaz.equipmentShop[1][slotOfEquipment::Helmet][warStyle::Damage]= std::move(shlem);
    magaz.weaponShop[1][slotOfWeapon::Blade][warStyle::Damage]= std::move(oruzhie);

    magaz.showContents();

}