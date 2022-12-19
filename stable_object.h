#pragma once
#include "map_entity.h"
#include <iostream>

class stable_object : public map_entity {
public:
    stable_object(const int& i, const int& j, const char& type);
    bool is_checked() { return true; }      // werewolves and vampires shouldn't interact with it          
    virtual ~stable_object() = default ;    // virtual destructor because it's a derived class
};