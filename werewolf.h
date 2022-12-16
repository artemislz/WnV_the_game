#pragma once
#include "fighter.h"
#include <vector>

class Werewolf : public Fighter {
	std::vector<Werewolf*>* ptr;
public:
	Werewolf(int i, int j, char type = 'w');
	void set_pointer_to_teammates(std::vector<Werewolf*>& teammates) { ptr = &teammates; };
	inline std::vector<Werewolf*>* get_pointer_to_teammates()const { return ptr; }
};

