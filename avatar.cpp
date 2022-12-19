#include "avatar.h"
#include "global.h"
#include "magic_filter.h"
#include "map.h"
#include <iostream>
#include "entity.h"

using namespace std;
/*Avatar - Member functions & Constructor*/
avatar::avatar(const int& i, const int& j, const char& team, const char type ) : entity(i, j, type), magic_filters(1) {
	this->team = team;
}

void avatar::move(int input, map& map, magic_filter& magic_filter) {       // called when player press a button that moves the avatar
	static int calls = 0;
	char type;
	calls++;
	map_entity*** grid = map.get_grid();
	//	cout <<"this must be a: " <<  grid[i][j]->get_type();
		//system("pause");
		// cout << "before " << i << " " << j << endl;
	switch (input) {
	case UP:
		if (map.check_type(i - 1,j)) {

			if (map.check_type(i - 1, j, 'm')) {
				map_entity* p = grid[i - 1][j];         //old position of magic filter
				swap(grid[i - 1][j], grid[i][j]);
				add_filter();
				magic_filter.change_position(i, j, map);
			}
			else {
				//Map_entity* p = this;
				swap(grid[i][j], grid[i - 1][j]);
			}
			entity::move(1);
		}
		break;

	case DOWN:
		if (map.check_type(i + 1, j)) {

			if (map.check_type(i + 1, j, 'm')) {
				map_entity* p = grid[i + 1][j];         //old position of magic filter
				swap(grid[i + 1][j], grid[i][j]);
				add_filter();
				magic_filter.change_position(i, j, map);
			}
			else {
				swap(grid[i][j], grid[i + 1][j]);
			}
			entity::move(2);									//move down
		}
		break;

	case LEFT:
		if (map.check_type(i, j - 1)) {

			if (map.check_type(i, j - 1, 'm')) {
				map_entity* p = grid[i][j - 1];         //old position of magic filter
				swap(grid[i][j - 1], grid[i][j]);
				add_filter();
				magic_filter.change_position(i, j, map);
			}
			else {
				swap(grid[i][j], grid[i][j - 1]);
			}

			entity::move(3);                             //move left	
		}
		break;
	case RIGHT:
		if (map.check_type(i, j + 1)) {

			if (map.check_type(i, j + 1, 'm')) {
				map_entity* p = grid[i][j + 1];         //old position of magic filter
				swap(grid[i][j + 1], grid[i][j]);
				add_filter();
				magic_filter.change_position(i, j, map);
			}
			else {
				swap(grid[i][j], grid[i][j + 1]);
			}
			entity::move(4);                             //move right    		
		}
		break;

	default:
		break;
	}

}
