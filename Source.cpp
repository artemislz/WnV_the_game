#include <iostream>

#include "class.h"
#include "globals.h"
using namespace std;


int main()
{
    int x, y;
    cout << "Enter the dimensions: " << endl;
    cin >> x >> y;

    char team;
    cout << "Time to choose your team...\n" <<
        "Enter V for Vampires and W for Werewolves: \n";
    cin >> team;
    Game game(x, y, team);
    Map map = game.get_map();
    //game.get_map()
    map.print();

    map.update('u');
    system("clear");
    map.update('u');
    system("clear");
    map.update('u');
    system("clear");
    map.update('u');
    system("clear");

    map.update('u');

    /* for(int i = 0; i < map.get_vampires(); i++) {
         cout << "Vampire " << i + 1 << " has: \n" ;
         map.vampire_vector[i].display();
         cout << "Werewolf " << i + 1 << " has:\n";
         map.werewolf_vector[i].display();
     }
     map.change_day();
     map.print();*/

     //take players input
     //update & print until quit or end of game
    return 0;
}