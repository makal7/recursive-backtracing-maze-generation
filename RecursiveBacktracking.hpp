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

//datatype of maze
struct Cell
{
    bool eastWall, westWall, northWall, southWall;
    bool visited;
};

//datatype of current cell
struct CurrentCell
{
    int x, y;
    int direction, numberOfDirections;
    bool eastAvailable, westAvailable, northAvailable, southAvailable;
};

//class declaration
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
        void whichDirectionsAreAvailable();


        int width, height;
        unsigned int seed;
        CurrentCell currentCell;
        std::vector<std::vector<Cell>> grid;
        std::stack<int> stackX;
        std::stack<int> stackY;
};