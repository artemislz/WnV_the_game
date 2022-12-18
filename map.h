#pragma once
#include "global.h"
#include "map_entity.h"
class map_entity;

class map {
private:
	int x;
	int y;      // (x, y) - > map dimensions
	bool day;   // false -> night  true -> day
	friend int get_random(const int&, const int&);
	map_entity*** grid;
public:
	map(const int&, const int&, const char&);    // map constructor
	~map();
	void print();                      // display map to terminal
	//void put_magic_filter(Magic_filter* p, int, int);          //takes the old coordinates of avatar
	inline int get_x()const { return x; }
	inline int get_y()const { return y; }
	inline bool get_day()const { return day; }
	inline map_entity* get_grid(const int& i, const int& j)const { return grid[i][j]; }
	inline map_entity*** get_grid()const { return grid; }
	void place_to_grid(const int& i, const int& j, map_entity* value);
	void change_day();
	void set_outline();
	bool check_type(const int& i, const int& j);      //checks if (i, j) is earth or magic_filter
	bool check_type(const int& i, const int& j, const char& type);
};