#include "compare.h"
#include "vampire.h"
#include "werewolf.h"
#include <iostream>

compare_vampires::compare_vampires(vampire* const& i) : k(i) {};

bool compare_vampires::operator()(vampire* const& i) {
    return (i->get_i() == k->get_i()) && (i->get_j() == k->get_j());
}

compare_werewolves::compare_werewolves(werewolf* const& i) : k(i) {};


bool compare_werewolves::operator()(werewolf* const& i) {
	return (i->get_i() == k->get_i()) && (i->get_j() == k->get_j());
}
