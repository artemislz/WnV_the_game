#pragma once
#include <vector>
#include "global.h"
#include "map_entity.h"
#include "map.h"
//#include "avatar.h"
#include<vector>
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
	void set_all_unckecked();
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
		w->set_pointer_to_teammates(teammates);
		Map_entity* m = w;
		map.get_grid()[xx][yy] = m;
		teammates.push_back(w);
	};
}

template< typename T>
void Team<T>::set_all_unckecked(){
	for(auto & element : teammates){
		if (!element->is_checked())
			continue;
		(*element).set_checked();
	}
}
/*
template< class T>
class Avatar : public Entity {
private:
	int magic_filters;
	char team;
public:
	Avatar(int x, int y, char team, char type = 'a');
	inline void add_filter() { magic_filters++; }
	inline int get_filters()const { return magic_filters; }
	void use_magic_filter(vector<T*> teammates);
	void update_avatar(int input, Map& map, Magic_filter& magic_filter);          // update of the grid after player's movement
};


template< typename T>
void Avatar<T>::use_magic_filter(std::vector<T*> teammates) {
	// teammates = team.get_teammates();
	for (auto& teammate : teammates) {
		if ((*teammate).get_health() != 5)
			(*teammate).set_health(5);
	}
}*/