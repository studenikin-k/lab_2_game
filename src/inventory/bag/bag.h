#ifndef LAB_2_GAME_BAG_H
#define LAB_2_GAME_BAG_H
#include "../equipment/equipment.h"
#include "../weapon/weapon.h"
#include <vector>
#include <memory>
#include <algorithm>
#include "../potion/potion.h"
#include <unordered_map>

class bag {
public:
    bag() = default;

    void inputIntoBag(equipment *item);

    void inputIntoBag(weapon *gun);

    void inputIntoBag(potion *potion);

    void outputEquipmentFromBag(const std::string &name);

    void outputWeaponFromBag(const std::string &name);

    void outputPotionFromBag(const std::string &name);

    void showBag() const;

    std::vector<equipment *> bagEquipment;
    std::vector<weapon *> bagWeapon;
    std::vector<potion *> bagPotion;
private:

    template<typename T>
    void printCategory(const std::vector<T*>& vec, const std::string& title) const {
        std::cout << "\n=== " << title << " ===\n";
        if (vec.empty()) {
            std::cout << "  (пусто)\n\n";
            return;
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << "  " << (i + 1) << ") ";
            vec[i]->showInInventory();
        }
        std::cout << "\n";
    }
};



#endif //LAB_2_GAME_BAG_H
