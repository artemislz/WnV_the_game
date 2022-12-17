#pragma once
#include "vampire.h"
#include "werewolf.h"

struct compare_vampires {
    Vampire* k;
    compare_vampires(Vampire* const& i) : k(i) {}
    bool operator()(Vampire* const& i);
};

struct compare_werewolves {
    Werewolf* k;
    compare_werewolves(Werewolf* const& i) : k(i) {}
    bool operator()( Werewolf* const& i);
};

