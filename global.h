#pragma once
/*define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_X 88			//x
#define KEY_SPACE 32
#define KEY_ENTER 13
#define KEY_F 70*/
#define ERROR_CHAR_INPUT 10
#define ERROR_OUT_OF_RANGE 20
#define ERROR_WRONG_TEAM 30

enum KEY { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, X = 88, SPACE = 32, ENTER = 13, F = 70 };

int get_random(const int&, const int&);
void set_player_preferences(int&, int&, char&);
/*#include <iostream>

#include <cstdlib>
#include <time.h>
#include <vector>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <algorithm>
#include <execution>

using namespace std;*/