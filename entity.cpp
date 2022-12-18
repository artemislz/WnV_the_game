﻿
#include "entity.h"



/*Entity - Member functions & constructors*/
entity::entity(const int& i, const int& j, const char type) : map_entity(i, j, type) {
    if (type == 'a')
        checked = true;
    else {
        checked = false;
    }
}


void entity::move(const int& n) {
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





