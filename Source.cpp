#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "class.h"
#include "globals.h"

using namespace std;


int main()
{
  /*  const int microToSeconds = 1000000;
    const double delay2 = 2 * microToSeconds;     //2 seconds
    while (!_kbhit()) {
    cout << "press sth\n";
    Sleep(500);
    }
    char ch = _getch();
    int key = ch;
    if (key == KEY_UP) {
        cout << "up \n";
    };*/
    int x, y;
    cout << "Enter the dimensions of the map: " << endl;
    cin >> x >> y;

    char team;
    cout << "Time to choose your team...\n" 
         << "Enter V for Vampires and W for Werewolves: \n";
    cin >> team;
    Game game(x, y, team);
    game.get_map().print();        // first print of the cosmos
  //  char k = _getch();
    game.run();
   // Map map = game.get_map();
   // Player player = game.get_player();
    //game.get_map()
   // map.print();
   /* map.update('u');
    Sleep(10);
    system("cls");
    map.update('u');
    */
   /* map.update('u');
    system("cls");
    map.update('u');
    system("cls");

    map.update('u');*/

    /* for(int i = 0; i < map.get_vampires(); i++) {
         cout << "Vampire " << i + 1 << " has: \n" ;
         map.vampire_vector[i].display();
         cout << "Werewolf " << i + 1 << " has:\n";
         map.werewolf_vector[i].display();
     }*/
   //  map.change_day();
     /*int a;
     cout << "Waiting for move..." << endl;
     switch (wParam) {

     }*/
 /*    map.print();
     cout << "waiting for input.. \n";
     char key = _getch();
     player.set_input(key);
     int value = key;
     map.update_avatar(value);*/
   /*  while (map.get_vampires() != 0 && map.get_werewolves() != 0 && value != KEY_X) {
         
     if (value == KEY_X || value == KEY_DOWN || value == ) {
        
         switch (_getch()){
         case KEY_UP:
             map.update(KEY_UP);
             cout << "avatar goes up\n";
             break;
         case KEY_DOWN:
             map.update(KEY_DOWN);
             cout << "avatar goes down\n";
             break;
         case KEY_LEFT:
             map.update(KEY_LEFT);
             cout << "avatar goes left\n";
             break;
         case KEY_RIGHT:
             map.update(KEY_RIGHT);
             cout << "avatar goes right\n";
             break;
         }
         key = _getch();
         value = key;
     }
     system("pause");
     /*map.update('d'); 
     map.update('a');
     map.update('s');
     map.update('w');*/
     //take players input
     //update & print until quit or end of game
    return 0;
}