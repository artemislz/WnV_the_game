#include "global.h"
#include "map.h"
#include "stable_object.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
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


