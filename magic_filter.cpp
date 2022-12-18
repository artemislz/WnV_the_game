#include "global.h"
#include "magic_filter.h"
#include <iostream>
#include "map.h"

/*Magic Filter - Member Functions & Costructors*/
magic_filter::magic_filter(int x, int y) : map_entity(x, y, 'm') {};

void magic_filter::setup(int i, int j) {
	this->i = i;
	this->j = j;
}

void magic_filter::change_position(int old_i, int old_j, map& Map) {
	int xx, yy;
	map_entity*** grid = Map.get_grid();
	do {
		xx = get_random(0, Map.get_x() + 1);
		yy = get_random(0, Map.get_y() + 1);
	} while (!Map.check_type(xx, yy, 'e'));

	std::swap(grid[xx][yy], grid[old_i][old_j]);     //swap the old position of avatar with earth
	grid[xx][yy] = this;
	//Map.place_to_grid(xx, yy, p);               //object of magic filter
}
