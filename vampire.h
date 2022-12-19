#pragma once
#include "fighter.h"
#include <vector>
#include <iostream>

class vampire : public fighter {
    std::vector<vampire*>* ptr;
public:
    vampire(const int& i, const int& j, const char& type = 'v');
    void move(const int& n) override;       // n-> possible movements
   // void attack(WereWolves& ememy);
    void set_pointer_to_teammates(std::vector<vampire*>& teammates) { ptr = &teammates; };
    inline std::vector<vampire*>* get_pointer_to_teammates()const { return ptr;}
    virtual ~vampire() { std::cout << "vampire "; }
};
