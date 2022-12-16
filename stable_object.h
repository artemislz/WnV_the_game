#pragma once
#include "map_entity.h"
#include <iostream>

class Stable_object : public Map_entity {
public:
    Stable_object(int i, int j, char type);
    inline bool is_checked() { return true; }
};