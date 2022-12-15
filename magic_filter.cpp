#include "global.h"
#include "magic_filter.h"
#include <iostream>
#include "map.h"

/*Magic Filter - Member Functions & Costructors*/
Magic_filter::Magic_filter(int x, int y) : Map_entity(x, y, 'm') {};

void Magic_filter::setup(int i, int j) {
	this->i = i;
	this->j = j;
}

void Magic_filter::change_position(Map_entity* p, int old_i, int old_j, Map& map) {
	int xx, yy;
	Map_entity*** grid = map.get_grid();
	do {
		xx = get_random(0, map.get_x() + 1);
		yy = get_random(0, map.get_y() + 1);
	} while (!map.check_type(xx, yy, 'e'));
	std::swap(grid[xx][yy], grid[old_i][old_j]);     //swap the old position of avatar with earth
	map.place_to_grid(xx, yy, p);               //object of magic filter
}
