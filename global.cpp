#include "global.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

// returns a random integer between [a,b]
int get_random(const int& a, const int& b)
{
	return a + rand() % (b - a + 1);
}

