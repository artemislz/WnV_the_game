#pragma once
#include "map_entity.h"
#include <iostream>
class entity : public map_entity {            //<<Fighters,Avatar
	bool checked;       // true if he attacked or has been attacked
public:
	entity(const int& i, const int& j, const char type);
	virtual void move(const int& n);
	void set_checked() { checked = !checked; };
	inline bool is_checked()override { return checked; }
	virtual ~entity() { std::cout << "emtity\n"; };
	//void place(Map& map);
};
