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
fighter::fighter(const int& i, const int& j, const char type) : entity(i, j, type), health(MAX_HEALTH) {
    power = get_random(1, 3);
    defense = get_random(1, 2);
    heal = get_random(0, 2);
    this->type = type;
}

void fighter::display() {
	//cout << "Coordinates" << " i : " << i << " j : " << j << endl;
	
    cout << "power: " << power ;
    cout << "  defense: " << defense;
	cout << "  heal: " << heal;
    cout << "  health: " << health;
	cout << endl;
}

void fighter::give_heal(fighter& teammate) {
	int num = get_random(0,5);			//give heal or not
	if (!num && heal) {					
		this->lose_heal();
		teammate.add_health();			//if doesn't have heal return
	}
	else return;
}

void fighter::add_health(){
	if(health == MAX_HEALTH) return;
	health++;
}

void fighter::lose_health(int enemy_pow) {
	int diff;

	if (enemy_pow > defense) {
		diff = enemy_pow - defense;
		health -= diff;
	}
	else if (enemy_pow == defense) {		// in case the enemy who is been attacked has the same  
		health--;							//defense value with the health will be diminished by 1	
														
	}
}

void fighter::attack(fighter& enemy, map& Map) {	// fighter attacks to the enemy

	enemy.lose_health(power);					
	
	/*the enemy's death*/
	if (enemy.get_health() <= 0) {				

		int i = enemy.get_i();
		int j = enemy.get_j();

		if (enemy.get_type() == 'w') {

			werewolf* wptr = dynamic_cast<werewolf*>(&enemy);								//convert map_entity pointer to werewolf pointer 
																							//because werewolf is a derived class of map_entity

			std::vector<werewolf*>* were = (*wptr).get_pointer_to_teammates();				//search the werewolf to the vector of his teammates
			auto itr = find_if(were->cbegin(), were->cend(), compare_werewolves(wptr));		//erase him from the vector
			were->erase(itr);
			
		}
		else {

			vampire* vptr = dynamic_cast<vampire*>(&enemy);									//convert map_entity pointer to vampire pointer 
																							//because vampire is a derived class of map_entity
			std::vector<vampire*>* vamp = (*vptr).get_pointer_to_teammates();				//search the vampire to the vector of his teammates
			auto itrr = find_if(vamp->cbegin(), vamp->cend(), compare_vampires(vptr));		//erase him from the vector
			vamp->erase(itrr);
		
		}
		// fill his position with earth
		map_entity* earth = new stable_object(i, j, 'e');
		Map.place_to_grid(i, j, earth);

	}
} 



bool fighter::defend(const char& position_of_enemy, map& Map) {		//returns true if defense happened

	map_entity*** grid = Map.get_grid();
	
	switch (position_of_enemy)										//moves to the opposite direction of enemy's position
	{
	case 'u':
		if (Map.check_type(i + 1, j, 'e')) {
			std::swap(grid[i][j], grid[i + 1][j]);
			move(2);												//changes appropriately the coordinates i, j - move down
			return true;
		}
		break;
	case 'd':
		if(Map.check_type(i - 1, j, 'e')){
			std::swap(grid[i][j], grid[i - 1][j]);
			move(1);												//changes appropriately the coordinates i, j - move up
			return true;
		}
		break;
	case 'r':
		if (Map.check_type(i, j - 1, 'e')) {
			std::swap(grid[i][j], grid[i][j - 1]);
			move(3);												//changes appropriately the coordinates i, j - move left
			return true;
		}
		break;
	case 'l':
		if (Map.check_type(i, j + 1, 'e')) {
			std::swap(grid[i][j], grid[i][j + 1]);
			move(4);												//changes appropriately the coordinates i, j - move right
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

																					
bool fighter::interact(fighter& close_fighter, const char& p, map& Map ) {		//returns true if defense happened	
	bool defense_happened = false;																				

	/*same type of fighters*/
	if(type == close_fighter.get_type()) {						
			const int enemy_health = close_fighter.get_health();							//give heal to the teammate

			/*cout << "Same type" << type << " " << close_fighter.get_type() << endl;
			cout << "fighter 1: " << endl;
			display();
			cout << "fighter 2: " << endl;
			close_fighter.display();*/

			if (health == enemy_health && health == MAX_HEALTH) {
				set_checked();
				close_fighter.set_checked();
				return false;
			}
			else {
				int max_health = std::max(health, enemy_health);
				if ((max_health == health) || (health == enemy_health)) {
					give_heal(close_fighter);
				}
				else {
					close_fighter.give_heal(*this);
				}
			}

			/*cout << "AFTER " << endl;
			cout << "fighter 1: " << endl;
			display();
			cout << std::endl;
			cout << "fighter 2: " << endl;
			close_fighter.display();
			cout << std::endl;
			system("pause");*/

	}
	/*different type of fighters*/

	// if p = 'u' -> close fighter is above fighter
	// if p = 'd' -> close fighter is below fighter
	// if p = 'r' -> close fighter is on fighter's right
	// if p = 'l' -> close fighter is on fighter's left
	else {														

		const int enemy_power = close_fighter.get_power();
		const int max_power = std::max(power, enemy_power);

		/*cout << "Different type\n";
		cout << "fighter 1: " << endl;
		display();
		cout << std::endl;
		cout << "fighter 2: " << endl;
		close_fighter.display();
		cout << std::endl;*/

		
		char opp;												//opposite direction
		if (max_power == power || (power == enemy_power && !get_random(0, 1))) {		//if power == enemy_power -> choose randomly who will attack to
			if (power != enemy_power) {
				switch (p) {
				case 'u':	opp = 'd';
					break;
				case 'd':	opp = 'u';
					break;
				case 'r':	opp = 'l';
					break;
				case 'l':	opp = 'r';
					break;
				}
				// if the fighter attack to the close enemy, 
				//close fighter will defend my moving to the opposite direction
				//because it has the opposite relative position (opp)

				defense_happened = close_fighter.defend(opp, Map);

				//if defend() return false, this means that fighter 
				//didn't manage to move away from the attacker
				//So the enemy attacks.	
				if (!defense_happened) {
					attack(close_fighter, Map);
				}
			}
			else {
				attack(close_fighter, Map);
			}
		
		}
		// if the close_enemy attack to fighter then 
		// we have already their relative position (p)
		else if (max_power == enemy_power || (power == enemy_power) ){
			if (power != enemy_power) {
				defense_happened = defend(p, Map);
				if (!defense_happened) {
					close_fighter.attack(*this, Map);
				}
			}
			else {
				close_fighter.attack(*this, Map);
			}
			
		}

		/*cout << "AFTER ";
		cout << "fighter 1: ";
		display();
		cout << std::endl;
		cout << "fighter 2: ";
		close_fighter.display();
		cout << endl;
		system("pause");*/

	}
	set_checked();														//mark them as fighters who have interacted with each other
	close_fighter.set_checked();
	return defense_happened;
}