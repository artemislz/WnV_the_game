
#include "entity.h"



/*Entity - Member functions & constructors*/
Entity::Entity(int i, int j, char type) : Map_entity(i, j, type), checked(false) {}

/*inline int Map_entity::get_i() const { return i; }
inline int Map_entity::get_j() const { return j; }
inline char Map_entity::get_type() const { return type; }
inline void Map_entity::set_type(char t) { type = t; }*/

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





