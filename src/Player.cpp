#include "Player.h"



Player::Player()
{
	name = "N/A";
	pawn.reserve(4);
}


Player::~Player()
{
}

void Player::move_pawn(int number_of_steps, int pawn_number)
{
	if (pawn_number > 4 || pawn_number < 0) {
		myException e("You tried to move a pawn that doesn't exist.");
		throw(e);
	}
	else
		pawn[pawn_number]->move(number_of_steps);
}

void Player::namePlayer()
{
	std::cout << "Enter your name" << std::endl;
	std::cin >> name;
}

std::string Player::getName()
{
	return name;
}

void Player::assignPawn(Pawn &new_pawn, int pawn_number)
{
	pawn.push_back(&new_pawn);
	pawn[pawn_number]->setPlayer(this->number);
}

void Player::setPawnsSymbol(char new_symbol)
{
	for (int i = 0; i < 4; ++i) {
		pawn[i]->setSymbol(new_symbol);
	}
}

void Player::setPawnsPosition(int new_position, int pawn_number)
{
	pawn[pawn_number]->setPosition(new_position);
}

void Player::setNumber(int new_number)
{
	number = new_number;
}

void Player::setOut(int pawn_number, bool mode)
{
	pawn[pawn_number]->setOut(mode);
}

void Player::setHome(int pawn_number, bool mode)
{
	pawn[pawn_number]->setHome(mode);
}

bool Player::isOut(int pawn_number)
{
	if (pawn_number > 3 || pawn_number < 0) {
		myException e("You tried to move a pawn that doesn't exist.");
		throw(e);
	}
	else
		return pawn[pawn_number]->getOut();
}

bool Player::isHome(int pawn_number)
{
	return pawn[pawn_number]->isHome();
}

Pawn * Player::getPawn(int pawn_number)
{
	return pawn[pawn_number];
}

int Player::getNumber()
{
	return number;
}

int Player::getPosition(int pawn_number)
{
	return pawn[pawn_number]->getPosition();
}

int Player::getSteps(int pawn_number)
{
	return pawn[pawn_number]->getSteps();
}

int Player::throwDice(Dice& dice)
{
	return dice.throwADice();
}

void Player::askForPawn(int & pawn_number, int & rolled_dice)
{
	std::cout << this->getName() << " rolled " << rolled_dice << std::endl << "Pawn to move: " << std::endl;
	std::cin >> pawn_number;
	std::cin.clear();
	std::cin.ignore(256, '\n');
}

char Player::getSymbol(int pawn_number)
{
	return pawn[pawn_number]->getSymbol();
}
