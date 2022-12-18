#include "fighter.h"
#include "global.h"
#include "stable_object.h"
#include "map.h"
#include "map_entity.h"
#include <iostream>
#include "entity.h"
#include "werewolf.h"
#include "vampire.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include "compare.h"

using namespace std;

/*Fighter - Member functions & Constructor*/
fighter::fighter(const int& i, const int& j, const char type) : entity(i, j, type), max_health(3), health(max_health) {
    power = get_random(1, 3);
    defence = get_random(1, 2);
    heal = get_random(0, 2);
    this->type = type;
}

void fighter::display() {
	cout << " i : " << i << "j" << j;
    std::cout << "power: " << power ;
    std::cout << " ,defence: " << defence;
    std::cout << " ,heal: " << heal;
    std::cout << " ,health: " << health;
	cout << endl;
}

void fighter::give_heal(fighter& teammate) {
	int num = get_random(0, 1);			//give heal or not
	if (num && heal) {					//if doesn't have heal return
		this->lose_heal();
		teammate.add_health();
	}
	else return;
}

void fighter::lose_health(int enemy_pow) {
	int diff;
	if (enemy_pow >= defence) {
		diff = enemy_pow - defence;
		health -= diff;
	}
	else return;
}

void fighter::attack(fighter& enemy, map& Map) {
	// wptr;
//	Vampire* vptr;
	//std::cout << "attack\n";
	enemy.lose_health(power);			//power of the attacker
	map_entity*** grid = Map.get_grid();
	//cout << "health is " << enemy.get_health() << endl;
	//system("pause");
	if (enemy.get_health() <= 0) {
		int i = enemy.get_i();
		int j = enemy.get_j();
		//cout << enemy.get_type();
		if (enemy.get_type() == 'w') {
			werewolf*  wptr = dynamic_cast<werewolf*>(&enemy);
			std::vector<werewolf*>* were = (*wptr).get_pointer_to_teammates();
			auto itr = find_if(were->cbegin(), were->cend(), compare_werewolves(wptr));
			were->erase(itr);
			
		}
		else {
			vampire* vptr = dynamic_cast<vampire*>(&enemy);
			std::vector<vampire*>* vamp = (*vptr).get_pointer_to_teammates();
			auto itrr = find_if(vamp->cbegin(), vamp->cend(), compare_vampires(vptr));
			vamp->erase(itrr);
		
		}
		
		grid[i][j] = new stable_object(i, j, 'e');

	}
} 

bool fighter::defend(const char& position_of_enemy, map& Map) {		//returns true if defends happened
	map_entity*** grid = Map.get_grid();
	//std::cout << "defend\n";
	//system("pause");
	switch (position_of_enemy)									//moves to the opposite direction of position of enemy
	{
	case 'u':
		if (Map.check_type(i + 1, j, 'e')) {
			std::swap(grid[i][j], grid[i + 1][j]);
			move(2);		//move down
			return true;
		}
		break;
	case 'd':
		if(Map.check_type(i - 1, j, 'e')){
			std::swap(grid[i][j], grid[i - 1][j]);
			move(1);		//move up
			return true;
		}
		break;
	case 'r':
		if (Map.check_type(i, j - 1, 'e')) {
			std::swap(grid[i][j], grid[i][j - 1]);
			move(3);		//move left
			return true;
		}
		break;
	case 'l':
		if (Map.check_type(i, j + 1, 'e')) {
			std::swap(grid[i][j], grid[i][j + 1]);
			move(4);		//move right
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool fighter::interact(fighter& close_fighter, const char& p, map& Map ) {			//returns true if defends happened

	bool defend_happened = false;

	if(type == close_fighter.get_type()) {
			const int health2 = close_fighter.get_health();
			if (health == health2 && health == 5) {
				set_checked();
				close_fighter.set_checked();
				return false;
			}
			else {
/*				std::cout << "Same type\n";
				std::cout << "i of fighter 1 " << i << "j of fighter 1 " << j << std::endl;
				std::cout << "i of fighter 2 " << close_fighter.get_i() << "j of fighter 2 " << close_fighter.get_j() << std::endl;
				std::cout << "fighter 1: ";
				display();*/
				//std::cout << "fighter 2: " << std::endl;
				//close_fighter.display();
				int max_health = std::max(health, health2);
				if ((max_health == health) || (health == health2)) {
					give_heal(close_fighter);
				}
				else {
					close_fighter.give_heal(*this);
				}
	/**		std::cout << "AFTER ";
				std::cout << "fighter 1: ";
				display();
				std::cout << std::endl;
				std::cout << "fighter 2: ";
				close_fighter.display();
				std::cout << std::endl;*/
				//return 0;
			}
	}
	else {						//different types
		const int power2 = close_fighter.get_power();
	/*	std::cout << "i of fighter 1 " << i << " ,j of fighter 1 " << j << std::endl;
		std::cout << "i of fighter 2 " << close_fighter.get_i() << " ,j of fighter 2 " << close_fighter.get_j() << std::endl;
		std::cout << "Different type\n";
		std::cout << "fighter 1: ";
		display();
		std::cout << std::endl;
		std::cout << "fighter 2: ";
		close_fighter.display();
		std::cout << std::endl;*/
		const int max_power = std::max(power, power2);
		
		char opp;		//opposite direction
		if (max_power == power || (power == power2 && !get_random(0, 1))) {		//power == power2 -> choose randomly who will attack
			
			switch(p){
				case 'u':	opp = 'd';
							break;		
				case 'd':	opp = 'u';
							break;
				case 'r':	opp = 'l';
							break;
				case 'l':	opp = 'r';
							break;
			}
			defend_happened = close_fighter.defend(opp, Map);
			//defend_moves += defend_happened;
			if (!defend_happened) {
				attack(close_fighter, Map);
			}
		}
		else if (max_power == power2 || (power == power2) ){
			defend_happened = defend(p, Map);
			if (!defend_happened) {
				close_fighter.attack(*this, Map);
			}
		}
	/*	std::cout << "AFTER ";
		std::cout << "fighter 1: ";
		display();
		std::cout << std::endl;
		std::cout << "fighter 2: ";
		close_fighter.display();
		std::cout << std::endl;*/
	}
	set_checked();	
	close_fighter.set_checked();
	return defend_happened;
}