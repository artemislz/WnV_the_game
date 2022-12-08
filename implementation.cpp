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
static bool comparefunc(Fighter& f1, Fighter& f2) {
    return f1.get_x() < f2.get_x();
}

/*Avatar - Member functions & Constructor*/
Avatar::Avatar(int x, int y, char team) : Entity(x, y), magic_filters(1) {
    this->team = team;
}

/*Entity - Member functions & Constructor*/
Entity::Entity(int x, int y) {
    this->x = x;
    this->y = y;
    
}
/*Map - Member functions & Constructor*/

Map::Map(int x, int y, char team) : x(x), y(y), day(true), avatar(x / 2 + 1, y / 2 + 1, team) {
    grid = new char* [x + 2];    // 2 extra lines for the outline
    for (int i = 0; i < x + 2; i++)
        grid[i] = new char[y + 2];
    vampires = (x * y) / 30;
    werewolves = vampires;      // same number of vampires and werewolves at first
    create(team);               // takes team as input for the avatar
}

void Map::create(char team) {
    int xx, yy;         // for outputs of function get_random in while loops
    srand((unsigned)time(NULL));

    /*Process of creating the outline of the map*/
    set_outline();

    /*Process of putting avatar in the center of the map*/
    grid[x / 2 + 1][y / 2 + 1] = team;      // we first put the avatar in order to avoid the middle specific position being taken by another entity or obstacle

    /*Process of creating and putting in random places vampires and werewolves*/
    for (int i = 0; i < vampires; i++) {         // same number of vampires and werewolves at the start of the game
        /*fill with vampires and werewolves*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = 'v';
        Vampire vampire(xx, yy, 'v');
        fighters_vector.push_back(vampire);
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = 'w';
        Werewolf werewolf(xx, yy, 'w');
        fighters_vector.push_back(werewolf);
    };
    /*Process of putting in random places lakes and trees*/
    int num = 0.04 * (x * y);        //4% of the positions of the grid
    for (int i = 0; i < num; i++) {
        /*fill with lakes(~)*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = '~';
        /*fill with trees(*)*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = '*';

    }

    /*Process of putting randomly the magic filter*/
    put_magic_filter();
    return;
}

void Map::put_magic_filter() {
    int xx, yy;
    do {
        xx = get_random(0, x + 1);
        yy = get_random(0, y + 1);
    } while (grid[xx][yy] != ' ');
    grid[xx][yy] = 'm';
}

void Map::set_outline() {
    for (int i = 1; i < x + 1; i++) {
        grid[i][0] = '|';
        grid[i][y + 1] = '|';
        for (int j = 1; j < y + 1; j++) {
            grid[i][j] = ' ';
        }
    }
    for (int j = 0; j < y + 2; j++) {
        grid[0][j] = '-';
        grid[x + 1][j] = '-';
    };
    grid[0][y - 2] = 'D';
    grid[0][y - 1] = 'A';
    grid[0][y] = 'Y';
}

void Map::print() {
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {
            cout << ' ';
            if(grid[i][j] == 'V' || grid[i][j]=='W'){
                cout << "A";
            }else{
                cout << grid[i][j];
            }
        }
        cout << endl;
    }
}

void Map::change_day() {
    if (day) {
        day = false;
        grid[0][y - 4] = 'N';
        grid[0][y - 3] = 'I';
        grid[0][y - 2] = 'G';
        grid[0][y - 1] = 'H';
        grid[0][y] = 'T';
    }
    else {
        day = true;
        grid[0][y - 2] = 'D';
        grid[0][y - 1] = 'A';
        grid[0][y] = 'Y';
        grid[0][y - 4] = '-';
        grid[0][y - 3] = '-';

    }
}

void Map::update_avatar(int input) {       // called when player press a button that moves the avatar
    static int calls = 0;
    int x, y;
    calls++;
    x = avatar.get_x();
    y = avatar.get_y();
    //  cout << x << " " << y << endl;
    switch (input) {
        case KEY_UP:
            if (grid[x - 1][y] == ' ' || grid[x - 1][y] == 'm') {
                grid[x][y] = ' ';
                avatar.move_up();
                if (grid[x - 1][y] == 'm') {
                    avatar.add_filter();
                    put_magic_filter();
                }
                break;
            }
    case KEY_DOWN:
        if (grid[x + 1][y] == ' ' || grid[x + 1][y] == 'm') {
            grid[x][y] = ' ';
            avatar.move_down();
            if (grid[x + 1][y] == 'm') {
                avatar.add_filter();
                put_magic_filter();
            }
            break;
        }
    case KEY_RIGHT:
        if (grid[x][y + 1] == ' ' || grid[x][y + 1] == 'm') {
            grid[x][y] = ' ';
            avatar.move_right();
            if (grid[x][y + 1] == 'm') {
                avatar.add_filter();
                put_magic_filter();
            }
            break;
        }
    case KEY_LEFT:
        if (grid[x][y - 1] == ' ' || grid[x][y - 1] == 'm') {
            grid[x][y] = ' ';
            avatar.move_left();
            if (grid[x][y - 1] == 'm') {
                avatar.add_filter();
                put_magic_filter();
            }
            break;
        }

    default:
        break;
    }
    
    x = avatar.get_x();
    y = avatar.get_y();
    grid[x][y] = avatar.get_team();
    if (calls % 10 == 0)        //change of the weather after 10 avatars moves
        change_day();
   
}

void Map::update() {        //vampires werewolves 1 random move attacks and defence
    move();
    interactions();

}

void Map::move() {
    int x, y;
    char t;
	vector<Fighter>::iterator ptr;
    for (ptr = fighters_vector.begin(); ptr < fighters_vector.end(); ptr++) {
        t = (*ptr).get_type();
        x = (*ptr).get_x();
        y = (*ptr).get_y();
        int p;
        if (t == 'w')
            p = get_random(0, 4);
        else {
            p = get_random(0, 8);
        }
        switch (p) {
        case 0:                 //stay in the same position
            break;
        case 1:                 //goes_up
            if (grid[x - 1][y] == ' ') {
                grid[x][y] = ' ';
                (*ptr).move_up();
                break;
            };
        case 2:                 //goes_down
            if (grid[x + 1][y] == ' ') {
                grid[x][y] = ' ';
                (*ptr).move_down();
                break;
            };
        case 3:                 //goes_left
            if (grid[x][y - 1] == ' ') {
                grid[x][y] = ' ';
				(*ptr).move_left();
                break;
            };
        case 4:                 //goes_right
            if (grid[x][y + 1] == ' ') {
                grid[x][y] = ' ';
				(*ptr).move_right();
                break;
            }                 //goes_up_right_diagonally
           
        case 5:
            if (grid[x - 1][y + 1] == ' ') {            //goes up right
                grid[x][y] = ' ';
				(*ptr).move_up();
                (*ptr).move_right();
                break;
            };
        case 6:
            if (grid[x - 1][y - 1] == ' ') {
                grid[x][y] = ' ';
				(*ptr).move_up();       //goes up left
                (*ptr).move_left();
                break;
            };
        case 7:
            if (grid[x + 1][y + 1] == ' ') {
                grid[x][y] = ' ';
                (*ptr).move_down();
                (*ptr).move_right();    //goes down right
                break;
            };
        case 8:
            if (grid[x + 1][y - 1] == ' ') {            //goes down left
                grid[x][y] = ' ';
                (*ptr).move_down();
                (*ptr).move_left();
                break;
            };
        };
        x = (*ptr).get_x();
        y = (*ptr).get_y();
        grid[x][y] = (*ptr).get_type();
    }
}

void Map::interactions() {

    sort(fighters_vector.begin(), fighters_vector.end(), &comparefunc);

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
Fighter::Fighter(int x, int y, char type) : Entity(x, y), health(10) {
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