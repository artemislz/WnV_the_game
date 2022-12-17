#include "compare.h"
#include "vampire.h"
#include "werewolf.h"
#include <iostream>

bool compare_vampires::operator()(Vampire* const& i) {
    return (i->get_i() == k->get_i()) && (i->get_j() == k->get_j());
}

bool compare_werewolves::operator()(Werewolf* const& i) {
	return (i->get_i() == k->get_i()) && (i->get_j() == k->get_j());
}