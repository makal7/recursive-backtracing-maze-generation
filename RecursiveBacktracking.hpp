#pragma once

#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#define EAST  1
#define WEST  2
#define NORTH 3
#define SOUTH 4

struct Cell
{
    bool eastWall, westWall, northWall, southWall;
    bool visited;
};

struct CurrentCell
{
    int x, y;
    int direction;
    bool eastAvailable, westAvailable, northAvailable, southAvailable;
};

class RecursiveBacktracking
{
	public:
        void generateMaze();
        std::vector<std::vector<Cell>> getMaze();
        void printMaze();
		RecursiveBacktracking(int width_,int height_);

    private:
        bool allVisited();
        int setDirection();


        int width, height;
        CurrentCell currentCell;
        std::vector<std::vector<Cell>> grid;
        //CurrentCell currentCell;
        std::stack<int> stackX;
        std::stack<int> stackY;
        unsigned int seed;

};

