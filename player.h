#pragma once

class Map;

class Player {
private:
    char team;      // W -> Werewolves  V -> Vampires
    int input;      // number of the charcter-key pressed
public:
    Player(char team);
    inline char get_team()const { return team; }
    friend class Map;  
    void set_input();
    inline char get_input()const { return input;};
};