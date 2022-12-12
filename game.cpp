#include "globals.h"
#include "class.h"
/*Game - Member functions & Constructor*/
Game::Game(int x, int y, char team) : active(true), map(x, y, team), player(team), avatar(x / 2 + 1, y / 2 + 1, team), team_vampires(x, y, map), team_werewolves(x, y, map) {
	cout << "The game is starting..." << endl
		<< "You are able to move in the map using arrow keys ..." << endl
		<< "Press space to pause game and X to exit..." << endl
		<< "Enjoy!\n\n";
	Map_entity* p = &avatar;
	map.place_to_grid(avatar.get_i(), avatar.get_j(), p);
	/*Process of putting randomly the magic filter*/
	int xx, yy;
	do {
		xx = get_random(0, x + 1);
		yy = get_random(0, y + 1);
	} while (map.check_type(xx, yy, 'e'));
	magic_filter.setup(xx, yy);
	Map_entity* p = &magic_filter;
	map.place_to_grid(xx, yy, p);
	//const char* win_team = "No winners team";
	//winners_team = win_team;
	system("pause");
}

void Game::update() {			//werewolves & vampires move randomly
	int i, j, p;
	Map_entity*** grid = map.get_grid();
	vector<Vampire> vector_vampires = team_vampires.get_teammates();
	vector<Vampire>::iterator ptr;
	for (ptr = vector_vampires.begin(); ptr < vector_vampires.end(); ptr++) {
		i = (*ptr).get_i();
		j = (*ptr).get_j();
		p = get_random(0, 8);
		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            //goes_up
			if (map.check_type(i - 1, j, 'e')) {
				(*ptr).move(1);
				swap(grid[i][j], grid[i - 1][j]);
				break;
			};
		case 2:                                             //goes_down
			if (map.check_type(i + 1, j, 'e')) {
				(*ptr).move(2);
				swap(grid[i][j], grid[i + 1][j]);
				break;
			};
		case 3:                                             //goes_left
			if (map.check_type(i, j - 1, 'e')) {
				(*ptr).move(3);
				swap(grid[i][j], grid[i][j - 1]);
				break;
			};
		case 4:                                             //goes_right
			if (map.check_type(i, j + 1, 'e')) {
				(*ptr).move(4);
				swap(grid[i][j], grid[i][j + 1]);
				break;
			}
		case 5:
			if (map.check_type(i - 1, j + 1, 'e')) {           //goes up right
				(*ptr).move(5);
				swap(grid[i][j], grid[i - 1][j + 1]);
				break;
			};
		case 6:
			if (map.check_type(i - 1, j - 1, 'e')) {
				(*ptr).move(6);                           //goes up left
				swap(grid[i][j], grid[i - 1][j - 1]);
				break;
			};
		case 7:
			if (map.check_type(i + 1, j + 1, 'e')) {
				(*ptr).move(7);                            //goes down right
				swap(grid[i][j], grid[i + 1][j + 1]);
				break;
			};
		case 8:
			if (map.check_type(i + 1, j - 1, 'e')) {            //goes down left
				(*ptr).move(8);
				swap(grid[i][j], grid[i + 1][j - 1]);
				break;
			};
		};
	}
	vector<Werewolf> vector_werewolves = team_werewolves.get_teammates();
	vector<Werewolf>::iterator ptrr;
	for (ptrr = vector_werewolves.begin(); ptrr < vector_werewolves.end(); ptrr++) {
		i = (*ptrr).get_i();
		j = (*ptrr).get_j();
		p = get_random(0, 4);
		switch (p) {
		case 0:                                            //stay in the same position
			break;
		case 1:                                            //goes_up
			if (map.check_type(i - 1, j, 'e')) {
				(*ptrr).move(1);
				swap(grid[i][j], grid[i - 1][j]);
				break;
			};
		case 2:                                             //goes_down
			if (map.check_type(i + 1, j, 'e')) {
				(*ptrr).move(2);
				swap(grid[i][j], grid[i + 1][j]);
				break;
			};
		case 3:                                             //goes_left
			if (map.check_type(i, j - 1, 'e')) {
				(*ptrr).move(3);
				swap(grid[i][j], grid[i][j - 1]);
				break;
			};
		case 4:                                             //goes_right
			if (map.check_type(i, j + 1, 'e')) {
				(*ptrr).move(4);
				swap(grid[i][j], grid[i][j + 1]);
				break;
			}
		}
	}
}

void Game::run() {

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
			map.print();
			Sleep(100);
			system("cls");
		};
		//	Sleep(100);
		player.set_input();
		// sleep(200);
		if (player.get_input() == KEY_X)
			active = false;
		else if (player.get_input() == KEY_SPACE)
			display_info();
		else {
			avatar.update_avatar(player.get_input(), map, magic_filter);
			map.print();
			Sleep(100);
			system("cls");
		}
	}
	end();
	return;
}

void Game::display_info() {

	string vampire_display = "| Number of Vampires Alive: ";
	string werewolf_display = "| Number of Werewolves Alive: ";
	string magic_filter_display = "| Number of Magic Filters you owned: ";

	vampire_display += to_string(team_vampires.number());
	werewolf_display += to_string(team_werewolves.number());
	magic_filter_display += to_string(avatar.get_filters());
	for (int i = 0; i < 20; i++)
		cout << " -";
	cout << endl << vampire_display;

	for (int i = 0, size = 40 - vampire_display.size(); i < size; i++)
		cout << " ";
	cout << "|\n" << werewolf_display;

	for (int i = 0, size = 40 - werewolf_display.size(); i < size; i++)
		cout << " ";
	cout << "|\n" << magic_filter_display;

	for (int i = 0, size = 40 - magic_filter_display.size(); i < size; i++)
		cout << " ";
	cout << "|\n";
	for (int i = 0; i < 20; i++)
		cout << " -";
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
			winners_team = "Vampires";
		else {
			winners_team = "Werewolves";
		}
		// system("cls");
		return true;
	}
	return false;
}

void Game::end() {
	cout << "THE  END OF THE GAME...\n";
	if (team_vampires.number() != 0 && team_werewolves.number() != 0) {
		cout << winners_team;
		return;
	}
	cout << "THE WINNERS TEAM IS: " << winners_team << endl;
	if (winners_team[0] == player.get_team())
		cout << "YOU ARE THE WINNER!^o^\n";
	else {
		cout << "UNLUCKY...+_+\n";
	}

	cout << "PRESS 'ENTER' TO SEE MORE INFO...\n";
	Sleep(200);
	char input = _getch();
	int key = input;
	if (key == KEY_ENTER) {
		display_info();
	}
	else {
		cout << "SO YOU DON'T CARE...\n";
	}
}