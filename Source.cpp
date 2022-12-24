#include "game.h"
#include "global.h"

using namespace std;


    
int main()
{
    int dim_x, dim_y;
    char team;
    set_player_preferences(dim_x, dim_y, team);
    game Game(dim_x, dim_y, team);
    Game.run();
    return 0;
}