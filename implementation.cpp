#include <iostream>
#include "class.h"
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <algorithm>
#include <execution>

//#include <bits/stdc++.h>
using namespace std;

//global functions
int get_random(int a, int b) {
    return a + rand() % (b - a + 1);
}

/*Avatar - Member functions & Constructor*/
Avatar::Avatar(int i, int j, char team, char type) : Entity(i, j,type), magic_filters(1) {
    this->team = team;
}

/*Map Entity - Member functions & Constructor*/
Map_entity::Map_entity(int i, int j, char type) {
    this->i = i;
    this->j = j;
    this->type = type;
}

/*Entity - Member functions & constructors*/
Entity::Entity(int i, int j, char type) : Map_entity(i, j, type) {
}

/*Map - Member functions & Constructor*/
Map::Map(int x, int y, char team) : x(x), y(y), day(true), avatar(x / 2 + 1, y / 2 + 1, team ) {
    
    vampires = (x * y) / 30;
    werewolves = vampires;      // same number of vampires and werewolves at first
    create();               // takes team as input for the avatar
}

void Map::create() {
    int xx, yy;         // for outputs of function get_random in while loops
    srand((unsigned)time(NULL));

    grid = new Map_entity **[x + 2];    // 2 extra lines for the outline
    for (int i = 0; i < x + 2; i++)
        grid[i] = new Map_entity *[y + 2];
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {
            grid[i][j] = NULL;
        }
    }
    /*Process of creating the outline of the map*/
    set_outline();

    /*Process of putting avatar in the center of the map*/
    grid[x / 2 + 1][y / 2 + 1] = &avatar;      // we first put the avatar in order to avoid the middle specific position being taken by another entity or obstacle

    /*Process of creating and putting in random places vampires and werewolves*/
    for (int i = 0; i < vampires; i++) {         // same number of vampires and werewolves at the start of the game
        /*fill with vampires and werewolves*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != NULL);
        Vampire* v = new Vampire(xx, yy);
        Map_entity* m = v;
        grid[xx][yy] = m;
        vector_fighters.push_back(*v);
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != NULL);
        Werewolf* w = new Werewolf(xx, yy);
        m = w;
        grid[xx][yy] = m;
        vector_fighters.push_back(*w);
    };
    /*Process of putting in random places lakes and trees*/
    int num = 0.04 * (x * y);        //4% of the positions of the grid
    for (int i = 0; i < num; i++) {
        /*fill with lakes(~)*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != NULL);
        grid[xx][yy] = new Map_entity(xx,yy,'l');
        
        /*fill with trees(*)*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != NULL);
        grid[xx][yy] = new Map_entity(xx,yy,'t');
    }
    /*Process of putting randomly the magic filter*/
    do {
        xx = get_random(0, x + 1);
        yy = get_random(0, y + 1);
    } while (grid[xx][yy] != NULL);
    grid[xx][yy] = new Map_entity(xx, yy, 'm');

    /*Process of filling the rest of the grid with earth*/
    for (int i = 1; i < x + 1; i++) {
        for (int j = 1; j < y + 1; j++) {                   //not checking the outline's positions
            if (grid[i][j] == NULL) {
                grid[i][j] = new Map_entity(i, j, 'e');
            }
        }
    }
    return;
}

void Map::set_outline() {
    for (int i = 1; i < x + 1; i++) {
        grid[i][0] = new Map_entity(i,0,'s');  // |
        grid[i][y + 1] =  new Map_entity(i,y+1,'s');
    }
    for (int j = 0; j < y + 2; j++) {
        grid[0][j] = new Map_entity(0, j, 'u');
        grid[x + 1][j] = new Map_entity(x + 1, j, 'u');
    };
}

void Map::put_magic_filter(Map_entity *p,int old_i, int old_j) {
    int xx, yy;
    do {
        xx = get_random(0, x + 1);
        yy = get_random(0, y + 1);
    }while (!check_type(xx,yy,'e'));
    swap(grid[xx][yy], grid[old_i][old_j]); //swap the old position of avatar with earth
    grid[xx][yy] = p;       //object of magic filter
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
    if ((*grid[i][j]).get_type() == 'e' || (*grid[i][j]).get_type() == 'm') {           //
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

void Map::update_avatar(int input) {       // called when player press a button that moves the avatar
    static int calls = 0;
    int i, j;
    char type;
    calls++;
    i = avatar.get_i();
    j = avatar.get_j();
    //  cout << x << " " << y << endl;
    switch (input) {
        case KEY_UP:
            if (check_type(i - 1, j)) {
                avatar.move_up();
                if (check_type(i - 1,  j,'m')) {
                    Map_entity* p = grid[i - 1][j];         //old position of magic filter
                    swap(grid[i - 1][j], grid[i][j]);
                    avatar.add_filter();
                    put_magic_filter(p, i, j);
                }
                else {
                    swap(grid[i][j], grid[i - 1][j]);
                }
                break;
            }
    case KEY_DOWN:
        if (check_type(i + 1, j)) {
            avatar.move_down();
            if (check_type(i + 1, j, 'm')) {
                Map_entity* p = grid[i + 1][j];         //old position of magic filter
                avatar.add_filter();
                put_magic_filter(p, i, j);
            }
            else {
                swap(grid[i][j], grid[i + 1][j]);
            }
            break;
        }
    case KEY_RIGHT:
        if (check_type(i, j + 1)) {
            avatar.move_right();
            if (check_type(i, j + 1, 'm')) {
                Map_entity* p = grid[i][j + 1];         //old position of magic filter
                avatar.add_filter();
                put_magic_filter(p, i, j);
            }
            else {
                swap(grid[i][j], grid[i][j + 1]);
            }
            break;
        }
    case KEY_LEFT:
        if (check_type(i, j - 1)) {
            avatar.move_left();
            if (check_type(i, j - 1, 'm')) {
                Map_entity* p = grid[i][j - 1];         //old position of magic filter
                avatar.add_filter();
                put_magic_filter(p, i, j);
            }
            else {
                swap(grid[i][j], grid[i][j - 1]);
            }
            break;
        }
    default:
        break;
    }
    if (calls % 10 == 0)        //change of the weather after 10 avatars moves
        change_day();
   
}

void Map::update() {        //vampires werewolves 1 random move attacks and defence
    move();
    interactions();
}


void Map::move() {
    int i, j;
    char t;
	vector<Fighter>::iterator ptr;
    for (ptr = vector_fighters.begin(); ptr < vector_fighters.end(); ptr++) {
        t = (*ptr).get_type();
        i = (*ptr).get_i();
        j = (*ptr).get_j();
        int p;
        if (check_type(i, j, 'w')) {
            p = get_random(0, 4);
        }
        else {
            p = get_random(0, 8);
        }
        switch (p) {
        case 0:                 //stay in the same position
            break;
        case 1:                 //goes_up
            if (check_type(i - 1, j, 'e')) {
                (*ptr).move_up();
                swap(grid[i][j], grid[i - 1][j]);
                break;
            };
        case 2:                 //goes_down
            if (check_type(i + 1, j, 'e')) {
                (*ptr).move_down();
                swap(grid[i][j], grid[i + 1][j]);
                break;
            };
        case 3:                 //goes_left
            if (check_type(i, j - 1, 'e')) {
                (*ptr).move_left();
                swap(grid[i][j], grid[i][j - 1]);
                break;
            };
        case 4:                 //goes_right
            if (check_type(i, j + 1, 'e')) {
                (*ptr).move_right();
                swap(grid[i][j], grid[i][j + 1]);
                break;
            }
        case 5:
            if (check_type(i - 1, j + 1, 'e')) {           //goes up right
                (*ptr).move_up();
                    (*ptr).move_right();
                    swap(grid[i][j], grid[i - 1][j + 1]);
                    break;
            };
        case 6:
            if (check_type(i - 1, j - 1, 'e')) {
                (*ptr).move_up();       //goes up left
                    (*ptr).move_left();
                    swap(grid[i][j], grid[i - 1][j - 1]);
                    break;
            };
        case 7:
            if (check_type(i + 1, j + 1, 'e')) {
                (*ptr).move_down();
                (*ptr).move_right();    //goes down right
                swap(grid[i][j], grid[i + 1][j + 1]);
                break;
            };
        case 8:
            if (check_type(i + 1, j - 1, 'e')) {            //goes down left
                (*ptr).move_down();
                (*ptr).move_left();
                swap(grid[i][j], grid[i + 1][j - 1]);
                break;
            };
        };
    }
}

void Map::interactions() {
}

void Map::display_info() {

	string vampire_display = "| Number of Vampires Alive: ";
	string werewolf_display = "| Number of Werewolves Alive: ";
	string magic_filter_display = "| Number of Magic Filters you owned: ";

	vampire_display += to_string(vampires);
	werewolf_display += to_string(werewolves);
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

/*Fighter - Member functions & Constructor*/
Fighter::Fighter(int x, int y, char type) : Entity(x, y, type), health(10) {
    power = get_random(1, 3);
    defence = get_random(1, 2);
    heal = get_random(0, 2);
    this->type = type;
}

void Fighter::display() {
    cout << "\tpower: " << power << endl;
    cout << "\tdefence: " << defence << endl;
    cout << "\theal: " << heal << endl;
}

/*Vampire - Member functions & Constructor*/
Vampire::Vampire(int x, int y, char type) : Fighter(x, y, type) {

}

/*Werewolf - Member functions & Constructor*/
Werewolf::Werewolf(int x, int y, char type) : Fighter(x, y, type) {

}

/*Game - Member functions & Constructor*/
Game::Game(int x, int y, char team) : active(true), map(x, y, team), player(team) {
	cout << "The game is starting..." << endl
		<< "You are able to move in the map using arrow keys ..." << endl
		<< "Press space to pause game and X to exit..." << endl
		<< "Enjoy!\n\n";
	system("pause");
}

void Game::run() {

	system("cls");
	while (active) {
		if (check_for_end()) {
			end();
			return;
		}
		while (!_kbhit()) {
			if (check_for_end()) {
				end();
				return;
			}
			map.update();
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
			map.display_info();

		else {
			map.update_avatar(player.get_input());
			map.print();
			Sleep(100);
			system("cls");  
		}
	}
	end();
	return;
}

bool Game::check_for_end() {
	if (map.get_vampires() == 0 || map.get_werewolves() == 0) {
        if (!map.get_vampires())
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
	cout << "PRESS 'ENTER' TO SEE THE RESULTS...\n";
	Sleep(200);
	char input = _getch();
	int key = input;
	if (key == KEY_ENTER) {
		if (winners_team == player.get_team())
			cout << "YOU ARE THE WINNER!^o^\n";
		else {
			cout << "UNLUCKY...+_+\n";
		}
	    //  cout << "Here are the final results...\n";
	    //    map.display_info();
		cout << "WINNERS TEAM: ";
		if (winners_team == 'V')
			cout << "VAMPIRES!\n";
		else {
			cout << "WEREWOLVES!\n";
		}
	}
	else {
		cout << "SO YOU DON'T CARE...\n";
	}
}

/*Player - Member functions & Constructor*/
Player::Player(char team) {         // IF NO W OR V APOSFALMATWSH
    this->team = team;
}

void Player::set_input() {
    char key = _getch();
    input = key;
}