#pragma once
#include "map.h"
#include "map_entity.h"
#include <iostream>
class map;

class magic_filter : public map_entity {
public:

	magic_filter(map& Map);													//initialize of random coordinates of magic filter 

	void change_position(int old_avatar_i, int old_avatar_j, map& Map);		// it takes the old avatar's position in order to swap it with  
																			//the earth in which the magic filter will pe placed after

	bool is_checked() override { return true; }			// werewolves and vampires shouldn't interact with it
	virtual ~magic_filter() = default;					// virtual destructor because it's a derived class
};
