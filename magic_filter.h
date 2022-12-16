#pragma once
#include "map_entity.h"

class Map;

class Magic_filter : public Map_entity {
public:
	Magic_filter(int x, int y);
	void setup(int i, int j);
	void change_position(Map_entity* p, int old_i, int old_j, Map& map);
	bool is_checked() { return true; }
};
