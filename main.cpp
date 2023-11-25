#include "RecursiveBacktracking.hpp"

int main()
{
	RecursiveBacktracking maze(10, 10);
	maze.generateMaze();
	maze.printMaze();

	return 0;
}