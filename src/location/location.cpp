#include "../../include/all_headers.h"

location::location(const std::string &name)
        : _name(name) {
}


std::string location::getName() const {
    return _name;
}

void location::setName(const std::string &name) {
    this->_name = name;
}
