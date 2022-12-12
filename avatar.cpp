#include "globals.h"
#include "class.h"

/*Avatar - Member functions & Constructor*/
Avatar::Avatar(int i, int j, char team, char type) : Entity(i, j, type), magic_filters(1) {
    this->team = team;
}

void Avatar::update_avatar(int input, Map& map, Magic_filter& magic_filter) {       // called when player press a button that moves the avatar
    static int calls = 0;
    char type;
    calls++;
    Map_entity*** grid = map.get_grid();
    //  cout << x << " " << y << endl;
    switch (input) {
    case KEY_UP:
        if (map.check_type(i - 1, j)) {
            move(1);
            if (map.check_type(i - 1, j, 'm')) {
                Map_entity* p = grid[i - 1][j];         //old position of magic filter
                swap(grid[i - 1][j], grid[i][j]);
                add_filter();
                magic_filter.change_position(p, i, j, map);
            }
            else {
                swap(grid[i][j], grid[i - 1][j]);
            }
            break;
        }
    case KEY_DOWN:
        if (map.check_type(i + 1, j)) {
            move(2);                             //move down
            if (map.check_type(i + 1, j, 'm')) {
                Map_entity* p = grid[i + 1][j];         //old position of magic filter
                swap(grid[i + 1][j], grid[i][j]);
                add_filter();
                magic_filter.change_position(p, i, j, map);
            }
            else {
                swap(grid[i][j], grid[i + 1][j]);
            }
            break;
        }
    case KEY_LEFT:
        if (map.check_type(i, j - 1)) {
            move(3);                             //move left
            if (map.check_type(i, j - 1, 'm')) {
                Map_entity* p = grid[i][j - 1];         //old position of magic filter
                swap(grid[i][j - 1], grid[i][j]);
                add_filter();
                magic_filter.change_position(p, i, j, map);
            }
            else {
                swap(grid[i][j], grid[i][j - 1]);
            }
            break;
        }
    case KEY_RIGHT:
        if (map.check_type(i, j + 1)) {
            move(4);                             //move right    
            if (map.check_type(i, j + 1, 'm')) {
                Map_entity* p = grid[i][j + 1];         //old position of magic filter
                swap(grid[i][j + 1], grid[i][j]);
                add_filter();
                magic_filter.change_position(p, i, j, map);
            }
            else {
                swap(grid[i][j], grid[i][j + 1]);
            }
            break;
        }
    default:
        break;
    }
    if (calls % 10 == 0)        //change of the weather after 10 avatars moves
        map.change_day();

}