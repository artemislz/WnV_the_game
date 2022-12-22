#pragma once
#include "global.h"
#include "map_entity.h"
class map_entity;

class map {
private:
	int x;
	int y;											// (x, y) -> map dimensions
	map_entity*** grid;								//grid with pointers to map_entity objects
public:
	map(const int&, const int&);		
	void print(bool day);									// display map to terminal with appropriate symbols
	inline int get_x()const { return x; }
	inline int get_y()const { return y; }
	inline map_entity* get_grid(const int& i, const int& j)const { return grid[i][j]; }			//returns a specific element of grid
	inline map_entity*** get_grid()const { return grid; }										//returns the whole grid
	void place_to_grid(const int& i, const int& j, map_entity* value);							//place to the position (i,j) of grid the value				
	void set_outline();
	bool check_type(const int& i, const int& j);												//checks if (i, j) is earth or magic_filter (for avatar movement)
	bool check_type(const int& i, const int& j, const char& type);								//returns true if the item in position (i,j) has the requested type
	~map();			
};