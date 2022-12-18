#pragma once
#include"entity.h"
#include "map.h"
#include "stable_object.h"
#include<vector>
#include <iostream>
class map;

class fighter : public entity {
protected:
	int max_health;
	int health;         // paradoxh: 10
	int power;          // random [1,3]
	int defence;        // random [1,2]
	int heal;           // random [0,2]
public:
	fighter(const int&, const int&, char);
	void display();
	inline void lose_heal() { heal--; }
	void add_health();
	inline void lose_health() { health--; }
	void lose_health(const int enemy_pow);
	inline int get_health() const { return health; }
	inline void set_health(const int& h) { health = h; }
	inline int  get_power()const { return power; }
	inline int get_max_health() const { return max_health; }
	//inline char get_type()const { return type; }
	void give_heal(fighter& teammate);
	void attack(fighter& enemy, map& map);
	bool defend(const char& position_of_enemy, map& map);
	bool interact(fighter& close_fighter, const char& p, map& map);
	bool compare(fighter* f);
	virtual ~fighter() { std::cout << "Destructing fighter..."; }
};