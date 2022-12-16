#include "fighter.h"
#include "global.h"
#include "stable_object.h"
#include "map.h"
#include "map_entity.h"
#include <iostream>
#include "entity.h"

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



void Fighter::give_heal(Fighter& teammate) {
	int num = get_random(0, 1);			//give heal or not
	if (num && heal) {					//if doesn't have heal return
		this->lose_heal();
		teammate.add_health();
	}
	else return;
}

void Fighter::lose_health(int enemy_pow) {
	int diff;
	if (enemy_pow >= defence) {
		diff = enemy_pow - defence;
		health -= diff;
	}
	else return;
	/*else {
		diff = defence - enemy_pow;
	}*/
}