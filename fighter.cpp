#include "fighter.h"
#include "global.h"
#include "stable_object.h"
#include "map.h"
#include "map_entity.h"
#include <iostream>

/*Fighter - Member functions & Constructor*/
Fighter::Fighter(int x, int y, char type) : Entity(x, y, type), health(10) {
    power = get_random(1, 3);
    defence = get_random(1, 2);
    heal = get_random(0, 2);
    this->type = type;
}

void Fighter::display() {
    std::cout << "\tpower: " << power << std::endl;
    std::cout << "\tdefence: " << defence << std::endl;
    std::cout << "\theal: " << heal << std::endl;
    std::cout << "\thealth" << health << std::endl;
}

template <typename T> void Fighter::attack(T& enemy, Map& map) {
	enemy.lose_health(power);			//power of the attacker
	Map_entity*** grid = map.get_grid();
	if (enemy.get_health() == 0) {
		int i = enemy.get_i();
		int j = enemy.get_j();
		delete grid[i][j];
		grid[i][j] = new Stable_object(i, j, 'e');
	}
	/*else {
		defend(enemy, map);
	}*/
}

