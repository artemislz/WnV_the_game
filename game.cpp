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
#include <string>

using namespace std;

class player;

void set_player_preferences(int& dim_x, int& dim_y, char& team) {
	bool repeat;
	repeat = true;
	cout << "Time to choose the dimensions of the map... " << endl;
	//Sleep(500);
	cout << "The dimensions must be from 10 to 30" << endl;
	//Sleep(500);
	while (repeat) {
		try {
			string x;
			string y;

			/*FOR X DIMENSION*/
			cout << "Enter x : ";
			cin >> x;

			/* If the input contains a character that's not represent a digit is wrong */
			for (int i = 0; i < x.length(); i++) {
				if (!isdigit(x[i])) {
					if (x[i] == '.')		// if it's float ask for integer
						throw(ERROR_FLOAT);
					throw(ERROR_CHAR_INPUT);
				}
			}
			// If the input has more than 3 digits/characters is surely wrong
			// in that way an overflow is avoided
			if (x.length() >= 3) {		
				throw(ERROR_OUT_OF_RANGE);					
			}

			/*if the input is 1 or 2 characters that represents a number convert the string to number*/
			dim_x = stoi(x);

			// by agreement number of werewolves and vampires at the start is x*y/30
			// and we want at least 3 fighters for each team
			// also grids that has dimensions over 30 don't fit well at the terminal
			if (dim_x < 10 || dim_x > 30) 
				throw(ERROR_OUT_OF_RANGE);
			
			/*SAME FOR Y DIMENSION*/
			cout << "Enter y : ";
			cin >> y;

			for (int i = 0; i < y.length(); i++) {
				if (!isdigit(y[i])) {	
					if (y[i] == '.')
						throw(ERROR_FLOAT);
					throw(ERROR_CHAR_INPUT);
				}
			}

			if (y.length() >= 3) {		
				throw(ERROR_OUT_OF_RANGE);					
			}
			
			dim_y = stoi(y);

			if (dim_y > 30 || dim_y < 10 ) {
				throw(ERROR_OUT_OF_RANGE);
			}

			/*if the input is valid ask the player to choose his/her team*/
			repeat = false;

		}

		catch (int n) {

			system("cls");

			switch (n) {

			case(ERROR_OUT_OF_RANGE):
				cout << "Dimension out of range...\n"
					<< "Reminder: x and y must from 10 to 30 \n"
					<< "Please try again.\n";
				break;

			case(ERROR_CHAR_INPUT):
				cout << "Characters are not allowed...\n"
					<< "Please try again.\n";
				break;

			case(ERROR_FLOAT):
				cout << "Only integers are allowed...\n"
					<< "Please try again.\n";
				break;
			}
			
			repeat = true;
		}
	}
	system("cls");
	/* if the char entered for team is different from 'V' or 'W', the input is not valid */
	// repeat until player enter a valid input 
	cout << "Time to choose your team...\n"
		 << "Enter V for Vampires and W for Werewolves: \n";
	repeat = true;
	while (repeat) {
		try {
			cin >> team;
			if (team != 'V' && team != 'W') {
				throw(ERROR_WRONG_TEAM);
			}
			repeat = false;
		}
		catch (int n) {
			system("cls");
			cout << "The team you entered doesn't match with 'V' or 'W'\n"
				<< "Please try again.\n";
			repeat = true;
		}
	}
	system("cls");
}

/*Game - Member functions & Constructor*/
game::game(const int& x, const int& y, const char& team) : active(true), Map(x, y), Player(team), Avatar(x / 2 + 1, y/ 2 + 1, team), team_vampires(Map), team_werewolves(Map), Magic_filter(Map), winners_team('0') {
	cout << "			The game is starting... \n \n ";
	//Sleep(1000);
	cout << "			During the game, vampires and werewolves are fighting...\n \n";
	//Sleep(1500);
	cout << "			You are able to move in the map using arrow keys ...\n \n";
	//Sleep(1500);
	cout << "			Your job is to collect as many magic filters as you can,\n" 
			"			in order to heal the team you chose to support!\n \n";
	//Sleep(2000);
	cout <<  "			At least 10 magic filters are required. Press 'F' to use them.\n \n";
	//Sleep(2000);
	if (team == 'V')
		cout << "			But remember... You can only use them at day...\n \n";
	else
		cout << "			But remember... You can only use them at night...\n \n";
	//Sleep(2000);
	cout << "			Press space to pause and see more info about the game\n \n";
	//Sleep(1500);
	cout << "			Press 'X' to exit...\n \n";
	//Sleep(1000);
	cout << "			Enjoy!\n \n";
	

	/*place avatar and magic filter after they are consructed to the grid*/
	map_entity* p = &Avatar;
	Map.place_to_grid(Avatar.get_i(), Avatar.get_j(), p);			

	map_entity* pp = &Magic_filter;
	Map.place_to_grid(Magic_filter.get_i(), Magic_filter.get_j(), pp);
	
	//system("pause");
	cout << "\t\t\t\tPress any key when you are ready to play...";
	system("pause > nul");								//source :: https://cboard.cprogramming.com/cplusplus-programming/130086-editing-output-message-system-pause.html
}

void game::update() {												
	static int frame = 0;											
	frame++;													
	if (frame % 40 == 0) {			// by agreement day changes and night alternate after 40 updates of game frame
		Map.change_day();			// used static variable so that it its value will be carried through the function calls
		frame = 0;					// set as 0 after the change in order to avoid overflow
	}
	int i, j, p;
	map_entity*** grid = Map.get_grid();

	// werewolves & vampires change position randomly
	// werewolves move up, down, left, right
	// vampires, except for the moves up, down, left, right, 
	// can also move diagonally to any direction
		
	vector<vampire*> vector_vampires = team_vampires.get_teammates(); 
	vector<vampire*>::iterator ptr;
	for (ptr = vector_vampires.begin(); ptr < vector_vampires.end(); ptr++) {

		i = (**ptr).get_i();	// old coordinates
		j = (**ptr).get_j();

		p = get_random(1, 8);	// random direction


		// if the block that fighters is trying to go to is filled with
		// earth, then fighter is able to move and
		// fighter's coordinates change appropriately

		switch (p) {
		case 0:												// stay in the same position
			break;
		case 1:												
			if (Map.check_type(i - 1, j, 'e')) {			// move up 
				
				swap(grid[i][j], grid[i - 1][j]);
				(**ptr).move(1);
			};
			break;
		case 2:                                             
			if (Map.check_type(i + 1, j, 'e')) {			// move down 
				
				swap(grid[i][j], grid[i + 1][j]);
				(**ptr).move(2);
			};
			break;
		case 3:												// move left 
			if (Map.check_type(i, j - 1, 'e')) {
				
				swap(grid[i][j], grid[i][j - 1]);
				(**ptr).move(3);
			};
			break;
		case 4:                                             // move right
			if (Map.check_type(i, j + 1, 'e')) {
				
				swap(grid[i][j], grid[i][j + 1]);
				(**ptr).move(4);
			}
			break;
		case 5:												// move up-right
			if (Map.check_type(i - 1, j + 1, 'e')) {          
				
				swap(grid[i][j], grid[i - 1][j + 1]);
				(**ptr).move(5);
			};
			break;
		case 6:												// move up-left
			if (Map.check_type(i - 1, j - 1, 'e')) {
															
				swap(grid[i][j], grid[i - 1][j - 1]);
				(**ptr).move(6);
			};
			break;
		case 7:												// move down-right
			if (Map.check_type(i + 1, j + 1, 'e')) {
															
				swap(grid[i][j], grid[i + 1][j + 1]);
				(**ptr).move(7);
			};
			break;
		case 8:												// move down-left
			if (Map.check_type(i + 1, j - 1, 'e')) {             
				
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
		
		i = (**ptrr).get_i();			// old coordinates
		j = (**ptrr).get_j();

		p = get_random(0, 4);			// random direction

		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            // move up
			if (Map.check_type(i - 1, j, 'e')) {
				swap(grid[i][j], grid[i - 1][j]);
				(**ptrr).move(1);
			};
			break;
		case 2:												// move down
			if (Map.check_type(i + 1, j, 'e')) {
				swap(grid[i][j], grid[i + 1][j]);
				(**ptrr).move(2);
			};
			break;
		case 3:												// move left                     
			if (Map.check_type(i, j - 1, 'e')) {
				swap(grid[i][j], grid[i][j - 1]);
				(**ptrr).move(3);
			};
			break;
		case 4:												// move right
			if (Map.check_type(i, j + 1, 'e')) {
				swap(grid[i][j], grid[i][j + 1]);
				(**ptrr).move(4);
			}
			break;
		}
	}

}

void game::run() {
	/* Print the initialized map before any update*/
	Map.print();
	Sleep(80);
	system("cls");

	while (active) {
		/*check for winner after the update that happened after the player pressed a key*/
		if (check_for_winner()) {
			active = false;
			end();
			return;
		}

		/*if player didn't press a button*/
		while (!_kbhit()) {

			if (check_for_winner()) {		//check for winner while player doesn't press any key
				active = false;
				end();
				return;
			}

			update();
			Map.print();
			Sleep(80);
			system("cls");

			/*if defence happend print the new grid*/
			if (interactions()) {		
				Map.print();
				Sleep(80);
				system("cls");
			}

			
		};

		/*if player pressed a button*/
		Player.set_input();
		const int& player_input = Player.get_input();

		switch (player_input) {
		case X:						//'X' pressed -> game stops 
			active = false;
			end();
			return;
			break;
		case SPACE:
			pause();				//space pressed -> game paused + info display
			break;
		case F:
			// by agreement avatar can heal his/her team by using 10 magic filters
			if (Avatar.get_filters() >= 10) {			
				// avatar who supports vampires can heal them only at day
				if (Player.get_team() == 'V' && Map.get_day())
					Avatar.use_magic_filter(team_vampires.get_teammates());
				// avatar who supports werewolves can heal them only at night
				else if (Player.get_team() == 'W' && !Map.get_day())
					Avatar.use_magic_filter(team_werewolves.get_teammates());

			}
			break;
		default:				//use of arrow_keys to move avatar
			//save the old dimensions of avatar in order to swap magic filter with  
			//the earth in which it will be placed after 
			int old_i = Avatar.get_i();
			int old_j = Avatar.get_j();
			bool catched = Avatar.move(player_input, Map);				//returns true if avatar catch a magic filter
			if (catched == true) {
				Magic_filter.change_position(old_i, old_j, Map);
			}
			
		}
		update();														//werewolve's and vampire's ramndom movement				
		Map.print();
		Sleep(50);
		system("cls");

		if (interactions()) {											// interactions returns true only if a defend 
			Map.print();												// have happend between two fighters
			Sleep(50);													// In defend() it is possible for a fighter to move 
			system("cls");												// So, print map again
		}

	}
	end();
	return;
}


bool game::interactions() {

	int count = 0, num = 0, defences_counter = 0;
	bool up = 0, down = 0, left = 0, right = 0;

	map_entity*** grid = Map.get_grid();
	
	for (int i = 1; i < Map.get_x() + 1; i++) {
		for (int j = 1; j < Map.get_y() + 1; j++) {
			
			if (grid[i][j]->is_checked()) 								// if it is stable_object/Avatar or fighter who interacted, continue
				continue;
			
			/* Check up, down, right and left block for existance of fighter*/	
			// if there is a fighter in the block push position's character to the
			// vector 
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
			count = up + down + left + right;							// count -> the number of possible movements (used for get_random)
			if (!count)													// if there isn't a fighter close to him continue
				continue;
		
			/* select randomly to interact with one of the close fighters */
			num = get_random(0, count - 1);
			char p = positions.at(num);									// choose from vector one position
			fighter* fptr1 = dynamic_cast<fighter*>(grid[i][j]);		// Convert map_entity pointer to fighter pointer to access 
			fighter* fptr2;												// member functions 

			/* Interaction with the chosen fighter */
			switch (p) {
			case 'u':
				fptr2 = dynamic_cast<fighter*>(grid[i - 1][j]);
				defences_counter += fptr1->interact(*fptr2, 'u', Map);
				break;
			case 'd':
				fptr2 = dynamic_cast<fighter*>(grid[i + 1][j]);
				defences_counter += fptr1->interact(*fptr2, 'd', Map);
				break;
			case 'l':
				fptr2 = dynamic_cast<fighter*>(grid[i][j - 1]);
				defences_counter += fptr1->interact(*fptr2, 'l', Map);
				break;
			case 'r':
				fptr2 = dynamic_cast<fighter*>(grid[i][j + 1]);
				defences_counter += fptr1->interact(*fptr2, 'r', Map);
				break;
					
			}	
		}
	}

	/* Set checked of all the fighters who interact to false */
	team_vampires.set_all_unchecked();
	team_werewolves.set_all_unchecked();

	/*returns true if defence happended so that the new grid will be printed*/
	if (defences_counter)
		return true;
	else
	{
		return false;
	}
}

void game::display_game_info(){

	string vampire_display = "| Number of Vampires Alive: ";
	string werewolf_display = "| Number of Werewolves Alive: ";
	string magic_filter_display = "| Number of Magic Filters you owned: ";

	vampire_display += to_string(team_vampires.teammates_alive());
	werewolf_display += to_string(team_werewolves.teammates_alive());
	magic_filter_display += to_string(Avatar.get_filters());

	/* up outline of the box */
	for (int i = 0; i < 20; i++) {
		if (i == 0) cout << "\t\t\t";
		std::cout << " -";
	}

	/* Display number of vampires alive */
	std::cout << "\n\t\t\t" << vampire_display;
	for (int i = 0, size = 40 - vampire_display.size(); i < size; i++)
		std::cout << " ";

	/* Display number of werewolves alive */
	std::cout << "|\n\t\t\t" << werewolf_display;
	for (int i = 0, size = 40 - werewolf_display.size(); i < size; i++)
		std::cout << " ";

	/* Display number of magic filters that Avatar has in his possesion */
	std::cout << "|\n\t\t\t" << magic_filter_display;
	for (int i = 0, size = 40 - magic_filter_display.size(); i < size; i++)
		std::cout << " ";

	std::cout << "|\n";

	/* down outline of the box */
	for (int i = 0; i < 20; i++) {
		if (i == 0) cout << "\t\t\t";
		std::cout << " -";
	}
}

void game::display_info() {	

	display_game_info();

	/* Display level of power, defence, heal and health 
	of all the fighters of player's team that are still alive */
	cout << "\n \n \t \t \t \t   Your Team's info";	
	if (Player.get_team() == 'V') {	
		team_vampires.display_team();
	}
	else {
		team_werewolves.display_team();
	}
	
}

void game::pause() {

	/* Display number of fighters alive, number of magic filters 
	that Avatar has in his possesion and information about  the
	fighters of team that Avatar supports */
	
	display_info();			
	
	cout << "\n \t \t \tPress space again to continue...";
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
	/* if there are no alive fighters in a team, 
	then the other team wins and the game ends */
	if (team_vampires.teammates_alive() == 0 || team_werewolves.teammates_alive() == 0) {
		if (team_vampires.teammates_alive())
			winners_team = 'V';
		else if(team_werewolves.teammates_alive()) {
			winners_team = 'W';
		}
		return true;
	}
	return false;
}

/*FINAL INFO DISPLAY - RESULTS OF THE GAME*/
void game::end() {

	
	std::cout << "\t \t \tTHE  END OF THE GAME...\n";

	/*if there is winner*/
	if (check_for_winner()) {

		if (Player.get_team() == winners_team) 
			cout << "\t\t\tYOU ARE THE WINNER ! \n ";
		else {
			cout << "\n \t \t \tENEMIES WON... \n";
			cout << "\n \t\t\tMAYBE NEXT TIME... \n";
		}

		cout << "\t \t \tFINAL SCORE: " << team_vampires.teammates_alive() << " - " << team_werewolves.teammates_alive() << endl;

		std::cout << "\t \t \tPRESS 'ENTER' TO SEE MORE INFO...\n";
		char input = _getch();
		int key = input;
		if (key == ENTER) {

			display_game_info();
			
			cout << "\n \n \t \t \tTHE TEAM THAT WON THE BATTLE INFO: \n";
			if (winners_team == 'V') 
				team_vampires.display_team();
			
			else 
				team_werewolves.display_team();
			
		}

		else 
			std::cout << "\t \t \tSO YOU DON'T CARE...\n";
	
	}
	/*if there is no winner*/
	else {

		std::cout << "\t \t \tPRESS 'ENTER' TO SEE MORE INFO...\n";
		char input = _getch();
		int key = input;

		if (key == ENTER) {

			display_game_info();

			cout << "\n \n \t \t \t \t   Team Vampires info";
			team_vampires.display_team();

			cout << "\n\t\t\t\t   Team Werewolves info";
			team_werewolves.display_team();
		}

		else 
			std::cout << "\t \t \tSO YOU DON'T CARE...\n";
	}
		
	return;
}