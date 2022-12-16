#pragma once
#include "fighter.h"
#include <vector>
#include <iostream>

class Vampire : public Fighter {
    std::vector<Vampire*>* ptr;
public:
    Vampire(int i, int j, char type = 'v');
    void move(int n);       // n-> possible movements
    //void attack(WereWolves& ememy);
  //  void set_pointer_to_teammates(std::vector<Vampire*>& teammates) { ptr = &teammates; };
 //   inline std::vector<Vampire*>* get_pointer_to_teammates()const { return ptr;}
};
