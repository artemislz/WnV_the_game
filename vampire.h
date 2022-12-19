#pragma once
#include "fighter.h"
#include <vector>
#include <iostream>

class vampire : public fighter {
    std::vector<vampire*>* ptr;             //pointer to its teammates in order to find and erase 
                                            //from vector the fighter when it dies
public:
    vampire(const int& i, const int& j, const char& type = 'v');
    void move(const int& n) override;       // n -> code of move
                                            //declared as override because it overrides 
										    //the pure virtual move() function of entity
                                            //In this way, all the vampires can move diagonally too.

    void set_pointer_to_teammates(std::vector<vampire*>& teammates) { ptr = &teammates; };
    inline std::vector<vampire*>* get_pointer_to_teammates()const { return ptr;}
    virtual ~vampire() = default;           // virtual destructor because it's a derived class
};

