#pragma once
#include <iostream>
class map_entity {
protected:
	int i;
	int j;
	char type;      //a->avatar , v->vampire , w->werewolf , t->trees , l->lakes , m->magic_filter , u->up-down outline , s->side's outline
public:
	map_entity(const int&, const int&, const char&);
	inline int get_i() const { return i; }
	inline int get_j() const { return j; }
	inline char get_type() const { return type; }
	inline void set_type(const char& t) { type = t; }
	virtual bool is_checked() = 0;
	//virtual void place(Map& map) = 0;
	virtual ~map_entity() { std::cout << "map_entity"; }
};

