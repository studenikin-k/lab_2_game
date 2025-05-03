//
// Created by basybemoog on 25.04.2025.
//

#ifndef LOCATION_H
#define LOCATION_H

#include "opponent.h"


class location{
public:
    [[nodiscard]] std::string getName() const;

    void setName(const std::string &name);

    explicit location(const std::string &name);



    ~location() = default;
private:
    std::string _name;


};



#endif //LOCATION_H
