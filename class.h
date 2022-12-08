#pragma once
#include "globals.h"
#include <vector>




class Entity {            //<<Fighters,Avatar
protected:
    int x;      // position
    int y;
public:
    Entity(int x, int y);
    inline int get_x() const { return x; }
    inline int get_y() const { return y; }
    inline void move_up() { x--; }          //-> prosthhkh allagh theshs sto grid
    inline void move_down() { x++; }
    inline void move_right() { y++; }
    inline void move_left() { y--; }
};

class Fighter : public Entity {
protected:
    int health;         // paradoxh: 10
    int power;          // random [1,3]
    int defence;        // random [1,2]
    int heal;           // random [0,2]
    char type;
    bool checked;       // true -> checked if he has fighters close to him
public:
    //void set_values();
    //virtual void attack() = 0;       //?????
    Fighter(int x, int y, char type);
    void display();
    inline char get_type()const { return type; }
    friend bool comparefunc(Fighter*, Fighter*);
};
static bool comparefunc(Fighter& f1, Fighter& f2);
class Werewolf : public Fighter {
public:
    //void attack(Vampires& enemy);
    Werewolf(int x, int y, char type);
};

class Vampire : public Fighter {
public:
    Vampire(int x, int y, char type);
    //void attack(WereWolves& ememy);
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
    inline void add_filter() { magic_filters++; }
    inline int get_filters()const { return magic_filters; }
    inline char get_team()const { return team; }
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
    friend int get_random(int, int);
    char** grid;
   
public:
    Map(int x, int y, char team);    // map constructor
    void create(char team);          // create of the first grid
    // void add_avatar(char);
    void print();                      // display map to terminal
    void update_avatar(int input);          // update of the grid after player's movement
    void update();
    void put_magic_filter();
    inline int get_x()const { return x; }
    inline int get_y()const { return y; }
    inline int get_vampires()const { return vampires; }
    inline int get_werewolves()const { return werewolves; }
    inline Avatar get_avatar() { return avatar; }
    inline bool get_day()const { return day; }
    void change_day();
    void set_outline();
    void display_info();
    void move();
    void interactions();

  //  void move_vampires();
   // void move_werewolves();
     std::vector<Fighter> fighters_vector;
     Fighter search();
    //inline char** get_grid() { return grid; }
    //void set_coordinates(Avatar& a,int x,int y);
    // inline char get_input(Player* player) {return player->input;};
    // friend class Avatar;        //in order to have access to the grid and the dimensions
    //void reposition(int sx, int sy, int fx, int fy);
};

class Player {
private:
    char team;      // W -> Werewolves  V -> Vampires
    int input;     // number of the charcter-key pressed
public:
    Player(char team);
    // friend class Game;    // in order to have access to the player's input
    inline char get_team()const { return team; };
    // friend void Avatar::set_team(Player& p);  
    friend class Map;
    // friend void update(Player* player);          // update of tthe grid after player's movement
    void set_input();
    inline char get_input()const { return input;};
};

class Game {
private:
    bool active;  //true -> paused
    Player player;
    Map map;
    char winners_team;
public:
    Game(int, int, char);
    void end();
    void pause();       //kalei thn display_info
    inline Map get_map()const { return map; }
    inline Player get_player()const { return player; }
    void run();
    bool check_for_end();       // YES -> END
};
