#pragma once
#include "map.h"
#include "entity.h"
#include "team.h"
#include "magic_filter.h"
#include "fighter.h"
#include <vector>
#include <iostream>

class avatar : public entity {
private:
	int magic_filters;
	char team;
public:
	avatar(const int&, const int&, const char&, const char type = 'a');
	inline void add_filter() { magic_filters++; }
	inline int get_filters()const { return magic_filters; }
	template< typename T> void use_magic_filter(std::vector<T*>& teammates);	
	bool move(int input, map& Map);         // update of the grid after player's movement || returns true if avatar catched the magic filter and false otherwise
	virtual ~avatar() = default;			// virtual destructor because it's a derived class
};

/*use of template function because it's the same procedure
applied on other data type depends on the team avatar supports*/
//defined in header file because it's template
template< typename T>				
void avatar::use_magic_filter(std::vector<T*>& teammates) {
	magic_filters -= 10;					// by aggrement the avatar in order to heal his/her teammates are required and used 10 magic filters
	for (auto& teammate : teammates) {
		if ((*teammate).get_health() != MAX_HEALTH)
			(*teammate).set_health(MAX_HEALTH);
	}
}