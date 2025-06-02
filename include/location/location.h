#ifndef LOCATION_H
#define LOCATION_H

#include "../all_headers.h"


class location {
public:
    [[nodiscard]] std::string getName() const;

    void setName(const std::string &name);

    explicit location(const std::string &name);


    virtual ~location() = default;

private:
    std::string _name;
};


#endif //LOCATION_H
