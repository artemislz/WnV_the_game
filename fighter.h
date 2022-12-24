#pragma once
#include"entity.h"
#include "map.h"
#include "stable_object.h"
#include<vector>
#include <iostream>
#define MAX_HEALTH 3		// by aggrement game starts with that value as health for all the fighters
class map;

class fighter : public entity {
protected:	
	int health;         // current health
	int power;          // random [1,3]
	int defense;        // random [1,2]
	int heal;           // random [0,2]
public:
	fighter(const int&, const int&, char);
	void display();							// it displays to the screen info about the specific fighter (used from 
											//display_info() which is called when space is pressed or at the end of the game)
	inline void lose_heal() { heal--; }
	void add_health();
	void lose_health(const int enemy_pow);				//used in attack
	inline int get_health() const { return health; }
	inline void set_health(const int& h) { health = h; }
	inline int  get_power()const { return power; }
	bool interact(fighter& close_fighter, const char& p, map& map);		// it returns 'true' only if a defense has occured
																		// p -> relative position of the 2 fighters
	void give_heal(fighter& teammate);
	void attack(fighter& enemy, map& map);
	bool defend(const char& position_of_enemy, map& map);				
	virtual ~fighter() = default;						// virtual destructor because it's derived class
};