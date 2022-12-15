#include "vampire.h"

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