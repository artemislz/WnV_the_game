#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "class.h"
#include "globals.h"


using namespace std;


int main()
{
    int x = 25, y = 25;
  //  cout << "Enter the dimensions of the map: " << endl;
    //cin >> x >> y;

    char team = 'V';
 //   cout << "Time to choose your team...\n" 
 //        << "Enter V for Vampires and W for Werewolves: \n";
 //   cin >> team;
    Game game(x, y, team);
    game.get_map().print();        // first print of the cosmos
    game.run();
   
    
    return 0;
}