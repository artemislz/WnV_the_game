#include "global.h"
#include "map.h"
#include "stable_object.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
using namespace std;
/*Map - Member functions & Constructor*/
map::map(const int& x, const int& y) : x(x), y(y) {

    srand((unsigned int)time(nullptr));

    grid = new map_entity * * [x + 2] ;                         // allocate 2 extra lines for the up and down outline
    for (int i = 0; i < x + 2; i++)
        grid[i] = new map_entity * [y + 2];                     // allocate 2 extra lines for the right and left outline
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {                     
            grid[i][j] = nullptr;                               // initialize all grid to null                               
        }
    }
 
    /*Process of creating the outline of the map*/
    set_outline();

    /*Process of putting in random places lakes and trees*/
    int xx, yy;                                             // for outputs of function get_random in while loops
    const int num = (double)0.04 * (x * y);                 //4% of the positions of the grid filled with obstacles
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
    return;              
}


void map::set_outline() {
    for (int i = 1; i < x + 1; i++) {
        /* left - right outline */
        grid[i][0] = new stable_object(i, 0, 's');              
        grid[i][y + 1] = new stable_object(i, y + 1, 's');
    }
    for (int j = 0; j < y + 2; j++) {
        /* up - down outline */
        grid[0][j] = new stable_object(0, j, 'u');
        grid[x + 1][j] = new stable_object(x + 1, j, 'u');
    };
}


void map::print(bool day){ 
    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (day == true) {
        SetConsoleTextAttribute(h, 14);
        cout << "\t\t\tD A Y" << endl;
    }
    else {
        SetConsoleTextAttribute(h, 1);
        cout << "\t\t\tN I G H T" << endl;
    }

    /* according to the type of map entity prints the 
     appropriate symbol */
    for (int i = 0; i < x + 2; i++) {
        cout << "\t\t\t";
        for (int j = 0; j < y + 2; j++) {
            const char& type = (*grid[i][j]).get_type();
            cout << ' ';
            switch (type) {
            case 'u':
               // system("Color 04");
                SetConsoleTextAttribute(h, 15);
                cout << '-';
                break;
            case 's':
                SetConsoleTextAttribute(h, 15);
                cout << '|';
                break;
            case 'e':
                SetConsoleTextAttribute(h, 0);
                cout << ' ';
                break;
            case 'a':
               // system("Color 04");
                SetConsoleTextAttribute(h, 14);
                cout << "A";
                break;
            case 'v':
                SetConsoleTextAttribute(h, 12);
                cout << 'v';
                break;
            case 'w':
                SetConsoleTextAttribute(h, 9);
                cout << 'w';
                break;
            case 'l':
                SetConsoleTextAttribute(h, 11);
                cout << '~';
                break;
            case 't':
                SetConsoleTextAttribute(h, 10);
                cout << '*';
                break;
            case 'm':
                SetConsoleTextAttribute(h, 13);
                cout << 'm';
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
}

bool map::check_type(const int& i, const int& j) {                              //specific operation for avatar's movements
    if ((*grid[i][j]).get_type() == 'e' || (*grid[i][j]).get_type() == 'm') {
        return true;
    }
    return false;
}

bool map::check_type(const int& i, const int& j, const char& type) {        // used for understanding what it's in a specfic grid's position
	if ((*grid[i][j]).get_type() == type)
	{
		return true;
	}
	return false;
}

void map::place_to_grid(const int& i, const int& j, map_entity* value)          // place the value to a specific position in the grid 
{                                                                               // and delete the previous object that grid[i][j] pointed to
    delete grid[i][j];
    grid[i][j] = value;
}

map::~map() {
    // Deallocation of memory which allocated dynamically 
    // to avoid memory leaks 
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < y + 2; j++) {
            if (grid[i][j]->get_type() == 'm' || grid[i][j]->get_type() == 'a') continue;
            delete grid[i][j];
        }
    }
    for (int i = 0; i < x + 2; i++) {
        delete[] grid[i];
    }
    delete grid;
}