#pragma once

#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "RecursiveBacktrackingDataTypes.hpp"

namespace makal7
{

    //class declaration
    class RecursiveBacktracking
    {
    public:
        void generateMaze();
        std::vector<std::vector<Cell>> getMaze();
        void printMaze();
        RecursiveBacktracking(int width_, int height_);

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
}