#pragma once
#include "map.h"
#include "entity.h"
#include "team.h"
#include "magic_filter.h"
#include <vector>

class Avatar : public Entity {
private:
	int magic_filters;
	char team;
public:
	Avatar(int x, int y, char team, char type = 'a');
	inline void add_filter() { magic_filters++; }
	inline int get_filters()const { return magic_filters; }
	template< typename T> void use_magic_filter(std::vector<T*> teammates);
	void update_avatar(int input, Map& map, Magic_filter& magic_filter);          // update of the grid after player's movement
};


template< typename T>
void Avatar::use_magic_filter(std::vector<T*> teammates) {
	magic_filters -= 10;
	for (auto& teammate : teammates) {
		if ((*teammate).get_health() != 5)
			(*teammate).set_health(5);
	}
}