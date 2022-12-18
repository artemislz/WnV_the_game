#pragma once
#include "map_entity.h"
#include <iostream>
class map;

class magic_filter : public map_entity {
public:
	magic_filter(int x, int y);
	void setup(int i, int j);
	void change_position(int old_i, int old_j, map& Map);
	bool is_checked() override { return true; }
	virtual ~magic_filter() {std::cout << "magic" ;}
};
