#include "avatar.h"
#include "global.h"
#include "magic_filter.h"
#include "map.h"
#include <iostream>
#include "entity.h"
#include "game.h"
using namespace std;
/*Avatar - Member functions & Constructor*/
avatar::avatar(const int& i, const int& j, const char& team, const char type ) : entity(i, j, type) {	
	this->team = team;
	magic_filters = 1;				// avatar owns 1 magic filter at the start of the game
}

bool avatar::move(int input, map& Map) {		// called when player press a button that moves the avatar
												//input -> key code
	map_entity*** grid = Map.get_grid();

	switch (input) {
	case UP:
		if (Map.check_type(i - 1,j)) {					//checks if grid[i-1][j] has type 'e' -> earth or 'm' -> magic_filter

			if (Map.check_type(i - 1, j, 'm')) {
				map_entity* p = grid[i - 1][j];         //old position of magic filter
				swap(grid[i - 1][j], grid[i][j]);
				add_filter();
				entity::move(1);						//change of the coordinates i, j			
				return true;
			}
			else {
				swap(grid[i][j], grid[i - 1][j]);
				entity::move(1);						//changes appropriately the coordinates i, j
			}
			
		}
		break;

	case DOWN:
		if (Map.check_type(i + 1, j)) {

			if (Map.check_type(i + 1, j, 'm')) {
				map_entity* p = grid[i + 1][j];			//old position of magic filter
				swap(grid[i + 1][j], grid[i][j]);
				add_filter();
				entity::move(2);						//changes appropriately the coordinates i, j
				return true;
			}
			else {
				swap(grid[i][j], grid[i + 1][j]);		
				entity::move(2);						//changes appropriately the coordinates i, j
			}
			
		}
		break;

	case LEFT:
		if (Map.check_type(i, j - 1)) {

			if (Map.check_type(i, j - 1, 'm')) {
				map_entity* p = grid[i][j - 1];         //old position of magic filter
				swap(grid[i][j - 1], grid[i][j]);
				add_filter();
				entity::move(3);						//changes appropriately the coordinates i, j
				return true;
			}
			else {
				swap(grid[i][j], grid[i][j - 1]);		//changes appropriately the coordinates i, j
				entity::move(3);
			}
			
		}
		break;

	case RIGHT:
		if (Map.check_type(i, j + 1)) {

			if (Map.check_type(i, j + 1, 'm')) {
				map_entity* p = grid[i][j + 1];			//old position of magic filter
				swap(grid[i][j + 1], grid[i][j]);
				add_filter();
				entity::move(4);						//changes appropriately the coordinates i, j   	
				return true;
			}
			else {
				swap(grid[i][j], grid[i][j + 1]);		
				entity::move(4);						//changes appropriately the coordinates i, j
			}
			                  	
		}
		break;

	default:
		break;
	}
	return false;
}
