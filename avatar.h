#pragma once
#include "map.h"
#include "entity.h"

class Avatar : public Entity {
private:
	int magic_filters;
	char team;
public:
	Avatar(int x, int y, char team, char type = 'a');
	inline void add_filter() { magic_filters++; }
	inline int get_filters()const { return magic_filters; }
	void update_avatar(int input, Map& map, Magic_filter& magic_filter);          // update of the grid after player's movement
};
