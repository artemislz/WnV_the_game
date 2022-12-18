#pragma once
#include "map_entity.h"
#include <iostream>

class stable_object : public map_entity {
public:
    stable_object(const int& i, const int& j, const char& type);
    bool is_checked() { return true; }
    virtual ~stable_object() { std::cout << "stable"; };
};