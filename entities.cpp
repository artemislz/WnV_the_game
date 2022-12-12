#include "globals.h"
#include "class.h"

using namespace std;

//global functions
int get_random(int a, int b) {
	return a + rand() % (b - a + 1);
}

/*Team - Member functions & Constructors*/
template< typename T> Team<T>::Team(int x, int y, Map& map) {     // dimensions of the map
    winner = false;
    start_size = x * y / 30;
    place(x, y, map);
}

template< typename T> void Team<T>::place(int x,int y, Map& map) {
    for (int i = 0; i < start_size; i++) {         // same number of vampires and werewolves at the start of the game
        /*fill with teammates*/
        int xx, yy;
        do {
            xx = get_random(1, x);
            yy = get_random(1, y);
        } while (!map.check_type(xx, yy, 'e'));
        T* v = new T(xx, yy);
        Map_entity* m = v;
        map.place_to_grid(xx, yy, m);
        teammates.push_back(*v);
    };
}

/*Map Entity - Member functions & Constructor*/
Map_entity::Map_entity(int i, int j, char type) {
    this->i = i;
    this->j = j;
    this->type = type;
}

/*Stable_objects - Constructor*/
Stable_object::Stable_object(int i, int j, char type) : Map_entity(i,j,type) {}

/*Entity - Member functions & constructors*/
Entity::Entity(int i, int j, char type) : Map_entity(i, j, type) {}

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
    cout << "\thealth" << health << endl;
}

/*template <typename T> void Fighter::give_heal(T& teammate) {
    else {
        int max_health = max(health1, health2);
        if (max_health == health1) {
            num = get_random(0, 1);
            if (num) {
                vamptr1->
            }
            else continue;
        }
    }
}*/

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
    case 7:         //down_right
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
Magic_filter::Magic_filter(int x , int y) : Map_entity(x, y ,'m') {};

void Magic_filter::setup(int i, int j){
    this->i = i;
    this->j = j;
}

void Magic_filter:: change_position(Map_entity* p,int old_i, int old_j, Map& map){
	int xx, yy;
    Map_entity*** grid = map.get_grid();
	do {
		xx = get_random(0, map.get_x() + 1);
		yy = get_random(0, map.get_y() + 1);
	} while (!map.check_type(xx, yy, 'e'));
	swap(grid[xx][yy], grid[old_i][old_j]);     //swap the old position of avatar with earth
	map.place_to_grid(xx, yy, p);               //object of magic filter
}