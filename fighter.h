#pragma once
#include"entity.h"

class Map;

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