#include "game.h"
#include "global.h"
#include <iostream>
#include "map_entity.h"
#include "werewolf.h"
#include "vampire.h"
#include "map.h"
#include "player.h"
#include "fighter.h"
#include "avatar.h"
#include <Windows.h>
#include "magic_filter.h"
#include <string>
#include "team.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <conio.h>
#include "entity.h"
using namespace std;
class Player;
/*Game - Member functions & Constructor*/
Game::Game(int x, int y, char team) : active(true), map(x, y, team), player(team), avatar(x / 2 + 1, y / 2 + 1, team), team_vampires(x, y, map), team_werewolves(x, y, map), magic_filter(5,5) {
	std::cout << "The game is starting..." << endl
		<< "You are able to move in the map using arrow keys ..." << endl
		<< "Press space to pause game and X to exit..." << endl
		<< "Enjoy!\n\n";
	Map_entity* p = &avatar;
	map.place_to_grid(avatar.get_i(), avatar.get_j(), p);
	//std::cout << "this should be a: " <<map.get_grid()[x / 2 + 1][y / 2 + 1]->get_type();

	/*Process of putting randomly the magic filter*/
	int xx, yy;
	do {
		xx = get_random(0, x + 1);
		yy = get_random(0, y + 1);
	} while (!map.check_type(xx, yy, 'e'));
	magic_filter.setup(xx, yy);
	Map_entity* pp = &magic_filter;
	map.place_to_grid(xx, yy, pp);
	//const char* win_team = "No winners team";
	//winners_team = win_team;
	system("pause");
}

void Game::update() {			//werewolves & vampires move randomly
	static int frame = 0;
	frame++;
	if (frame % 40 == 0)
		map.change_day();
	int i, j, p;
	Map_entity*** grid = map.get_grid();
	vector<Vampire*> vector_vampires = team_vampires.get_teammates(); 
	vector<Vampire*>::iterator ptr;
	for (ptr = vector_vampires.begin(); ptr < vector_vampires.end(); ptr++) {
		i = (**ptr).get_i();
		j = (**ptr).get_j();
		p = get_random(0, 8);
		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            //goes_up
			if (map.check_type(i - 1, j, 'e')) {
				(**ptr).move(1);
				swap(grid[i][j], grid[i - 1][j]);
			};
			break;
		case 2:                                             //goes_down
			if (map.check_type(i + 1, j, 'e')) {
				(**ptr).move(2);
				swap(grid[i][j], grid[i + 1][j]);
			};
			break;
		case 3:                                             //goes_left
			if (map.check_type(i, j - 1, 'e')) {
				(**ptr).move(3);
				swap(grid[i][j], grid[i][j - 1]);
			};
			break;
		case 4:                                             //goes_right
			if (map.check_type(i, j + 1, 'e')) {
				(**ptr).move(4);
				swap(grid[i][j], grid[i][j + 1]);
			}
			break;
		case 5:
			if (map.check_type(i - 1, j + 1, 'e')) {           //goes up right
				(**ptr).move(5);
				swap(grid[i][j], grid[i - 1][j + 1]);
			};
			break;
		case 6:
			if (map.check_type(i - 1, j - 1, 'e')) {
				(**ptr).move(6);                           //goes up left
				swap(grid[i][j], grid[i - 1][j - 1]);
			};
			break;
		case 7:
			if (map.check_type(i + 1, j + 1, 'e')) {
				(**ptr).move(7);                            //goes down right
				swap(grid[i][j], grid[i + 1][j + 1]);
			};
			break;
		case 8:
			if (map.check_type(i + 1, j - 1, 'e')) {            //goes down left
				(**ptr).move(8);
				swap(grid[i][j], grid[i + 1][j - 1]);
			};
			break;
		};
	}
	vector<Werewolf*> vector_werewolves = team_werewolves.get_teammates();
	vector<Werewolf*>::iterator ptrr;
	for (ptrr = vector_werewolves.begin(); ptrr < vector_werewolves.end(); ptrr++) {
		i = (**ptrr).get_i();
		j = (**ptrr).get_j();
		p = get_random(0, 4);
		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            //goes_up
			if (map.check_type(i - 1, j, 'e')) {
				swap(grid[i][j], grid[i - 1][j]);
				(**ptrr).move(1);
			};
			break;
		case 2:                                             //goes_down
			if (map.check_type(i + 1, j, 'e')) {
				swap(grid[i][j], grid[i + 1][j]);
				(**ptrr).move(2);
			};
			break;
		case 3:                                             //goes_left
			if (map.check_type(i, j - 1, 'e')) {
				swap(grid[i][j], grid[i][j - 1]);
				(**ptrr).move(3);
			};
			break;
		case 4:                                             //goes_right
			if (map.check_type(i, j + 1, 'e')) {
				swap(grid[i][j], grid[i][j + 1]);
				(**ptrr).move(4);
			}
			break;
		}
	}
}

void Game::run() {
	map.print();
	system("cls");
	while (active) {
		if (check_for_winner()) {
			end();
			return;
		}
		while (!_kbhit()) {
			if (check_for_winner()) {		//check if a team has been disappeared
				end();
				return;
			}
			update();
			
			interactions();
			map.print();
			Sleep(100);
			system("cls");
		};
		//Sleep(100);
		player.set_input();
		//sleep(200);
		if (player.get_input() == KEY_X)
			active = false;
		else if (player.get_input() == KEY_SPACE)
			display_info();
		else if (player.get_input() == KEY_F) {			//use magic_filter
			//std::cout << "key f pressed";
			system("pause");
		}
		else {
			
			//Sleep(400);
			int z = player.get_input();
			//Sleep(400);
			avatar.update_avatar(z, map, magic_filter);
			map.print();
			Sleep(100);
			system("cls");
		}
	}
	end();
	return;
}

void Game::interactions() {
	int count = 0, num = 0;
	bool up, down, left, right;
	up = false;
	down = false;
	left = false;
	right = false;
	Map_entity*** grid = map.get_grid();
	for (int i = 1; i < map.get_x() + 1; i++) {
		for (int j = 1; j < map.get_y() + 1; j++) {
			if (!map.check_type(i, j, 'v') && !map.check_type(i, j, 'w')) { continue; }

			Fighter* f = dynamic_cast<Fighter*>(grid[i][j]);
			if (f->is_checked()) 
				continue;
			vector<char> positions;

			if (map.check_type(i - 1, j, 'v') || map.check_type(i - 1, j, 'w')) {           //up 
				Fighter* pu = dynamic_cast<Fighter*>(grid[i - 1][j]);
				if (!pu->is_checked()) {
					up = true;
					positions.push_back('u');
				}
				std::cout << "check up :" << up;
				system("pause");
				//system("pause");
			}
			if (map.check_type(i + 1, j, 'v') || map.check_type(i + 1, j, 'w')) {
				Fighter* pd = dynamic_cast<Fighter*>(grid[i + 1][j]);
				if (!pd->is_checked()) {
					down = true;
					positions.push_back('d');
				}
			}
			if (map.check_type(i, j - 1, 'v') || map.check_type(i, j - 1, 'w')) {
				Fighter* pl = dynamic_cast<Fighter*>(grid[i][j - 1]);
				if (!pl->is_checked()) {
					left = true;
					positions.push_back('l');
				}
			}
			if (map.check_type(i, j + 1, 'v') || map.check_type(i, j + 1, 'w')) {
				Fighter* pr = dynamic_cast<Fighter*>(grid[i][j + 1]);
				if (!pr->is_checked()) {
					right = true;
					positions.push_back('r');
				}
			}
			//count = up ;
			//num = get_random(1, count);
			if (up) {
				cout << "lalal";
				system("pause");
				char p = 'u';
				switch (p) {
				case 'u':
					if (grid[i - 1][j]->get_type() == grid[i][j]->get_type()) {
						Fighter* fptr1 = dynamic_cast<Fighter*>(grid[i - 1][j]);
						Fighter* fptr2 = dynamic_cast<Fighter*>(grid[i][j]);
						int health1 = fptr1->get_health();
						int health2 = fptr2->get_health();
						//system("pause");
						fptr2->lose_health();
						if (health1 == health2 == 10) continue;
						else {
							std::cout << "fighter 1: ";
							fptr1->display();
							std::cout << "fighter 2: ";
							fptr2->display();
							system("pause");
							int max_health = max(health1, health2);
							if ((max_health == health1) || (health1 == health2)) {
								fptr1->give_heal(*fptr2);
							}
							else {
								fptr2->give_heal(*fptr1);
							}
							std::cout << "after";
							fptr1->display();
							fptr2->display();
							system("pause");
							fptr1->set_checked();
							fptr2->set_checked();
						}
					}
					else {						//different types
						Vampire* vptr;
						Werewolf* wptr;
						if (grid[i - 1][j]->get_type() == 'v' && grid[i][j]->get_type() == 'w') {
							vptr = dynamic_cast<Vampire*>(grid[i - 1][j]);
							wptr = dynamic_cast<Werewolf*>(grid[i][j]);
						}
						else if (grid[i - 1][j]->get_type() == 'w' && grid[i][j]->get_type() == 'v') {
							vptr = dynamic_cast<Vampire*>(grid[i][j]);
							wptr = dynamic_cast<Werewolf*>(grid[i - 1][j]);
						}
						else continue;
						int v_power = vptr->get_power();
						int w_power = wptr->get_power();
						std::cout << "vampire 1: ";
						vptr->display();
						std::cout << "werewolf 2: ";
						wptr->display();
						system("pause");
						int max_power = max(v_power, w_power);
						if (max_power == v_power) {
							vptr->attack(*wptr, map);
						}
						else if (max_power == w_power) {
							wptr->attack(*vptr, map);
						}
						else {			//v_power == w_power -> choose randmply who will attack
							int rand = get_random(1, 2);
							if (rand) {
								vptr->attack(*wptr, map);
							}
							else {
								wptr->attack(*vptr, map);
							}
						}
						std::cout << "after";
						vptr->display();
						wptr->display();
						system("pause");
						vptr->set_checked();
						wptr->set_checked();
					}
				}
			}
		}
	}
}


void Game::display_info() {

		string vampire_display = "| Number of Vampires Alive: ";
		string werewolf_display = "| Number of Werewolves Alive: ";
		string magic_filter_display = "| Number of Magic Filters you owned: ";

		vampire_display += to_string(team_vampires.number());
		werewolf_display += to_string(team_werewolves.number());
		magic_filter_display += to_string(avatar.get_filters());
		for (int i = 0; i < 20; i++)
			std::cout << " -";
		std::cout << endl << vampire_display;

		for (int i = 0, size = 40 - vampire_display.size(); i < size; i++)
			std::cout << " ";
		std::cout << "|\n" << werewolf_display;

		for (int i = 0, size = 40 - werewolf_display.size(); i < size; i++)
			std::cout << " ";
		std::cout << "|\n" << magic_filter_display;

		for (int i = 0, size = 40 - magic_filter_display.size(); i < size; i++)
			std::cout << " ";
		std::cout << "|\n";
		for (int i = 0; i < 20; i++)
			std::cout << " -";
		char input = _getch();
		int key = input;
		while (key != KEY_SPACE) {
			char input = _getch();
			key = input;
		}
		system("cls");
		return;
}

bool Game::check_for_winner() {
	if (team_vampires.number() == 0 || team_werewolves.number() == 0) {
		if (!team_vampires.number())
			winners_team = 'V';
		else {
			winners_team = 'W';
		}
		// system("cls");
		return true;
	}
	return false;
}

void Game::end() {
	std::cout << "THE  END OF THE GAME...\n";
	//if (team_vampires.number() != 0 && team_werewolves.number() != 0) {
	//	std::cout << "NO WINNERS TEAM...";
	//	return;
	//}
	//std::cout << "THE WINNERS TEAM IS: " << winners_team << endl;
	if (winners_team == player.get_team())
		std::cout << "YOU ARE THE WINNER!^o^\n";
	else {
		std::cout << "UNLUCKY...+_+\n";
	}

	std::cout << "PRESS 'ENTER' TO SEE MORE INFO...\n";
	Sleep(200);
	char input = _getch();
	int key = input;
	if (key == KEY_ENTER) {
		display_info();
	}
	else {
		std::cout << "SO YOU DON'T CARE...\n";
	}
}






