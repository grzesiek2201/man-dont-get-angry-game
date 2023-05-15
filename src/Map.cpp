#include "Map.h"
#include "myException.h"
#include <iostream>

bool Map::loadMap()	//**STRING STREAM AND FILE HANDLING**
{
	bool good = false;
	std::string line;
	std::stringstream line_stream;
	std::fstream plik;
	plik.open("board_map.txt", std::ifstream::in);
	try {
		if (!plik) {
			myException e("The board_map file was not found. Please read 'readme.txt'");
			throw(e);
		}
		else {
			good = true;
			int coordinate = 0;
			while (!plik.eof()) {
				int i = 0;
				line_stream.str("");
				line_stream.clear();
				getline(plik, line);
				line_stream << line;
				while (!line_stream.eof()) {
					if (coordinate == 0) {
						line_stream >> x_coordinate[i];
					}
					else if (coordinate == 1) {
						line_stream >> y_coordinate[i];
					}
					++i;
				}
				coordinate++;
			}
		}
	}
	catch (const myException &e) {
		std::cout << e.what() << std::endl;
	}
	return good;
}

Map::Map()
{
}


Map::~Map()
{
}