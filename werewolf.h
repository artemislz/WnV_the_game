#pragma once
#include "fighter.h"
#include <vector>

class werewolf : public fighter {
	std::vector<werewolf*>* ptr;
public:
	werewolf(const int& i, const int& j, const char& type = 'w');
	void set_pointer_to_teammates(std::vector<werewolf*>& teammates) { ptr = &teammates; };
	inline std::vector<werewolf*>* get_pointer_to_teammates()const { return ptr; }
	virtual ~werewolf() = default;
	
};

