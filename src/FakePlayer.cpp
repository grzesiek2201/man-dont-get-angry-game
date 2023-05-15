#include "FakePlayer.h"



void FakePlayer::askForPawn(int & pawn_number, int & rolled_dice)
{
	//first get out of the base
	if (rolled_dice == 6) {
		for (int i = 0; i < 4; ++i) {
			if (!pawn[i]->getOut()) {
				pawn_number = i + 1;
				break;
			}
		}
	}
	else {
		//secondly choose the pawn that are not in home
		int free_pawns = 0;
		for (int i = 0; i < 4; ++i) {
			if (pawn[i]->getOut()) {
				free_pawns++;
				if (!pawn[i]->isHome()) {
					pawn_number = i + 1;
					break;
				}
				else
					free_pawns--;
			}
		}
		if (free_pawns == 0) {
			for (int i = 0; i < 4; ++i) {
				if (pawn[i]->getOut()) {
					pawn_number = i + 1;
				}
			}
		}
	}
}

FakePlayer::FakePlayer()
{
}


FakePlayer::~FakePlayer()
{
}
