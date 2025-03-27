#ifndef LAB_2_GAME_INVENTORY_H
#define LAB_2_GAME_INVENTORY_H
#include <iostream>

class inventory {

public:
    inventory() = default;
    ~inventory()= default;

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &name);

    [[nodiscard]] unsigned int getLevel() const;

    void setLevel(unsigned int level);
private:
    std::string name{};
    unsigned int level{};
};


#endif
