#ifndef LAB_2_GAME_OPPONENT_H
#define LAB_2_GAME_OPPONENT_H
#include <iostream>
#include "character.h"
class opponent : character {
public:
    opponent(std::string &,unsigned int,unsigned int, unsigned int, unsigned int,unsigned int,
    unsigned int, unsigned int);
    ~opponent()= default;

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &name);


private:
    std::string name;
    unsigned int level{};
public:
    unsigned int getLevel() const;

    void setLevel(unsigned int level);
};


#endif //LAB_2_GAME_OPPONENT_H
