#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

class MapReader {
private:
	int **Maze;
	int x, y;
	double ppos_x, ppos_y;

public:
	MapReader(std::string location)
	{
	
			std::ifstream file;
			file.open(location.c_str());

			char letter;
			file >> x >> letter >> y;
			std::cout << x << "	" << y<<std::endl;
			Maze = new int *[y];
			for (int i = 0; i < y; ++i)
				Maze[i] = new int[x];

			std::ifstream readFile(location.c_str());
			std::vector<std::string> v;
			std::string line;
			while (std::getline(readFile, line))
			{
				v.push_back(line);
			}

			for (int i = 0; i < y; ++i)
			{
				for (int j = 0; j < x; ++j)
				{
					if ((v[i+1])[j] == 'X') Maze[i][j] = 1;
					else if ((v[i + 1])[j] == 'E') Maze[i][j] = 2;
					else if ((v[i + 1])[j] == 's')
					{
						ppos_x = i+1;
						ppos_y = j;
						Maze[i][j] = 0;
					}
					else Maze[i][j] = 0;
				}
			}
            
            
	}

	int getElement(int x, int y)
	{
		return Maze[x][y];
	}

	int getWidth()
	{
		return x;
	}

	int getHeight()
	{
		return y;
	}

	int getPlayerPosX()
	{
		return ppos_x;
	}

	int getPlayerPosY()
	{
		return ppos_y;
	}
	~MapReader()
	{
		for (int i = 0; i < y; ++i) {
			delete [] Maze[i];
		}
		delete[] Maze;
	}
};
