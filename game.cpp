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
Game::Game(int x, int y, char team) : active(true), map(x, y, team), player(team), avatar(x / 2 + 1, y / 2 + 1, team), team_vampires(x, y, map), team_werewolves(x, y, map), magic_filter(5,5), winners_team('0') {
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
		p = get_random(1, 8);
		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            //goes_up
			if (map.check_type(i - 1, j, 'e')) {
				
				swap(grid[i][j], grid[i - 1][j]);
				(**ptr).move(1);
			};
			break;
		case 2:                                             //goes_down
			if (map.check_type(i + 1, j, 'e')) {
				
				swap(grid[i][j], grid[i + 1][j]);
				(**ptr).move(2);
			};
			break;
		case 3:                                             //goes_left
			if (map.check_type(i, j - 1, 'e')) {
				
				swap(grid[i][j], grid[i][j - 1]);
				(**ptr).move(3);
			};
			break;
		case 4:                                             //goes_right
			if (map.check_type(i, j + 1, 'e')) {
				
				swap(grid[i][j], grid[i][j + 1]);
				(**ptr).move(4);
			}
			break;
		case 5:
			if (map.check_type(i - 1, j + 1, 'e')) {           //goes up right
				
				swap(grid[i][j], grid[i - 1][j + 1]);
				(**ptr).move(5);
			};
			break;
		case 6:
			if (map.check_type(i - 1, j - 1, 'e')) {
				                         //goes up left
				swap(grid[i][j], grid[i - 1][j - 1]);
				(**ptr).move(6);
			};
			break;
		case 7:
			if (map.check_type(i + 1, j + 1, 'e')) {
			                                              //goes down right
				swap(grid[i][j], grid[i + 1][j + 1]);
				(**ptr).move(7);
			};
			break;
		case 8:
			if (map.check_type(i + 1, j - 1, 'e')) {            //goes down left
				
				swap(grid[i][j], grid[i + 1][j - 1]);
				(**ptr).move(8);
			};
			break;
		};
	}
	vector<Werewolf*> vector_werewolves = team_werewolves.get_teammates();
	vector<Werewolf*>::iterator ptrr;
	int count = 0;
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
			//cout << "After update \n";
			//map.print();
			interactions();
			//cout << "After interactions \n";
			map.print();
			//system("pause");
			Sleep(100);
			system("cls");
		};
		//Sleep(100);
		player.set_input();
		//sleep(
		if (player.get_input() == KEY_X)
			active = false;
		else if (player.get_input() == KEY_SPACE)
			display_info();
		else if (player.get_input() == KEY_F) {			//use magic_filter
			if (avatar.get_filters() >= 10 ) {
				if(player.get_team() == 'V' && map.get_day())
					avatar.use_magic_filter(team_vampires.get_teammates());
				else if (player.get_team() == 'W' && map.get_day())
					avatar.use_magic_filter(team_werewolves.get_teammates());
			}
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

	int count = 0, num = 0, defend_moves = 0, defend_happened = 0;
	bool up = 0, down = 0, left = 0, right = 0;

	Map_entity*** grid = map.get_grid();

	for (int i = 1; i < map.get_x() + 1; i++) {
		for (int j = 1; j < map.get_y() + 1; j++) {
			if (grid[i][j]->is_checked()) 			// if is stable_object/avatar or fighter who interacted, continue
				continue;
			
			vector<char> positions;	

			up = !grid[i - 1][j]->is_checked();
			if (up) {
				positions.push_back('u');
			}

			down = !grid[i + 1][j]->is_checked();
			if (down) {
				positions.push_back('d');
			}

			right = !grid[i][j + 1]->is_checked();
			if (right) {
				positions.push_back('r');
			}

			left = !grid[i][j - 1]->is_checked();
			if (left) {
				positions.push_back('l');
			}
			count = up + down + left + right;		// select randomly to interact with one of the close fighters
			if (!count) 
				continue;
			num = get_random(0, count - 1);
			char p = positions.at(num);
			Fighter* fptr1 = dynamic_cast<Fighter*>(grid[i][j]);
			Fighter* fptr2;
			switch (p) {
			case 'u':
				fptr2 = dynamic_cast<Fighter*>(grid[i - 1][j]);
				defend_moves += fptr1->interact(*fptr2, 'u', map);
				break;
			case 'd':
				fptr2 = dynamic_cast<Fighter*>(grid[i + 1][j]);
				defend_moves += fptr1->interact(*fptr2, 'd', map);
				break;
			case 'l':
				fptr2 = dynamic_cast<Fighter*>(grid[i][j - 1]);
				defend_moves += fptr1->interact(*fptr2, 'l', map);
				break;
			case 'r':
				fptr2 = dynamic_cast<Fighter*>(grid[i][j + 1]);
				defend_moves += fptr1->interact(*fptr2, 'r', map);
				break;
					
			}	
		}
	}

	team_vampires.set_all_unckecked();
	team_werewolves.set_all_unckecked();
	/*if (defend_moves) {
		cout << "After a defend that happened\n";
		map.print();
	}*/
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
		if (team_vampires.number())
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






