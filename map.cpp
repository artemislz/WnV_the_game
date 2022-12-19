#include "global.h"
#include "map.h"
#include "stable_object.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;
/*Map - Member functions & Constructor*/
map::map(const int& x, const int& y, const char& team) : x(x), y(y), day(true) {
    srand((unsigned int)time(nullptr));
    grid = new map_entity * * [x + 2] ;    // 2 extra lines for the outline
    for (int i = 0; i < x + 2; i++)
        grid[i] = new map_entity * [y + 2];
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {
            grid[i][j] = nullptr;
        }
    }
 
    /*Process of creating the outline of the map*/
    set_outline();

    /*Process of putting in random places lakes and trees*/
    int xx, yy;         // for outputs of function get_random in while loops
    const int num = (double)0.04 * (x * y);        //4% of the positions of the grid
    for (int i = 0; i < num; i++) {
        /*fill with lakes(~)*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != nullptr || (xx == x / 2 + 1 && yy == y / 2 + 1));
        grid[xx][yy] = new stable_object(xx, yy, 'l');

        /*fill with trees(*)*/
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (grid[xx][yy] != nullptr || (xx == x / 2 + 1 && yy == y / 2 + 1));
        grid[xx][yy] = new stable_object(xx, yy, 't');
    }


    /*Process of filling the rest of the grid with earth*/
    for (int i = 1; i < x + 1; i++) {
        for (int j = 1; j < y + 1; j++) {                   //not checking the outline's positions
            if (grid[i][j] == nullptr) {
                grid[i][j] = new stable_object(i, j, 'e');
            }
        }
    }
    return;              // takes team as input for the avatar
}


void map::set_outline() {
    for (int i = 1; i < x + 1; i++) {
        grid[i][0] = new stable_object(i, 0, 's');  // |
        grid[i][y + 1] = new stable_object(i, y + 1, 's');
    }
    for (int j = 0; j < y + 2; j++) {
        grid[0][j] = new stable_object(0, j, 'u');
        grid[x + 1][j] = new stable_object(x + 1, j, 'u');
    };
}


void map::print() {
    if (day == true) {
        cout << "D A Y" << endl;
    }
    else {
        cout << "N I G H T" << endl;
    }
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {
            const char& type = (*grid[i][j]).get_type();
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
            default:
                break;
            }
        	
        }
        cout << endl;
    }
}

void map::change_day() {
    if (day) {
        day = false;
    }
    else {
        day = true;
    }
}

bool map::check_type(const int& i, const int& j) {
    if ((*grid[i][j]).get_type() == 'e' || (*grid[i][j]).get_type() == 'm') {
        return true;
    }
    return false;
}

bool map::check_type(const int& i, const int& j, const char& type) {
	if ((*grid[i][j]).get_type() == type)
	{
		return true;
	}
	return false;
}
void map::place_to_grid(const int& i, const int& j, map_entity* value)
{
    delete grid[i][j];
    grid[i][j] = value;
}

map::~map() {
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {
            //cout << grid[i][j]->get_type();
            if (grid[i][j]->get_type() == 'm' || grid[i][j]->get_type() == 'a') continue;
            delete grid[i][j];
            //cout << endl;
        }
    }
    for (int i = 0; i < x + 2; i++) {
        delete[] grid[i];
    }
    delete grid;
}