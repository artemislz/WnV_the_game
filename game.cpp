#include "game.h"
#include "global.h"
#include <iostream>
#include "map_entity.h"
#include "werewolf.h"
#include "vampire.h"
#include "map.h"
#include "player.h"
#include "fighter.h"
#include "Avatar.h"
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

class player;
/*Game - Member functions & Constructor*/
game::game(const int& x, const int& y, const char& team) : active(true), Map(x, y, team), Player(team), Avatar(x / 2 + 1, y/ 2 + 1, team), team_vampires(x, y, Map), team_werewolves(x, y, Map), Magic_filter(5,5), winners_team('0') {
	std::cout << "The game is starting..." << endl
		<< "You are able to move in the map using arrow keys ..." << endl
		<< "Press space to pause game and X to exit..." << endl
		<< "Enjoy!\n\n";
	map_entity* p = &Avatar;
	Map.place_to_grid(Avatar.get_i(), Avatar.get_j(), p);
	//std::cout << "this should be a: " <<map.get_grid()[x / 2 + 1][y / 2 + 1]->get_type();
	/*Process of putting randomly the magic filter*/
	int xx, yy;
	do {
		xx = get_random(0, x + 1);
		yy = get_random(0, y + 1);
	} while (!Map.check_type(xx, yy, 'e'));
	Magic_filter.setup(xx, yy);
	map_entity* pp = &Magic_filter;
	Map.place_to_grid(xx, yy, pp);
	//const char* win_team = "No winners team";
	//winners_team = win_team;
	system("pause");
}

void game::update() {			//werewolves & vampires move randomly
	static int frame = 0;
	frame++;
	if (frame % 40 == 0)
		Map.change_day();
	int i, j, p;
	map_entity*** grid = Map.get_grid();
	vector<vampire*> vector_vampires = team_vampires.get_teammates(); 
	vector<vampire*>::iterator ptr;
	for (ptr = vector_vampires.begin(); ptr < vector_vampires.end(); ptr++) {
		i = (**ptr).get_i();
		j = (**ptr).get_j();
		p = get_random(1, 8);
		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            //goes_up
			if (Map.check_type(i - 1, j, 'e')) {
				
				swap(grid[i][j], grid[i - 1][j]);
				(**ptr).move(1);
			};
			break;
		case 2:                                             //goes_down
			if (Map.check_type(i + 1, j, 'e')) {
				
				swap(grid[i][j], grid[i + 1][j]);
				(**ptr).move(2);
			};
			break;
		case 3:                                             //goes_left
			if (Map.check_type(i, j - 1, 'e')) {
				
				swap(grid[i][j], grid[i][j - 1]);
				(**ptr).move(3);
			};
			break;
		case 4:                                             //goes_right
			if (Map.check_type(i, j + 1, 'e')) {
				
				swap(grid[i][j], grid[i][j + 1]);
				(**ptr).move(4);
			}
			break;
		case 5:
			if (Map.check_type(i - 1, j + 1, 'e')) {           //goes up right
				
				swap(grid[i][j], grid[i - 1][j + 1]);
				(**ptr).move(5);
			};
			break;
		case 6:
			if (Map.check_type(i - 1, j - 1, 'e')) {
				                         //goes up left
				swap(grid[i][j], grid[i - 1][j - 1]);
				(**ptr).move(6);
			};
			break;
		case 7:
			if (Map.check_type(i + 1, j + 1, 'e')) {
			                                              //goes down right
				swap(grid[i][j], grid[i + 1][j + 1]);
				(**ptr).move(7);
			};
			break;
		case 8:
			if (Map.check_type(i + 1, j - 1, 'e')) {            //goes down left
				
				swap(grid[i][j], grid[i + 1][j - 1]);
				(**ptr).move(8);
			};
			break;

		default:
			break;
		}
		
	}
	vector<werewolf*> vector_werewolves = team_werewolves.get_teammates();
	vector<werewolf*>::iterator ptrr;
	int count = 0;
	for (ptrr = vector_werewolves.begin(); ptrr < vector_werewolves.end(); ptrr++) {
		
		i = (**ptrr).get_i();
		j = (**ptrr).get_j();
		p = get_random(0, 4);
		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            //goes_up
			if (Map.check_type(i - 1, j, 'e')) {
				swap(grid[i][j], grid[i - 1][j]);
				(**ptrr).move(1);
			};
			break;
		case 2:                                             //goes_down
			if (Map.check_type(i + 1, j, 'e')) {
				swap(grid[i][j], grid[i + 1][j]);
				(**ptrr).move(2);
			};
			break;
		case 3:                                             //goes_left
			if (Map.check_type(i, j - 1, 'e')) {
				swap(grid[i][j], grid[i][j - 1]);
				(**ptrr).move(3);
			};
			break;
		case 4:                                             //goes_right
			if (Map.check_type(i, j + 1, 'e')) {
				swap(grid[i][j], grid[i][j + 1]);
				(**ptrr).move(4);
			}
			break;
		}
	}
}

void game::run() {
	Map.print();
	system("cls");
	while (active) {
		if (check_for_winner()) {
			//~map();
			active = false;
			end();
			return;
		}
		while (!_kbhit()) {
			if (check_for_winner()) {		//check if a team has been disappeared
				//~map();
				active = false;
				end();
				return;
			}
			update();
			//cout << "After update \n";
			//map.print();
			interactions();
			//cout << "After interactions \n";
			Map.print();
			//system("pause");
			Sleep(100);
			system("cls");
		};
		//Sleep(100);
		Player.set_input();
		//sleep(
		if (Player.get_input() == X)
			active = false;
		else if (Player.get_input() == SPACE)
			display_info();
		else if (Player.get_input() == F) {			//use magic_filter
			if (Avatar.get_filters() >= 10) {
				if (Player.get_team() == 'V' && Map.get_day())
					Avatar.use_magic_filter(team_vampires.get_teammates());
				else if (Player.get_team() == 'W' && !Map.get_day())
					Avatar.use_magic_filter(team_werewolves.get_teammates());
			}
			//system("pause");
		}
		else {

			//Sleep(400);
			const int& z = Player.get_input();
			//Sleep(400);
			Avatar.move(z, Map, Magic_filter);
			update();
			Map.print();
			Sleep(100);
			system("cls");
		}
	}
	end();
	return;
}


void game::interactions() {

	int count = 0, num = 0, defend_moves = 0, defend_happened = 0;
	bool up = 0, down = 0, left = 0, right = 0;

	map_entity*** grid = Map.get_grid();

	for (int i = 1; i < Map.get_x() + 1; i++) {
		for (int j = 1; j < Map.get_y() + 1; j++) {
			if (grid[i][j]->is_checked()) 			// if is stable_object/Avatar or fighter who interacted, continue
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
			fighter* fptr1 = dynamic_cast<fighter*>(grid[i][j]);
			fighter* fptr2;
			switch (p) {
			case 'u':
				fptr2 = dynamic_cast<fighter*>(grid[i - 1][j]);
				defend_moves += fptr1->interact(*fptr2, 'u', Map);
				break;
			case 'd':
				fptr2 = dynamic_cast<fighter*>(grid[i + 1][j]);
				defend_moves += fptr1->interact(*fptr2, 'd', Map);
				break;
			case 'l':
				fptr2 = dynamic_cast<fighter*>(grid[i][j - 1]);
				defend_moves += fptr1->interact(*fptr2, 'l', Map);
				break;
			case 'r':
				fptr2 = dynamic_cast<fighter*>(grid[i][j + 1]);
				defend_moves += fptr1->interact(*fptr2, 'r', Map);
				break;
					
			}	
		}
	}

	team_vampires.set_all_unchecked();
	team_werewolves.set_all_unchecked();
	/*if (defend_moves) {
		cout << "After a defend that happened\n";
		map.print();
	}*/
}


void game::display_info() {

		string vampire_display = "| Number of Vampires Alive: ";
		string werewolf_display = "| Number of Werewolves Alive: ";
		string magic_filter_display = "| Number of Magic Filters you owned: ";

		vampire_display += to_string(team_vampires.number());
		werewolf_display += to_string(team_werewolves.number());
		magic_filter_display += to_string(Avatar.get_filters());
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

		/*Display health, power, defence, heal of all fighters*/
		cout << endl;
		vector<vampire*> vector_vampires = team_vampires.get_teammates();
		vector<vampire*>::iterator ptr;
		cout << "Team vampires info \n";
		for (ptr = vector_vampires.begin(); ptr < vector_vampires.end(); ptr++){
			(*ptr)->display();
			cout << endl;
		}
		cout << endl;

		vector<werewolf*> vector_werewolves = team_werewolves.get_teammates();
		vector<werewolf*>::iterator ptrr;
		cout << "Team werewolves info \n";
		for (ptrr = vector_werewolves.begin(); ptrr < vector_werewolves.end(); ptrr++){
			(*ptrr)->display();
			cout << endl;
		}
		cout << endl;
		if (!active) {
			return;
		}
		char input = _getch();
		int key = input;
		while (key != SPACE) {
			char input = _getch();
			key = input;
		}
		system("cls");
		return;
}

bool game::check_for_winner() {
	if (team_vampires.number() == 0 || team_werewolves.number() == 0) {
		if (team_vampires.number())
			winners_team = 'V';
		else if(team_werewolves.number()) {
			winners_team = 'W';
		}
	//	else {
	//		cout << "Wrong dimensions...Try again";
	//	}
		// system("cls");
		return true;
	}
	return false;
}

void game::end() {
	
	std::cout << "THE  END OF THE GAME...\n";
	//if (team_vampires.number() != 0 && team_werewolves.number() != 0) {
	//	std::cout << "NO WINNERS TEAM...";
	//	return;
	//}
	//std::cout << "THE WINNERS TEAM IS: " << winners_team << endl;
	if (winners_team == Player.get_team())
		std::cout << "YOU ARE THE WINNER!^o^\n";
	else {
		std::cout << "UNLUCKY...+_+\n";
	}
	std::cout << "PRESS 'ENTER' TO SEE MORE INFO...\n";
	char input = _getch();
	int key = input;
	if (key == ENTER) {
		display_info();
	}
	else {
		std::cout << "SO YOU DON'T CARE...\n";
	}
	return;
}