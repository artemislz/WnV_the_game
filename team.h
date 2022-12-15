#pragma once
#include <vector>
#include "entity.h"
#include "map.h"

template< class T>
class  Team {
private:
	std::vector<T*> teammates;
	bool winner;       // true -> won false -> lose
	int start_size;
public:
	Team(int x, int y, Map& map);
	void place(int x, int y, Map& map);
	inline int number()const { return teammates.size(); }
	inline std::vector<T*> get_teammates() { return teammates; }
	// friend void place(Map& map, Team& team);
};