#pragma once
#define board_length 40

class Pawn
{
private:
	bool out = false;
	bool home = false;
	char symbol;
	int position;
	int steps_made;
	int number;
	int player;
public:
	Pawn();
	~Pawn();
	void move(int number_of_steps);
	void setPlayer(int player_number);
	void setSymbol(char new_color);
	void setPosition(int new_positon);
	void setOut(bool mode);
	void setHome(bool mode);
	char getSymbol();
	bool getOut() { return out; }
	bool isHome() { return home; }
	int getPosition();
	int getSteps();
	int getPlayer();
};

