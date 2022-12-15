#include "entity.h"
#include "globals.h"

class Map {
private:
	int x;
	int y;      // (x, y) - > map dimensions
	bool day;   // false -> night  true -> day
	int werewolves; // count of werewolves alive
	friend int get_random(int, int);
	Map_entity*** grid;
public:
	Map(int x, int y, char team);    // map constructor
	void print();                      // display map to terminal
	//void put_magic_filter(Magic_filter* p, int, int);          //takes the old coordinates of avatar
	inline int get_x()const { return x; }
	inline int get_y()const { return y; }
	inline bool get_day()const { return day; }
	inline Map_entity* get_grid(int i, int j)const { return grid[i][j]; }
	inline Map_entity*** get_grid()const { return grid; }
	inline void place_to_grid(int i, int j, Map_entity*& value) { grid[i][j] = value; }
	void change_day();
	void set_outline();
	bool check_type(int, int);      //checks if (i, j) is earth or magic_filter
	bool check_type(int, int, char);
};