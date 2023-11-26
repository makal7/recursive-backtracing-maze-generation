#include "RecursiveBacktracking.hpp"

int main()
{
	makal7::RecursiveBacktracking maze(10, 10);
	maze.generateMaze();
	maze.printMaze();

	return 0;
}