#pragma once
#include <vector>
#include "global.h"
#include "map_entity.h"
#include "map.h"
#include <iostream>

/* use of template class because it's the same procedure
applied on other data types depends on the fighter type
of team's instances
->defined in header file because it's template*/

template< class T>
class  team {
private:
	std::vector<T*> teammates;			//vector that includes all the instances of the team
	int start_number_of_teammates;		// by agreement it's x*y/30 x,y: map dimensions
public:
	team(map& Map);
	void place_teammates_to_grid(int x, int y, map& Map);
	inline int teammates_alive()const { return teammates.size(); }
	inline std::vector<T*>& get_teammates() { return teammates; }
	void set_all_unchecked();
	void display_team();
	~team() = default;
};

/*Team - Member functions & Constructors*/
template< typename T>
team<T>::team(map& Map) {     // x, y -> dimensions of the map
	int x = Map.get_x();
	int y = Map.get_y();
	start_number_of_teammates= x * y / 30;
	place_teammates_to_grid(x, y, Map);
}

template< typename T>
void team<T>::place_teammates_to_grid(int x, int y, map& Map) {
	for (int i = 0; i < start_number_of_teammates; i++) {         // same number of vampires and werewolves at the start of the game
		/*fill grid with teammates*/
		int xx, yy;
		do {
			xx = get_random(1, x);
			yy = get_random(1, y);
		} while (!Map.check_type(xx, yy, 'e')|| (xx == Map.get_x() / 2 + 1 && yy == Map.get_y() / 2 + 1));		// skip the avatar's position, which is 
																												//at the centre of the grid by agreement
		T* w = new T(xx, yy);				// create of fighters
		w->set_pointer_to_teammates(teammates);		// every fighter points to its teammates
		map_entity* m = w;
		Map.place_to_grid(xx, yy, m);
		teammates.push_back(w);
	};
}

template< typename T>					// it sets the teammates as unchecked
void team<T>::set_all_unchecked() {		// it's called after every update of the game in order to make them interact to the next frame
	for(auto & element : teammates){
		if (!element->is_checked())
			continue;
		(*element).set_checked();
	}
}

template< typename T>
void team<T>::display_team(){
	std::cout << std::endl;	
	for (auto & element : teammates){
		element->display();
		std::cout << std::endl;
	}
}