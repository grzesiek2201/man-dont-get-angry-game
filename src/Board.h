#pragma once
#include "Player.h"
#include "FakePlayer.h"
#include "Map.h"

class Board
{
private:
	char squares[board_length];
	char board[coordinate_length][coordinate_length];
	int home[4][4] = { 0 };
	bool out[4] = { false };
	//Pawn *pawn_board[board_length] = { 0 };
	Map map;
	Player **players;		//**MEMORY MANAGEMENT** **POLYMORPHISM**
	Pawn *pawns;
	Dice dice;
	void movePawn(int active_player, int rolled_dice, int pawn_number, bool& end_of_game);
	//void askWhichPawnToMove(int& pawn_number, int rolled_dice);
	void nextPlayer(int& active_player);
	void moveOutOfBase(int active_player, int pawn_number);
	void checkHome(int active_player, int pawn_number, bool& end_of_game);
	bool checkMove(int active_player, int rolled_dice, int pawn_number);
	void updateTheBoard();
public:
	Board();
	~Board();
	void readyGame();
	void play();
	void showPlayer();
	void showBoard();
};

