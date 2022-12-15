#pragma once
#include "fighter.h"

class Vampire : public Fighter {
public:
    Vampire(int i, int j, char type = 'v');
    void move(int n);       // n-> possible movements
    //void attack(WereWolves& ememy);
};
