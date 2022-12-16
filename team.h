#pragma once
#include <vector>
#include "global.h"
#include "map_entity.h"
#include "map.h"


class Map;


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

/*Team - Member functions & Constructors*/
template< typename T>
Team<T>::Team(int x, int y, Map& map) {     // dimensions of the map
	winner = false;
	start_size = x * y / 30;
	place(x, y, map);
}

template< typename T>
void Team<T>::place(int x, int y, Map& map) {
	for (int i = 0; i < start_size; i++) {         // same number of vampires and werewolves at the start of the game
		/*fill with teammates*/
		int xx, yy;
		do {
			xx = get_random(1, x);
			yy = get_random(1, y);
		} while (!map.check_type(xx, yy, 'e'));
		T* w = new T(xx, yy);
		Map_entity* m = w;
		map.get_grid()[xx][yy] = m;
		teammates.push_back(w);
	};
}