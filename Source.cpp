#include "game.h"

int main()
{
    int x , y ;
    std::cout << "Enter the dimensions of the map: " << std::endl;
    std::cin >> x >> y;

    char team ;
    std::cout << "Time to choose your team...\n" 
         << "Enter V for Vampires and W for Werewolves: \n";
    std::cin >> team;
    game game(x, y, team);
    
    game.run();
   
    return 0;
}