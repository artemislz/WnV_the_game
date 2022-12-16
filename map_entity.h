#pragma once

class Map_entity {
protected:
	int i;
	int j;
	char type;      //a->avatar , v->vampire , w->werewolf , t->trees , l->lakes , m->magic_filter , u->up-down outline , s->side's outline
public:
	Map_entity(int i, int j, char type);
	int get_i() const { return i; }
	int get_j() const { return j; }
	inline char get_type() const { return type; }
	inline void set_type(char t) { type = t; }
	virtual bool is_checked() = 0;
	//virtual void place(Map& map) = 0;
};

