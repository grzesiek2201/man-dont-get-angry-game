#include "Board.h"

#define number_of_players 4

void Board::movePawn(int active_player, int rolled_dice, int pawn_number, bool& end_of_game)
{
	if (checkMove(active_player, rolled_dice, pawn_number)) {
		//if pawn is in home, first remove it from home, then put it in a new square (also for the display)
		if (players[active_player]->isHome(pawn_number - 1)) {
			for (int i = 0; i < 4; ++i) {
				if (home[active_player][i] == pawn_number) {
					home[active_player][i] = 0;
				}
			}
		}
		try {		//**EXCEPTION HANDLING**
			//remove the pawn from it's current position
			squares[players[active_player]->getPosition(pawn_number - 1)] = '-';
			//move active player's pawn
			players[active_player]->move_pawn(rolled_dice, pawn_number - 1);
			updateTheBoard();
			std::cout << "Pawn number " << pawn_number << " has been moved by " << rolled_dice << " squares" << std::endl << std::endl;
		}
		catch (const myException& e) {
			std::cout << e.what() << std::endl;
		}
	}
	else {
		//choose different pawn
		std::cout << "Cannot move this pawn :(" << std::endl;
	}
	std::cin.get();
	checkHome(active_player, pawn_number, end_of_game);
	showBoard();
}

void Board::nextPlayer(int& active_player)
{
	if (active_player == 3) {
		active_player = 0;
	}
	else {
		++active_player;
	}
}

void Board::moveOutOfBase(int active_player, int pawn_number)
{
	std::cout << "Moving pawn out of base." << std::endl;
	out[active_player] = true;
	players[active_player]->setOut(pawn_number - 1, true);
	players[active_player]->setPawnsPosition(board_length / 4 * active_player, pawn_number - 1);
	squares[players[active_player]->getPosition(pawn_number - 1)] = players[active_player]->getSymbol(pawn_number - 1);
	updateTheBoard();
	showBoard();
}

void Board::checkHome(int active_player, int pawn_number, bool& end_of_game)
{
	int home_count = 0;
	//if the pawn that player has moved should be in home now, add him to home
	if (players[active_player]->getPosition(pawn_number - 1) == -10) {
		int home_position = players[active_player]->getSteps(pawn_number - 1) - board_length;
		players[active_player]->setHome(pawn_number - 1, true);
		home[active_player][home_position] = pawn_number;
	}
	//check if the home is full
	for (int i = 0; i < 4; ++i) {
		if (home[active_player][i] != 0) {
			home_count++;
		}
	}
	if (home_count == 4) {
		std::cout << players[active_player]->getName() << " HAS WON!!" << std::endl;
		std::cin.ignore(256, '\n');
		std::cin.clear();
		std::cin.get();
		end_of_game = true;

	}
}

bool Board::checkMove(int active_player, int rolled_dice, int pawn_number)
{
	int home_position = players[active_player]->getSteps(pawn_number - 1) + rolled_dice - board_length;
	//if you won't go past the length of the board
	if (!((players[active_player]->getSteps(pawn_number - 1) + rolled_dice) > (board_length + 3))) {
		//if you're near home, which means that you can enter the home with one move, check if there are no other pawns on the square you want to move to
		if (home_position > -1) {
			//if there is no space in home where you want to move to
			if (home[active_player][home_position] != 0) {
				return false;
			}
			//else you can move (there is free space in home)
			else
				return true;
		}
		//if you're not near home and you won't go out of the board's range
		else
			return true;
	}
	else
		return false;
}

void Board::updateTheBoard()
{
	//write homes
	for (int i = 0; i < 31; i += 10) {
		squares[i] = 'X';
	}
	//write pawns to the squares
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (players[i]->getPosition(j) > -1) {
				squares[players[i]->getPosition(j)] = players[i]->getSymbol(j);
			}
		}
	}
	//update the board with pawns
	for (int i = 0; i < board_length; ++i) {
		board[map.getX(i)][map.getY(i)] = squares[i];
	}

}

Board::Board()
{
	if (map.loadMap()) {
		std::cout << "Welcome to the board game named 'chinese man' - directly translating from polish" << std::endl << "(it's not racist seriously I'm not lying)." << std::endl << "There will be two real players and two bots, which you can also name." << std::endl << "I hope you'll enjoy this little competitive game." << std::endl << "Best of luck!" << std::endl;
		std::cin.get();
		//allocate memory for players
		players = new Player*[number_of_players];
		//allocate memory for pawns
		pawns = new Pawn[16];
		//create players and name them
		for (int i = 0; i < 2; ++i) {
			players[i] = new Player;
			players[i]->setNumber(i);
			std::cout << "Name the " << i + 1 << " player." << std::endl;
			players[i]->namePlayer();
		}
		for (int i = 2; i < 4; ++i) {
			players[i] = new FakePlayer;
			players[i]->setNumber(i);
			std::cout << "Name the greates mind of all time bot player number " << i - 1 << " to your best liking" << std::endl;
			players[i]->namePlayer(); //WHY AM I NAMING FAKE PLAYERS? why not...
		}
		system("cls");
		//load a map
		//write ones to all squares
		for (int i = 0; i < board_length; ++i) {
			squares[i] = '-';
		}
	}
	else {
		exit(-1);
	}
}


Board::~Board()
{

	delete[] players;
	delete[] pawns;
}

void Board::readyGame()
{
	char temp;
	int number_of_pawn = 0;
	//assign pawns to players, later ask them about their color
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			players[i]->assignPawn(pawns[number_of_pawn], j);
			++number_of_pawn;
		}
	}
	//assign colors to players
	std::cout << "Which color would you like to be? Enter a single character, no matter what it is, letter, symbol - just choose one." << std::endl;
	for (int i = 0; i < 4; ++i) {
		std::cout << players[i]->getName() << std::endl;
		std::cin >> temp;
		players[i]->setPawnsSymbol(temp);
		std::cin.clear();
		std::cin.ignore(256, '\n');
	}
	
}

void Board::play() {
	bool end_of_game = false;
	int pawn_number = 0;
	int rolled_dice = 0;
	int active_player = 0;
	int number_of_rolls_left = 0;
	readyGame();
	//the game doesn't end until somebody wins, there will be a condition added
	while (!end_of_game) {
		std::cin.get();
		std::cout << players[active_player]->getName() << " is rolling the dice." << std::endl;
		//if player has no active pawns, give him 3 rolls
		if (!out[active_player]) {
			number_of_rolls_left = 3;
		}
		while (1) {
			//everybody rolls a dice
			//if players rolls six, he's got another roll
			if ((rolled_dice = players[active_player]->throwDice(dice)) == 6) {
				//move/get out of base
				while (1) {
					players[active_player]->askForPawn(pawn_number, rolled_dice);
					//if selected pawn is in base, move it out
					try {
						if (!players[active_player]->isOut(pawn_number - 1)) {
							moveOutOfBase(active_player, pawn_number);//add updating of the board
						}

						//if selected pawn is not in base, move it
						else {
							movePawn(active_player, rolled_dice, pawn_number, end_of_game);
						}
					}
					catch (const myException& e) {
						std::cout << e.what() << std::endl;
						continue;
					}
					break;
				}
				continue;
			}
			//if the player has no active pawns, he gets to roll again
			else if (!out[active_player] && number_of_rolls_left > 0) {
				//take away one roll
				number_of_rolls_left--;
				continue;
			}
			//if the player hasn't rolled 6 and has no active pawns, move to the next player
			else if (!out[active_player] && number_of_rolls_left == 0) {
				//next player
				nextPlayer(active_player);
				break;
			}
			//if it's a normal roll and player has active pawns, move and go to the next player
			else {
				//ask for a pawn to move and check if it's active
				while (1) {
					try {
						players[active_player]->askForPawn(pawn_number, rolled_dice);
						//if selected pawn is in base, move it out
						if (!players[active_player]->isOut(pawn_number - 1)) {
							std::cout << "You can only move pawns that are active." << std::endl;
							continue;
						}
						//move an active pawn
						else {
							movePawn(active_player, rolled_dice, pawn_number, end_of_game);
							break;
						}
					}
					catch (const myException& e) {
						std::cout << e.what() << std::endl;
						continue;
					}
				}
				//next player
				nextPlayer(active_player);
				break;
			}
		}
	}
	std::cout << "Thank you for playing." << std::endl;
}

void Board::showPlayer()
{
	for (int i = 0; i < 4; ++i) {
		std::cout << players[i]->getName() << std::endl;
	}
}

void Board::showBoard()
{
	system("cls");
	for (int i = 0; i < coordinate_length; ++i) {
		for (int j = 0; j < coordinate_length; ++j) {
			std::cout << board[j][i];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "HOMES" << std::endl;
	for (int i = 0; i < 4; ++i) {
		std::cout << players[i]->getName() << "  " << players[i]->getSymbol(1) << std::endl;
		for (int j = 0; j < 4; ++j) {
			std::cout << home[i][j];
		}
		std::cout << std::endl;
	}
}
