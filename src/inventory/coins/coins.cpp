#include "coins.h"
#include "iostream"

std::string coins::showMoney() const {
    unsigned int gold = copper / 10000;
    unsigned int remaining = copper % 10000;
    unsigned int silver = remaining / 100;
    unsigned int copper_remaining = remaining % 100;

    return "Золото: " + std::to_string(gold) +
           " Серебро: " + std::to_string(silver) +
           " Бронза: " + std::to_string(copper_remaining) + "\n";
}


std::string coins::showSellPrice() const {
    unsigned int total_copper = copper / 2;
    unsigned int gold = total_copper / 10000;
    unsigned int remaining = total_copper % 10000;
    unsigned int silver = remaining / 100;
    unsigned int copper_remaining = remaining % 100;

    return "Золото: " + std::to_string(gold) +
           " Серебро: " + std::to_string(silver) +
           " Бронза: " + std::to_string(copper_remaining) + "\n";
}


unsigned int coins::getCopper() const {
    return copper;
}

void coins::setCopper(unsigned int _copper) {
    coins::copper = _copper;
}
