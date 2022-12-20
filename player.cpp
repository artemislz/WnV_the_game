#include <conio.h>
#include "player.h"


/* Player - Member functions & Constructor */
player::player(const char& team) {        
    this->team = team;
    this->input = team;
}

/* takes the player input and converts it to the corresponding key code */
void player::set_input() {
    char key = _getch();
    input = key;
}

