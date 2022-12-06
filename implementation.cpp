﻿#include <iostream>
#include "class.h"
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fcntl.h>
#include <io.h>
using namespace std;

int get_random(int a, int b) {
    return a + rand() % (b - a + 1);
}

/*Avatar - Member functions & Constructor*/
Avatar::Avatar(int x, int y, char team) : Entity(x, y), magic_filters(1) {
    this->team = team;
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

    /*Process of putting avatar in the center of the map*/
    grid[x / 2 + 1][y / 2 + 1] = team;      // we first put the avatar in order to avoid the middle specific position being taken by another entity or obstacle

    /*Process of creating and putting in random places vampires and werewolves*/
    for (int i = 0; i < vampires; i++) {         // same number of vampires and werewolves at the start of the game
        /*fill with vampires*/
        do {
            xx = get_random(0, x + 1);
            yy = get_random(0, y + 1);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = 'v';
        Vampire vampire(xx, yy);
        vampire_vector.push_back(vampire);
        /*fill with werewolves*/
        do {
            xx = get_random(0, x + 1);
            yy = get_random(0, y + 1);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = 'w';
        Werewolf werewolf(xx, yy);
        werewolf_vector.push_back(werewolf);
    };

    /*Process of putting in random places lakes and trees*/
    int num = 0.04 * (x * y);        //4% of the positions of the grid
    for (int i = 0; i < num; i++) {

        /*fill with lakes(~)*/
        do {
            xx = get_random(0, x + 1);
            yy = get_random(0, y + 1);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = '~';

        /*fill with trees(*)*/
        do {
            xx = get_random(0, x + 1);
            yy = get_random(0, y + 1);
        } while (grid[xx][yy] != ' ');
        grid[xx][yy] = '*';

    }

    /*Process of putting randomly the magic filter*/
    do {
        xx = get_random(0, x + 1);
        yy = get_random(0, y + 1);
    } while (grid[xx][yy] != ' ');
    grid[xx][yy] = 'm';

    return;
}


void Map::print() {
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {
            cout << ' ';
            //  cout << "DAY - -";
            //  break;
      //    }
          //else {
            //  cout << "NIGHT -";
             // break;
         // };

    //  }
  //    if (grid[i][j] == 'v') {
   //       cout << grid[i][j];
   //       continue;
   //   }
           /* if (grid[i][j] == 'V') {
                cout << "";
                continue;
            }
            if (grid[i][j] == 'W') {
                cout << "";
                continue;
            }
            /*    if (grid[i][j] == 'w') {
                    cout << "🐺";
                    continue;
                }
                if (grid[i][j] == '~') {
                    cout << "🌊";
                    continue;
                }
                if (grid[i][j] == '*') {
                    cout << "🌲";
                    continue;
                }
                if (grid[i][j] == 'm') {
                    cout << "🔮";
                    continue;
                }
                if (i == 0 && j == y - 2) {
                    cout << grid[i][j];
                    continue;
                }
                if (j != 0) {                    // between outline and the first column's entities/objects only one space
                    cout << grid[i][j] << ' ';
                    continue;
                }*/
     //       cout << "\342\230\272";
            cout << grid[i][j];
            

        }
        cout << endl;
    }

    //cout << "\u203E ";       // source:https://www.codeproject.com/Questions/877314/how-to-print-an-overline-pls-help
    //cout << endl;
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

void Map::update(int input) {
    static int calls = 0;
    int x, y;
    calls++;
    x = avatar.get_x();
    y = avatar.get_y();
    cout << x << " " << y << endl;
    if (input == KEY_UP && grid[x - 1][y] == ' ') {
        grid[x][y] = ' ';
        avatar.move_up();
    }
    else if (input == KEY_DOWN && grid[x + 1][y] == ' ') {
        grid[x][y] = ' ';
        avatar.move_down();
    }
    else if (input == KEY_RIGHT && grid[x][y + 1] == ' ') {
        grid[x][y] = ' ';
        avatar.move_right();
    }
    else if (input == KEY_LEFT && grid[x][y - 1] == ' ') {
        grid[x][y] = ' ';
        avatar.move_left();
    }
    x = avatar.get_x();
    y = avatar.get_y();
    grid[x][y] = avatar.get_team();
    if (calls % 10 == 0)        //change of the weather after 10 calls of update function
        change_day();
    cout << x << " " << y << endl;
    print();
}

/*Entity - Member functions & Constructor*/
Entity::Entity(int x, int y) {
    this->x = x;
    this->y = y;
}

/*Fighter - Member functions & Constructor*/
Fighter::Fighter(int x, int y) : Entity(x, y), health(10) {
    power = get_random(1, 3);
    defence = get_random(1, 2);
    heal = get_random(0, 2);

}
void Fighter::display() {
    cout << "\tpower: " << power << endl;
    cout << "\tdefence: " << defence << endl;
    cout << "\theal: " << heal << endl;
}

/*Vampire - Member functions & Constructor*/
Vampire::Vampire(int x, int y) : Fighter(x, y) {

}


/*Werewolf - Member functions & Constructor*/
Werewolf::Werewolf(int x, int y) : Fighter(x, y) {

}


/*Game - Member functions & Constructor*/
Game::Game(int x, int y, char team) : paused(false), map(x, y, team) {
    cout << "The game is starting..." << endl;
}


/*Player - Member functions & Constructor*/
Player::Player() {
    input = 'u';
}

