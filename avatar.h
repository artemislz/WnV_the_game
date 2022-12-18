#pragma once
#include "map.h"
#include "entity.h"
#include "team.h"
#include "magic_filter.h"
#include <vector>

class avatar : public entity {
private:
	int magic_filters;
	char team;
public:
	avatar(const int&, const int&, const char&, const char type = 'a');
	inline void add_filter() { magic_filters++; }
	inline int get_filters()const { return magic_filters; }
	template< typename T> void use_magic_filter(std::vector<T*>& teammates);
	void move(int input, map& map, magic_filter& magic_filter);          // update of the grid after player's movement
	
};


template< typename T>
void avatar::use_magic_filter(std::vector<T*>& teammates) {
	magic_filters -= 10;
	for (auto& teammate : teammates) {
		if ((*teammate).get_health() != teammate->get_max_health())
			(*teammate).set_health(5);
	}
}