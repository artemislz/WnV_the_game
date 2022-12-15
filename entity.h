#pragma once
#include "map.h"

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
	//virtual void place(Map& map) = 0;
};

class Stable_object : public Map_entity {
public:
	Stable_object(int i, int j, char type);
	bool is_checked() { return 0; }
	// void place(Map& map);
};

class Magic_filter : public Map_entity {
public:
	Magic_filter(int x, int y);
	void setup(int i, int j);
	void change_position(Map_entity* p, int old_i, int old_j, Map& map);
	bool is_checked() { return 0; }
};

class Entity : public Map_entity {            //<<Fighters,Avatar
	bool checked;       // true if he attacked or has been attacked
public:
	Entity(int i, int j, char type);
	virtual void move(int n);
	void set_checked(bool f);
	bool is_checked() { return checked; }
	//void place(Map& map);
};

class Fighter : public Entity {
protected:
	int health;         // paradoxh: 10
	int power;          // random [1,3]
	int defence;        // random [1,2]
	int heal;           // random [0,2]
public:
	Fighter(int i, int j, char type);
	void display();
	inline void lose_heal() { heal--; }
	inline void add_health() { health++; }
	inline void lose_health() { health--; }
	void lose_health(int enemy_pow);
	inline int get_health() const { return health; }
	inline int  get_power()const { return power; }
	//inline char get_type()const { return type; }
	void give_heal(Fighter& teammate);
	template <typename T> void attack(T& enemy, Map& map);
	//template <typename T> void defend(T& attacked,Map& map);
  //  void health_decrease() { health--; }
};

class Werewolf : public Fighter {
public:
	Werewolf(int i, int j, char type = 'w');
};

class Vampire : public Fighter {
public:
	Vampire(int i, int j, char type = 'v');
	void move(int n);       // n-> possible movements
	//void attack(WereWolves& ememy);
};



