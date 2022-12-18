#include "global.h"
#include <cstdlib>

int get_random(const int& a, const int& b)
{
	return a + rand() % (b - a + 1);
}
