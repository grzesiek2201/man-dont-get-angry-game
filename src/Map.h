#pragma once
#include <fstream>
#include <string>
#include <sstream>

#define board_length 40
#define coordinate_length 12

class Map
{
private:
	int x_coordinate[board_length];
	int y_coordinate[board_length];
public:
	Map();
	~Map();
	bool loadMap();
	int getX(int position) { return x_coordinate[position]; }
	int getY(int position) { return y_coordinate[position]; }
};

