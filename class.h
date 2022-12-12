#pragma once
#include "globals.h"
#include <vector>

class Map_entity {
protected:
    int i;
    int j;
    char type;      //a->avatar , v->vampire , w->werewolf , t->trees , l->lakes , m->magic_filter , u->up-down outline , s->side's outline
public:
    Map_entity(int i, int j, char type);
    inline int get_i() const { return i; }
    inline int get_j() const { return j; }
    inline char get_type() const { return type; }
    inline void set_type(char t) { type = t; }
    virtual bool is_checked() = 0;
};

class Stable_object : public Map_entity {
public:
    Stable_object(int i, int j, char type);
    bool is_checked() { return 0; }
};

class Entity : public Map_entity {            //<<Fighters,Avatar
    bool checked;       // true if he attacked or has been attacked
public:
    Entity(int i, int j , char type);
    void move(int n);
    bool is_checked() { return checked; }
};

class Fighter : public Entity {
protected:
    int health;         // paradoxh: 10
    int power;          // random [1,3]
    int defence;        // random [1,2]
    int heal;           // random [0,2]
public:
    //void set_values();
    //virtual void attack() = 0;       //?????
    Fighter(int i, int j, char type);
    void display();
    
    inline void add_health() { health++;  }
    inline void lose_health() { health--; }
    inline int get_health() const { return health; }
    inline char get_type()const { return type; }
    template <typename T> void give_heal(T& teammate);
    //template <typename T> void attack(T& enemy);
};

class Werewolf : public Fighter {
public:
    //void attack(Vampires& enemy);
    Werewolf(int i, int j, char type = 'w');
};

class Vampire : public Fighter {
public:
    Vampire(int i, int j, char type = 'v');
    void move(int n);       // n-> possible movements
    //void attack(WereWolves& ememy);
};
class Map;
class Magic_filter : public Map_entity {
public:
	Magic_filter(int x, int y );
    void setup(int i, int j);
    void change_position(Map_entity* p, int old_i, int old_j, Map& map);
    bool is_checked() { return 0; }
};

class Map {
private:
    int x;
    int y;      // (x, y) - > map dimensions
    bool day;   // false -> night  true -> day
   // Avatar avatar;
   
   int werewolves; // count of werewolves alive
   friend int get_random(int, int);
   Map_entity*** grid;
public:
    Map(int x, int y, char team);    // map constructor
    void print();                      // display map to terminal
    //void put_magic_filter(Magic_filter* p, int, int);          //takes the old coordinates of avatar
    inline int get_x()const { return x; }
    inline int get_y()const { return y; }
    inline bool get_day()const { return day; }
    inline Map_entity* get_grid(int i, int j)const { return grid[i][j]; }
    inline Map_entity*** get_grid()const { return grid; }
    inline void place_to_grid(int i, int j, Map_entity*& value) { grid[i][j] = value; }
    void change_day();
    void set_outline();
    void display_info();
    void interactions();
    bool check_type(int, int);      //checks if (i, j) is earth or magic_filter
    bool check_type(int, int, char);
};

template< class T>
class  Team{
private:
	std::vector<T*> teammates;
    bool winner;       // true -> won false -> lose
    int start_size;
public:
	Team(int x, int y, Map& map);
    void place(int x, int y, Map& map);
    inline int number()const { return teammates.size(); }
    inline std::vector<T*> get_teammates() { return teammates; }
    
};

class Player {
private:
    char team;      // W -> Werewolves  V -> Vampires
    int input;     // number of the charcter-key pressed
public:
    Player(char team);
    inline char get_team()const { return team; }
    friend class Map;  
    void set_input();
    inline char get_input()const { return input;};
};

class Avatar : public Entity {
private:
    int magic_filters;
    char team;
public:
    Avatar(int x, int y, char team, char type = 'a');
    inline void add_filter() { magic_filters++; }
    inline int get_filters()const { return magic_filters; }
    void update_avatar(int input, Map& map, Magic_filter& magic_filter);          // update of the grid after player's movement
};

class Game {
private:
    bool active;  //true -> paused
    Map map;
	Player player;
	Avatar avatar;
    Team<Vampire> team_vampires;
    Team<Werewolf> team_werewolves;
    Magic_filter magic_filter; 
	char winners_team;
public:
    Game(int, int, char);
    void end();
    void pause();       //kalei thn display_info
    void display_info();
    inline Map get_map()const { return map; }
    inline Player get_player()const { return player; }
    void run();
    void update();
    bool check_for_winner();       // YES -> END
};