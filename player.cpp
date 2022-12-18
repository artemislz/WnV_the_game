#include <conio.h>
#include "player.h"


/*Player - Member functions & Constructor*/
player::player(const char& team) {         // IF NO W OR V APOSFALMATWSH
    this->team = team;
    this->input = team;
}

void player::set_input() {
    char key = _getch();
    input = key;
}

