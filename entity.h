#pragma once
#include "map_entity.h"


class Entity : public Map_entity {            //<<Fighters,Avatar
	bool checked;       // true if he attacked or has been attacked
public:
	Entity(int i, int j, char type);
	virtual void move(int n);
	void set_checked() { checked = !checked; };
	bool is_checked() { return checked; }
	//void place(Map& map);
};





