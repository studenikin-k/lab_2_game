#ifndef LAB_2_GAME_COINS_H
#define LAB_2_GAME_COINS_H
#include <iostream>
class coins{
public:

    [[nodiscard]] std::string  showMoney() const;
    [[nodiscard]] std::string  showSellPrice() const;


    [[nodiscard]] unsigned int getCopper() const;

    void setCopper(unsigned int copper);

    unsigned int copper; // валюта, которая будет иметь перерасчёт
    // 1 золото = 100 серебра , 1 серебра = 100 меди
};
#endif //LAB_2_GAME_COINS_H
