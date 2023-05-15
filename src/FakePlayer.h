#pragma once
#include "Player.h"
class FakePlayer :
	public Player
{
public:
	void askForPawn(int& pawn_number, int& rolled_dice) override;
	FakePlayer();
	~FakePlayer();
};

