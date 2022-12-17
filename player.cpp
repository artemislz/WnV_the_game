#include <conio.h>
#include "player.h"


/*Player - Member functions & Constructor*/
Player::Player(char team) {         // IF NO W OR V APOSFALMATWSH
    this->team = team;
    this->input = team;
}

void Player::set_input() {
    char key = _getch();
    input = key;
}

