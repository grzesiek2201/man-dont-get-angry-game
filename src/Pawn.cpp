#include "Pawn.h"



Pawn::Pawn()
	:symbol('-'), position(-100), out(false), steps_made(0), number(0), player(-1)
{
}


Pawn::~Pawn()
{
}

void Pawn::move(int number_of_steps)
{
	if (position + number_of_steps < board_length) {
		position += number_of_steps;
	}
	else {
		int remains = ((position + number_of_steps) % board_length);
		position = remains;
	}
	steps_made += number_of_steps;
	if (steps_made > (board_length - 1)) {
		position = -10;
	}
}

void Pawn::setPlayer(int player_number)
{
	player = player_number;
}

void Pawn::setSymbol(char new_symbol)
{
	symbol = new_symbol;
}

void Pawn::setPosition(int new_position)
{
	position = new_position;
}

void Pawn::setOut(bool mode)
{
	out = mode;
}

void Pawn::setHome(bool mode)
{
	home = mode;
}

char Pawn::getSymbol()
{
	return symbol;
}

int Pawn::getPosition()
{
	return position;
}

int Pawn::getSteps()
{
	return steps_made;
}

int Pawn::getPlayer()
{
	return player;
}

