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

//_getch() -> https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch?view=msvc-170
 //key scan codes -> https://learn.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-6.0/aa299374(v=vs.60)