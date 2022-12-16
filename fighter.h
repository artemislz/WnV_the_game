#pragma once
#include"entity.h"
#include "map.h"
#include "stable_object.h"
#include<vector>
#include <iostream>
class Map;

class Fighter : public Entity {
protected:
	int health;         // paradoxh: 10
	int power;          // random [1,3]
	int defence;        // random [1,2]
	int heal;           // random [0,2]
	int vector_position;	//
	//std::vector<T>* ptr_teammates;
public:
	Fighter(int i, int j, char type);
	void display();
	void lose_heal() { heal--; }
	void add_health() { health++; }
	void lose_health() { health--; }
	void lose_health(int enemy_pow);
	int get_health() const { return health; }
	int  get_power()const { return power; }
	//inline char get_type()const { return type; }
	void give_heal(Fighter& teammate);
	void attack(Fighter& enemy, Map& map);
	bool defend(char position_of_enemy, Map& map);
	bool interact(Fighter& close_fighter, const char& p, Map& map);
	//void health_decrease() { health--; }
};