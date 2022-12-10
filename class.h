#pragma once
#include "globals.h"
#include <vector>

class Map_entity {
protected:
    int i;
    int j;
    char type;      //a->avatar , v->vampire , w->werewolf , t->trees , l->lakes , f->filter , u->up-down outline , s->side's outline
public:
    Map_entity(int i, int j, char type);
    inline int get_i() const { return i; }
    inline int get_j() const { return j; }
    inline char get_type() const { return type; }
    inline void set_i(int i) { }
    inline void set_type(char t) { type = t; }
    virtual bool is_checked() = 0;
};

class Stable_object : public Map_entity {
public:
    Stable_object(int i, int j, char type);
    bool is_checked() { return 0; }
};

class Entity : public Map_entity {            //<<Fighters,Avatar
public:
    Entity(int i, int j , char type);
    inline void move_up() { i--; }          //-> prosthhkh allagh theshs sto grid
    inline void move_down() { i++; }
    inline void move_right() { j++; }
    inline void move_left() { j--; }
    bool is_checked() { return 0; }
};

class Fighter : public Entity {
protected:
    int health;         // paradoxh: 10
    int power;          // random [1,3]
    int defence;        // random [1,2]
    int heal;           // random [0,2]
    bool checked;       // true if he attacked or has been attacked
public:
    //void set_values();
    //virtual void attack() = 0;       //?????
    Fighter(int i, int j, char type);
    void display();
    bool is_checked() { return checked; }
    inline void add_health() { health++;  }
    inline void lose_health() { health--; }
    inline int get_health() const { return health; }
    inline char get_type()const { return type; }
};

class Werewolf : public Fighter {
public:
    //void attack(Vampires& enemy);
    Werewolf(int i, int j, char type = 'w');
};

class Vampire : public Fighter {
public:
    Vampire(int i, int j, char type = 'v');
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
    Avatar(int x, int y, char team, char type = 'a');
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
    Map_entity*** grid;
public:
    Map(int x, int y, char team);    // map constructor
    void create();          // create of the first grid
    // void add_avatar(char);
    void print();                      // display map to terminal
    void update_avatar(int input);          // update of the grid after player's movement
    void update();
    void put_magic_filter(Map_entity*,int , int );          //takes the old coordinates of avatar
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
    bool check_type(int, int);
    bool check_type(int, int, char);
    std::vector<Fighter> vector_fighters;
    //  void move_vampires();
    // void move_werewolves();
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
