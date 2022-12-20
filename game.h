#pragma once
#include "map.h"
#include "player.h"
#include "avatar.h"
#include "magic_filter.h"
#include "map_entity.h"
#include "werewolf.h"
#include "vampire.h"
#include "team.h"
#include <iostream>   

#define ERROR_CHAR_INPUT 10
#define ERROR_OUT_OF_RANGE 20
#define ERROR_WRONG_TEAM 30
#define ERROR_FLOAT 40

enum KEY { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, X = 88, SPACE = 32, ENTER = 13, F = 70 };
void set_player_preferences(int&, int&, char&);

class game {
	private:
		bool active;					//true-> continue running game, false -> end game 
		map Map;
		player Player;
		avatar Avatar;
		team<vampire> team_vampires;
		team<werewolf> team_werewolves;
		magic_filter Magic_filter;
		char winners_team;				// 'V' -> vampires team		'W' -> werewolves team
	public:
		game(const int&, const int&, const char&);
		void end();
		void pause();                   //calls display_info and returns only if space key is pressed
		void display_info();	
        void display_game_info();
		inline map get_map()const { return Map; }
		inline player get_player()const { return Player; }
		void run();
		void update();
		bool interactions();			// activates the vampires/werewolves interactions(attack/defend/heal) + returns if defence happend
		bool check_for_winner();        //returns true only if a team has won
		
		~game() = default;
};

