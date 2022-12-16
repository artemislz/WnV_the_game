#include "game.h"

int main()
{
    int x = 30, y = 30;
  //  cout << "Enter the dimensions of the map: " << endl;
    //cin >> x >> y;

    char team = 'V';
 //   cout << "Time to choose your team...\n" 
 //        << "Enter V for Vampires and W for Werewolves: \n";
 //   cin >> team;
    Game game(x, y, team);
    
    game.run();
   
    return 0;
}