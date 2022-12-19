#include "compare.h"
#include "vampire.h"
#include "werewolf.h"
#include <iostream>

// constructor of compare_vampires struct initialize the key
// that is searched in the vector (k)
compare_vampires::compare_vampires(vampire* const& i) : k(i) {};


// compares the vampire that k points to(key searched) with the vampire 
// the pointer passed in its arguments points to (i)
bool compare_vampires::operator()(vampire* const& i) {
    return (i->get_i() == k->get_i()) && (i->get_j() == k->get_j());
}

// constructor of compare_werewolves initialize 
// the key that is searched in the vector
compare_werewolves::compare_werewolves(werewolf* const& i) : k(i) {};

// compares the werewolf that k points to(key searched) with the werewolf
// the pointer passed in its arguments points to (i)
bool compare_werewolves::operator()(werewolf* const& i) {					
	return (i->get_i() == k->get_i()) && (i->get_j() == k->get_j());
}

