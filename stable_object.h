#pragma once
#include "map_entity.h"


class Stable_object : public Map_entity {
public:
    Stable_object(int i, int j, char type);
    bool is_checked() { return 0; }
    // void place(Map& map);
};