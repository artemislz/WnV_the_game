#pragma once
#include "map.h"
#include "player.h"
#include "avatar.h"
#include "magic_filter.h"
#include "map_entity.h"
#include "werewolf.h"
#include "vampire.h"
#include "team.h"


class game {
private:
	bool active;  //true -> paused
	map Map;
	player Player;
	avatar Avatar;
	team<vampire> team_vampires;
	team<werewolf> team_werewolves;
	magic_filter Magic_filter;
	char winners_team;
public:
	game(const int&, const int&, const char&);
	void end();
	void pause();                   //kalei thn display_info
	void display_info();
	inline map get_map()const { return Map; }
	inline player get_player()const { return Player; }
	void run();
	void update();
	void interactions();
	bool check_for_winner();        // YES -> END
	~game() {std::cout << "destruct"; };
};