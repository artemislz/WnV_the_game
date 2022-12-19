#pragma once

#include "map_entity.h"
#include <iostream>

class entity : public map_entity {				//<<Fighters,Avatar
	bool checked;								// true if it has to interact with other entity
public:
	entity(const int& i, const int& j, const char type);
	virtual void move(const int& n);			// n corresponds to a direction of movement
	void set_checked() { checked = !checked; };
	inline bool is_checked()override { return checked; }	//declared as override because it overrides 
															//the pure virtual 'is_checked' of map_entity
	virtual ~entity() = default;	// virtual destructor because it's a derived class
};
