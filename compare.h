#pragma once
#include "vampire.h"
#include "werewolf.h"

struct compare_vampires {
    vampire* k;
    compare_vampires(vampire* const& i);
    bool operator()(vampire* const& i);
};

struct compare_werewolves {
    werewolf* k;
    compare_werewolves(werewolf* const& i);


    bool operator()( werewolf* const& i);
};

