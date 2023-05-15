#pragma once
#include <string>
#include <iostream>
#include "Pawn.h"
#include "Dice.h"
#include "myException.h"
#include <vector>

class Player
{
protected:
	std::string name;
	std::vector<Pawn*> pawn;		//**VECTORS**
	int number;
public:
	Player();
	~Player();
	void move_pawn(int number_of_steps, int pawn_number);//add exceptions handling
	void namePlayer();
	std::string getName();
	void assignPawn(Pawn &new_pawn, int pawn_number);
	void setPawnsSymbol(char new_symbol);
	void setPawnsPosition(int new_position, int pawn_number);
	void setNumber(int new_number);
	void setOut(int pawn_number, bool mode);
	void setHome(int pawn_number, bool mode);
	bool isOut(int pawn_number);
	bool isHome(int pawn_number);
	Pawn* getPawn(int pawn_number);
	int getNumber();
	int getPosition(int pawn_number);
	int getSteps(int pawn_number);
	char getSymbol(int pawn_number);
	int throwDice(Dice& dice);
	virtual void askForPawn(int& pawn_number, int& rolled_dice);

};

