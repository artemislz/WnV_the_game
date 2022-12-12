#include "globals.h"
#include "class.h"


/*Player - Member functions & Constructor*/
Player::Player(char team) {         // IF NO W OR V APOSFALMATWSH
    this->team = team;
}

void Player::set_input() {
    char key = _getch();
    input = key;
}