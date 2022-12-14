#include "globals.h"
#include "class.h"

int get_random(int a, int b) {
	return a + rand() % (b - a + 1);
}

/*Game - Member functions & Constructor*/
Game::Game(int x, int y, char team) : active(true), map(x, y, team), player(team), avatar(x / 2 + 1, y / 2 + 1, team), team_vampires(x, y, map), team_werewolves(x, y, map), magic_filter(5,5) {
	cout << "The game is starting..." << endl
		<< "You are able to move in the map using arrow keys ..." << endl
		<< "Press space to pause game and X to exit..." << endl
		<< "Enjoy!\n\n";
	Map_entity* p = &avatar;
	map.place_to_grid(avatar.get_i(), avatar.get_j(), p);
	//cout << "this should be a: " <<map.get_grid()[x / 2 + 1][y / 2 + 1]->get_type();

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
			//cout << "key f pressed";
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
				cout << "check up :" << up;
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
							cout << "fighter 1: ";
							fptr1->display();
							cout << "fighter 2: ";
							fptr2->display();
							system("pause");
							int max_health = max(health1, health2);
							if ((max_health == health1) || (health1 == health2)) {
								fptr1->give_heal(*fptr2);
							}
							else {
								fptr2->give_heal(*fptr1);
							}
							cout << "after";
							fptr1->display();
							fptr2->display();
							system("pause");

						}
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
	cout << "THE  END OF THE GAME...\n";
	//if (team_vampires.number() != 0 && team_werewolves.number() != 0) {
	//	cout << "NO WINNERS TEAM...";
	//	return;
	//}
	//cout << "THE WINNERS TEAM IS: " << winners_team << endl;
	if (winners_team == player.get_team())
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


/*Avatar - Member functions & Constructor*/
Avatar::Avatar(int i, int j, char team, char type) : Entity(i, j, type), magic_filters(1) {
	this->team = team;
}

void Avatar::update_avatar(int input, Map& map, Magic_filter& magic_filter) {       // called when player press a button that moves the avatar
	static int calls = 0;
	char type;
	calls++;
	Map_entity*** grid = map.get_grid();
//	cout <<"this must be a: " <<  grid[i][j]->get_type();
	//system("pause");
	// cout << "before " << i << " " << j << endl;
	switch (input) {
	case KEY_UP:
		if (map.check_type(i - 1, j)) {

			if (map.check_type(i - 1, j, 'm')) {
				Map_entity* p = grid[i - 1][j];         //old position of magic filter
				swap(grid[i - 1][j], grid[i][j]);
				add_filter();
				magic_filter.change_position(p, i, j, map);
			}
			else {
				//Map_entity* p = this;
				swap(grid[i][j], grid[i - 1][j]);
			}
			move(1);
		}
		break;

	case KEY_DOWN:
		if (map.check_type(i + 1, j)) {

			if (map.check_type(i + 1, j, 'm')) {
				Map_entity* p = grid[i + 1][j];         //old position of magic filter
				swap(grid[i + 1][j], grid[i][j]);
				add_filter();
				magic_filter.change_position(p, i, j, map);
			}
			else {
				swap(grid[i][j], grid[i + 1][j]);
			}
			move(2);
			//move down
		}

		break;

	case KEY_LEFT:
		if (map.check_type(i, j - 1)) {

			if (map.check_type(i, j - 1, 'm')) {
				Map_entity* p = grid[i][j - 1];         //old position of magic filter
				swap(grid[i][j - 1], grid[i][j]);
				add_filter();
				magic_filter.change_position(p, i, j, map);
			}
			else {
				swap(grid[i][j], grid[i][j - 1]);
			}
			
			move(3);                             //move left	
		}
		break;
		case KEY_RIGHT:
			if (map.check_type(i, j + 1)) {
				
				if (map.check_type(i, j + 1, 'm')) {
					Map_entity* p = grid[i][j + 1];         //old position of magic filter
					swap(grid[i][j + 1], grid[i][j]);
					add_filter();
					magic_filter.change_position(p, i, j, map);
				}
				else {
					swap(grid[i][j], grid[i][j + 1]);
				}
				move(4);                             //move right    		
			}
		break;
	}
	
}



/*Map - Member functions & Constructor*/
Map::Map(int x, int y, char team) : x(x), y(y), day(true) {
	int xx, yy;         // for outputs of function get_random in while loops
	srand((unsigned)time(NULL));

	grid = new Map_entity * *[x + 2];    // 2 extra lines for the outline
	for (int i = 0; i < x + 2; i++)
		grid[i] = new Map_entity * [y + 2];
	for (int i = 0; i < x + 2; i++) {
		for (int j = 0; j < y + 2; j++) {
			grid[i][j] = NULL;
		}
	}

	/*Process of creating the outline of the map*/
	set_outline();

	/*Process of putting in random places lakes and trees*/
	int num = 0.04 * (x * y);        //4% of the positions of the grid
	for (int i = 0; i < num; i++) {
		/*fill with lakes(~)*/
		do {
			xx = get_random(1, x);
			yy = get_random(1, y);
		} while (grid[xx][yy] != NULL || (xx == x / 2 + 1 && yy == y / 2 + 1));
		grid[xx][yy] = new Stable_object(xx, yy, 'l');

		/*fill with trees(*)*/
		do {
			xx = get_random(1, x);
			yy = get_random(1, y);
		} while (grid[xx][yy] != NULL || (xx == x / 2 + 1 && yy == y / 2 + 1));
		grid[xx][yy] = new Stable_object(xx, yy, 't');
	}
	/*Process of filling the rest of the grid with earth*/
	for (int i = 1; i < x + 1; i++) {
		for (int j = 1; j < y + 1; j++) {                   //not checking the outline's positions
			if (grid[i][j] == NULL) {
				grid[i][j] = new Stable_object(i, j, 'e');
			}
		}
	}
	return;              // takes team as input for the avatar
}


void Map::set_outline() {
	for (int i = 1; i < x + 1; i++) {
		grid[i][0] = new Stable_object(i, 0, 's');  // |
		grid[i][y + 1] = new Stable_object(i, y + 1, 's');
	}
	for (int j = 0; j < y + 2; j++) {
		grid[0][j] = new Stable_object(0, j, 'u');
		grid[x + 1][j] = new Stable_object(x + 1, j, 'u');
	};
}


void Map::print() {
	char type;
	if (day == true) {
		cout << "D A Y" << endl;
	}
	else {
		cout << "N I G H T" << endl;
	}
	for (int i = 0; i < x + 2; i++) {
		for (int j = 0; j < y + 2; j++) {
			type = (*grid[i][j]).get_type();
			cout << ' ';
			switch (type) {
			case 'u':
				cout << '-';
				break;
			case 's':
				cout << '|';
				break;
			case 'e':
				cout << ' ';
				break;
			case 'a':
				cout << 'A';
				break;
			case 'v':
				cout << 'v';
				break;
			case 'w':
				cout << 'w';
				break;
			case 'l':
				cout << '~';
				break;
			case 't':
				cout << '*';
				break;
			case 'm':
				cout << 'm';
				break;
			}
		}
		cout << endl;
	}
}

void Map::change_day() {
	if (day) {
		day = false;
	}
	else {
		day = true;
	}
}

bool Map::check_type(int i, int j) {
	if ((*grid[i][j]).get_type() == 'e' || (*grid[i][j]).get_type() == 'm') {
		//cout << i << ' ' << j << endl;
		return true;
	}
	return false;
}

bool Map::check_type(int i, int j, char type) {
	if ((*grid[i][j]).get_type() == type) {
		return true;
	}
	return false;
}

/*Fighter - Member functions & Constructor*/
Fighter::Fighter(int i, int j, char type) : Entity(i, j, type), health(10) {
	power = get_random(1, 3);
	defence = get_random(1, 2);
	heal = get_random(0, 2);
}

void Fighter::display() {
	cout << "\tpower: " << power << endl;
	cout << "\tdefence: " << defence << endl;
	cout << "\theal: " << heal << endl;
	cout << "\thealth" << health << endl;
}

void Fighter::give_heal(Fighter& teammate) {
	int num = get_random(0, 1);			//give heal or not
	if (num && heal) {					//if doesn't have heal return
		this->lose_heal();
		teammate.add_health();
	}
	else return;
}

/*Team - Member functions & Constructors*/
template< typename T> 
Team<T>::Team<T>(int x, int y, Map& map) {     // dimensions of the map
	winner = false;
	start_size = x * y / 30;
	place(x, y, map);
}

template< typename T>
void Team<T>::place(int x, int y, Map& map) {
	for (int i = 0; i < start_size; i++) {         // same number of vampires and werewolves at the start of the game
		/*fill with teammates*/
		int xx, yy;
		do {
			xx = get_random(1, x);
			yy = get_random(1, y);
		} while (!map.check_type(xx, yy, 'e'));
		T* w = new T(xx, yy);
		Map_entity* m = w;
		map.get_grid()[xx][yy] = m;
		teammates.push_back(w);
	};
}

/*Map Entity - Member functions & Constructor*/
Map_entity::Map_entity(int i, int j, char type) {
	this->i = i;
	this->j = j;
	this->type = type;
}

/*Stable_objects - Constructor*/
Stable_object::Stable_object(int i, int j, char type) : Map_entity(i, j, type) {}

/*Entity - Member functions & constructors*/
Entity::Entity(int i, int j, char type) : Map_entity(i, j, type) , checked(false) {
}

void Entity::move(int n) {
	switch (n) {
	case 1:         //move_up
		i--;
		break;
	case 2:         //move_down
		i++;
		break;
	case 3:         //move_left
		j--;
		break;
	case 4:         //move_right;
		j++;
	}
}

/*Vampire - Member functions & Constructor*/
Vampire::Vampire(int i, int j, char type) : Fighter(i, j, type) {}

void Vampire::move(int n) {
	switch (n) {
	case 1:         //up
		i--;
		break;
	case 2:         //down
		i++;
		break;
	case 3:         //left
		j--;
		break;
	case 4:         //right;
		j++;
		break;
	case 5:         //up_right
		i--;
		j++;
		break;
	case 6:         //up_left
		i--;
		j--;
		break;
	case 7:			//down_right
		i++;
		j++;
		break;
	case 8:         //down_left
		i++;
		j--;
		break;
	}
}

/*Werewolf - Member functions & Constructor*/
Werewolf::Werewolf(int i, int j, char type) : Fighter(i, j, type) {}

/*Magic Filter - Member Functions & Costructors*/
Magic_filter::Magic_filter(int x, int y) : Map_entity(x, y, 'm') {};

void Magic_filter::setup(int i, int j) {
	this->i = i;
	this->j = j;
}

void Magic_filter::change_position(Map_entity* p, int old_i, int old_j, Map& map) {
	int xx, yy;
	Map_entity*** grid = map.get_grid();
	do {
		xx = get_random(0, map.get_x() + 1);
		yy = get_random(0, map.get_y() + 1);
	} while (!map.check_type(xx, yy, 'e'));
	swap(grid[xx][yy], grid[old_i][old_j]);     //swap the old position of avatar with earth
	map.place_to_grid(xx, yy, p);               //object of magic filter
}

/*Player - Member functions & Constructor*/
Player::Player(char team) {         // IF NO W OR V APOSFALMATWSH
	this->team = team;
}

void Player::set_input() {
	char key = _getch();
	input = key;
}