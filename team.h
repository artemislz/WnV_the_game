#pragma once
#include <vector>
#include "global.h"
#include "map_entity.h"
#include "map.h"
#include <iostream>
//#include "avatar.h"
#include<vector>
template< class T>
class  team {
private:
	std::vector<T*> teammates;
	bool winner;       // true -> won false -> lose
	int start_size;
public:
	team(int x, int y, map& Map);
	void place(int x, int y, map& Map);
	inline int number()const { return teammates.size(); }
	inline std::vector<T*>& get_teammates() { return teammates; }
	void set_all_unchecked();
	~team() { std::cout << "Destructing team"; }
	// friend void place(Map& map, Team& team);
};

/*Team - Member functions & Constructors*/
template< typename T>
team<T>::team(int x, int y, map& Map) {     // dimensions of the map
	winner = false;
	start_size = x * y / 30;
	place(x, y, Map);
}

template< typename T>
void team<T>::place(int x, int y, map& Map) {
	for (int i = 0; i < start_size; i++) {         // same number of vampires and werewolves at the start of the game
		/*fill with teammates*/
		int xx, yy;
		do {
			xx = get_random(1, x);
			yy = get_random(1, y);
		} while (!Map.check_type(xx, yy, 'e')|| (xx == Map.get_x() / 2 + 1 && yy == Map.get_y() / 2 + 1));
		T* w = new T(xx, yy);
		w->set_pointer_to_teammates(teammates);
		map_entity* m = w;
		Map.place_to_grid(xx, yy, m);
	//	Map.get_grid()[xx][yy] = m;
		teammates.push_back(w);
	};
}

template< typename T>
void team<T>::set_all_unchecked() {
	for(auto & element : teammates){
		if (!element->is_checked())
			continue;
		(*element).set_checked();
	}
}
