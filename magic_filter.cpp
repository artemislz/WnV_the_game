#include "global.h"
#include "magic_filter.h"
#include <iostream>
#include "map.h"
#include "map_entity.h"

/*Magic Filter - Member Functions & Costructors*/
magic_filter::magic_filter(map & Map) {
	/* Process of getting random coordinates of the 
	first position of magic filter */
	int xx, yy;
	do {
		xx = get_random(0, Map.get_x() + 1);
		yy = get_random(0, Map.get_y() + 1);
	} while (!Map.check_type(xx, yy, 'e'));
	i = xx;
	j = yy;
	type = 'm';
};

void magic_filter::change_position(int old_avatar_i, int old_avatar_j, map& Map) {
	int xx, yy;
	map_entity*** grid = Map.get_grid();

	do {
		xx = get_random(0, Map.get_x() + 1);
		yy = get_random(0, Map.get_y() + 1);
	} while (!Map.check_type(xx, yy, 'e'));

	std::swap(grid[xx][yy], grid[old_avatar_i][old_avatar_j]);		// swap the old position of avatar with earth
	grid[xx][yy] = this;											// initialize new random position with magic filter
}
