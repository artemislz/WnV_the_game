#pragma once


class Map;
class Player;
class Avatar;
class Werewolf;
class Vampire;
class Magic_filter;
template<class t> class Team;

class Game {
private:
	bool active;  //true -> paused
	Map map;
	Player player;
	Avatar avatar;
	Team<Vampire> team_vampires;
	Team<Werewolf> team_werewolves;
	Magic_filter magic_filter;
	char winners_team;
public:
	Game(int, int, char);
	void end();
	void pause();                   //kalei thn display_info
	void display_info();
	inline Map get_map()const { return map; }
	inline Player get_player()const { return player; }
	void run();
	void update();
	void interactions();
	bool check_for_winner();        // YES -> END
};