#ifndef LAB_2_GAME_CHARACTER_H
#define LAB_2_GAME_CHARACTER_H

#include "iostream"

class character {
public:
    character();

    ~character() = default;



    [[nodiscard]] unsigned int getHealth() const;

    void setHealth(unsigned int health);

    [[nodiscard]] unsigned int getDamage() const;

    void setDamage(unsigned int damage);

    [[nodiscard]] unsigned int getArmor() const;

    void setArmor(unsigned int armor);

    [[nodiscard]] unsigned int getAccuracy() const;

    void setAccuracy(unsigned int accuracy);

    [[nodiscard]] unsigned int getStun() const;

    void setStun(unsigned int stun);

    [[nodiscard]] unsigned int getDodge() const;

    void setDodge(unsigned int dodge);


protected:

    unsigned int health{};
    unsigned int damage{};
    unsigned int armor{};
    unsigned int accuracy{};
    unsigned int stun{};
    unsigned int dodge{};

};


#endif
