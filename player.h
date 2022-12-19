#pragma once
#include <iostream>
#include "global.h"
class map;

class player {
private:
    char team;      // W -> Werewolves  V -> Vampires
    int input;      // key code of the key pressed
public:
    player(const char& team);
    inline char get_team()const { return team; }
    void set_input();
    inline int get_input()const { return input;};
};