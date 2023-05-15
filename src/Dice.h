#pragma once
#include <time.h>

class Dice
{
public:
	Dice() {};
	~Dice() {};
	int throwADice() {
		srand(time(NULL));
		return ((rand() % 6) + 1);
	}
};

