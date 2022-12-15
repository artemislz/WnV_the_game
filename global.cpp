#include "global.h"
#include <cstdlib>

int get_random(int a, int b) {
	return a + rand() % (b - a + 1);
}
