#include "global.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

int get_random(const int& a, const int& b)
{
	return a + rand() % (b - a + 1);
}

void set_player_preferences(int& dim_x, int& dim_y, char& team) {
	bool repeat;
	repeat = true;
	while (repeat) {
		try {
			string x;
			string y;
			cout << "Enter the dimensions of the map: " << endl;
			cin >> x;
			cin >> y;
			//cout << "x = " << x << endl;
			//cout << "y = " << y << endl;
			if (x.length() > 3 || y.length() > 3) {
				throw(ERROR_CHAR_INPUT);
			}
			for (int i = 0; i < x.length(); i++) {
				if (!isdigit(x[i])) {
					throw(ERROR_CHAR_INPUT);
				}
			}
			for (int i = 0; i < y.length(); i++) {
				if (!isdigit(y[i])) {
					throw(ERROR_CHAR_INPUT);
				}
			}
			dim_x = stoi(x);
			dim_y = stoi(y);
			if (dim_x < 10 || dim_y < 10 || dim_x > 30 || dim_y > 30) {
				throw(ERROR_OUT_OF_RANGE);
			}
			repeat = false;
		}

		catch (int n) {
			switch (n) {
			case(ERROR_OUT_OF_RANGE):
				cout << "Dimensions out of range...\n"
					<< "Reminder x and y must from 10 to 30 "
					<< "Please try again.\n";
				break;

			case(ERROR_CHAR_INPUT):
				cout << "Characters are not allowed...\n"
					<< "Please try again.\n";
				break;
			}
			repeat = true;
		}
	}
	repeat = true;
	while (repeat) {
		try {
			cout << "Time to choose your team...\n"
				<< "Enter V for Vampires and W for Werewolves: \n";
			cin >> team;
			if (team != 'V' || team != 'W') {
				throw(ERROR_WRONG_TEAM);
			}
			repeat = false;
		}
		catch (int n) {
			cout << "The team you entered doesn't match with 'V' or 'W'\n"
				<< "Please try again.\n";
			repeat = true;
		}
	}
}