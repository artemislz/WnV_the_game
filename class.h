#pragma once
#include "globals.h"
#include <vector>

class Entity {            //<<Fighters,Avatar
protected:
    int x;      // position
    int y;
public:
    Entity(int x, int y);
    inline int get_x() { return x; }
    inline int get_y() { return y; }
    inline void move_up() { x--; }
    inline void move_down() { x++; }
    inline void move_right() { y++; }
    inline void move_left() { y--; }
    //virtual void move() = 0;    // pure virtual function beacuse every entity moves diffrently 
};

class Fighter : public Entity {
protected:
    int health;         // paradoxh: 10
    int power;          // random [1,3]
    int defence;        // random [1,2]
    int heal;           // random [0,2]
public:
    void set_values();
    //virtual void attack() = 0;       //?????
    Fighter(int x, int y);
    void display();
};

class Werewolf : public Fighter {
public:
    //     void attack(Vampires& enemy);
    Werewolf(int x, int y);
    void move();
};

class Vampire : public Fighter {
public:
    Vampire(int x, int y);
    //void attack(WereWolves& ememy);
    void move();
};
class Player;
class Avatar : public Entity {
private:
    int magic_filters;
    char team;
public:
    // Player* pointer_to_player;
    //;Avatar();        /*default constructor*/
    Avatar(int x, int y, char team);
    inline int get_filters() { return magic_filters; }
    inline char get_team() { return team; }
    //void move();
};

class Map {
private:
    int x;
    int y;      // (x, y) - > map dimensions
    bool day;   // false -> night  true -> day
    Avatar avatar;
    int vampires;   // count of vampires alive
    int werewolves; // count of werewolves alive
    friend void display_info();      // in order to display the info
    friend int get_random(int, int);
    char** grid;

public:
    Map(int x, int y, char team);    // map constructor
    void create(char team);          // create of the first grid
    // void add_avatar(char);
    void print();                       // display map to terminal
    void update(char input);          // update of tthe grid after player's movement
    inline int get_x()const { return x; }
    inline int get_y()const { return y; }
    inline int get_vampires()const { return vampires; }
    inline int get_werewolves()const { return werewolves; }
    inline bool get_day()const { return day; }
    void change_day();
    //void set_coordinates(Avatar& a,int x,int y);
    Avatar get_avatar() { return avatar; }
    // inline char get_input(Player* player) {return player->input;};
    // friend class Avatar;        //in order to have access to the grid and the dimensions
    std::vector<Werewolf> werewolf_vector;
    std::vector<Vampire> vampire_vector;

};

class Player {
private:
    //char team;      // W -> Werewolves  V -> Vampires
    char input;     // input -> key pressed 
public:
    Player();
    // friend class Game;    // in order to have access to the player's input
    //void set_team(char);
    // friend void Avatar::set_team(Player& p);  
    friend class Map;
    // friend void update(Player* player);          // update of tthe grid after player's movement
    inline char get_input() { return input; };
};

class Game {
private:
    bool paused;  //true -> paused 
    Player player;
    Map map;
public:
    Game(int, int, char);
    void end();
    void pause();       //kalei thn display_info
    void display_info();
    inline Map get_map() { return map; }
    inline Player get_player() { return player; }
};
