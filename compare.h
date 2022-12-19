#pragma once
#include "vampire.h"
#include "werewolf.h"

/* struct used to compare vampires for the search in their teammates vector */

struct compare_vampires {
    vampire* k;
    compare_vampires(vampire* const& i);                // gets as argument a pointer to the vampire we want find_if() to find
    bool operator()(vampire* const& i);                 // overload of () operator to be used as compare function for the "find_if" of vector
};


/* struct used to compare werewolves for the search in their teammates vector */

struct compare_werewolves {
    werewolf* k;
    compare_werewolves(werewolf* const& i);           // gets as argument a pointer to the werewolf we want "find_if()"" to find
    bool operator()(werewolf* const& i);              // overload of () operator to be used as compare function for the "find_if" of vector 
};

//------------------sources------------------//
//https://iq.opengenus.org/find-element-in-vector-cpp-stl/
//https://stackoverflow.com/questions/50450373/how-do-i-define-a-unary-predicate-for-copy-if-etc-in-c-/