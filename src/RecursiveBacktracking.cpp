#include "RecursiveBacktracking.hpp"

namespace makal7
{

    //method that generates a maze
    void RecursiveBacktracking::generateMaze()
    {
        //random starting location
        currentCell.x = rand() % this->width;
        currentCell.y = rand() % this->height;

        //create entrance to the maze
        this->grid[currentCell.x][0].northWall = false;

        //set current cell as visited
        this->grid[currentCell.x][currentCell.y].visited = true;

        //repeat as long as there is an unvisited cell
        do
        {
            //set the direction
            if (this->setDirection() == -1)
                continue;

            //save the old location
            stackX.push(this->currentCell.x);
            stackY.push(this->currentCell.y);

            //move and make transitions between walls
            switch (this->currentCell.direction)
            {
            case EAST:  this->grid[this->currentCell.x][this->currentCell.y].eastWall = false; this->currentCell.x += 1; this->grid[this->currentCell.x][this->currentCell.y].westWall = false; break;
            case WEST:  this->grid[this->currentCell.x][this->currentCell.y].westWall = false; this->currentCell.x -= 1; this->grid[this->currentCell.x][this->currentCell.y].eastWall = false; break;
            case NORTH: this->grid[this->currentCell.x][this->currentCell.y].northWall = false; this->currentCell.y -= 1; this->grid[this->currentCell.x][this->currentCell.y].southWall = false; break;
            case SOUTH: this->grid[this->currentCell.x][this->currentCell.y].southWall = false; this->currentCell.y += 1; this->grid[this->currentCell.x][this->currentCell.y].northWall = false; break;
            }

            //set current cell as visited
            grid[currentCell.x][currentCell.y].visited = true;

        } while (!allVisited());

        //create exit from the maze
        this->grid[currentCell.x][height - 1].southWall = false;
    }

    //method that returns the maze
    std::vector<std::vector<Cell>> RecursiveBacktracking::getMaze()
    {
        return grid;
    }

    //method that prints the maze to the console window
    void RecursiveBacktracking::printMaze()
    {
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                std::cout << "+";
                if (this->grid[j][i].northWall)
                    std::cout << "----";
                else
                    std::cout << "    ";
            }
            std::cout << "+\n";

            for (int j = 0; j < this->width; j++) {
                if (this->grid[j][i].westWall)
                    std::cout << "|";
                else
                    std::cout << " ";

                std::cout << "    ";
            }

            if (this->grid[this->width - 1][i].eastWall)
                std::cout << "|\n";
            else
                std::cout << " \n";
        }

        for (int j = 0; j < this->width; j++) {
            std::cout << "+";
            if (this->grid[j][this->height - 1].southWall)
                std::cout << "----";
            else
                std::cout << "    ";
        }
        std::cout << "+\n";
    }

    //constructor
    RecursiveBacktracking::RecursiveBacktracking(int width_, int height_)
    {
        //initialization of variables
        this->width = width_;
        this->height = height_;

        this->grid.reserve(width);
        for (int i = 0; i < width; ++i)
        {
            this->grid.push_back(std::vector<Cell>(height));
        }

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                this->grid[i][j].eastWall = true;
                this->grid[i][j].westWall = true;
                this->grid[i][j].northWall = true;
                this->grid[i][j].southWall = true;
                this->grid[i][j].visited = false;
            }
        }

        this->currentCell.numberOfDirections = 0;
        this->currentCell.direction = 0;
        this->currentCell.eastAvailable = 0;
        this->currentCell.northAvailable = 0;
        this->currentCell.southAvailable = 0;
        this->currentCell.westAvailable = 0;
        this->currentCell.x = 0;
        this->currentCell.y = 0;

        //generate random seed
        time_t t;
        this->seed = (unsigned int)time(&t);
        srand(seed);
    }

    //method that checks if all cells have been visited
    bool RecursiveBacktracking::allVisited()
    {
        for (int i = 0; i < this->width; i++)
            for (int j = 0; j < this->height; j++)
                if (this->grid[i][j].visited == false)
                    return false;

        return true;
    }

    //a method that selects a direction
    int RecursiveBacktracking::setDirection()
    {
        this->currentCell.direction = 0;
        this->currentCell.eastAvailable = false;
        this->currentCell.westAvailable = false;
        this->currentCell.northAvailable = false;
        this->currentCell.southAvailable = false;
        this->currentCell.numberOfDirections = 0;


        //check how many directions and which directions of movement are available
        this->whichDirectionsAreAvailable();

        //if multiple directions are available, randomly select one of them
        if (this->currentCell.numberOfDirections > 1)
        {
            bool randSus = false;
            int randomDirection;

            do
            {
                randomDirection = (rand() % 4) + 1;

                switch (randomDirection)
                {
                case NORTH: if (this->currentCell.northAvailable) { this->currentCell.direction = NORTH; randSus = true; } break;
                case SOUTH: if (this->currentCell.southAvailable) { this->currentCell.direction = SOUTH; randSus = true; } break;
                case WEST:  if (this->currentCell.westAvailable) { this->currentCell.direction = WEST;  randSus = true; } break;
                case EAST:  if (this->currentCell.eastAvailable) { this->currentCell.direction = EAST;  randSus = true; } break;
                }

            } while (randSus == false);

            return 0;
        }

        //if only one direction is available, go there
        if (this->currentCell.numberOfDirections == 1)
        {
            if (this->currentCell.northAvailable)
            {
                this->currentCell.direction = NORTH;
                return 0;
            }
            if (this->currentCell.southAvailable)
            {
                this->currentCell.direction = SOUTH;
                return 0;
            }
            if (this->currentCell.westAvailable)
            {
                this->currentCell.direction = WEST;
                return 0;
            }
            if (this->currentCell.eastAvailable)
            {
                this->currentCell.direction = EAST;
                return 0;
            }
        }

        //if no direction is available go back by 1
        if (this->currentCell.numberOfDirections == 0)
        {
            stackX.pop();
            stackY.pop();
            this->currentCell.x = stackX.top();
            this->currentCell.y = stackY.top();
            return -1;
        }

        return 0;
    }

    //a method that check how many directions and which directions of movement are available
    void RecursiveBacktracking::whichDirectionsAreAvailable()
    {
        if (this->currentCell.y >= 1)
        {
            if (this->grid[this->currentCell.x][this->currentCell.y - 1].visited == false)
            {
                this->currentCell.northAvailable = true;
                this->currentCell.numberOfDirections += 1;
            }
            else
            {
                this->currentCell.northAvailable = false;
            }
        }

        if (this->currentCell.y < (this->height - 1))
        {
            if (this->grid[this->currentCell.x][this->currentCell.y + 1].visited == false)
            {
                this->currentCell.southAvailable = true;
                this->currentCell.numberOfDirections += 1;
            }
            else
            {
                this->currentCell.southAvailable = false;
            }
        }
        if (this->currentCell.x >= 1)
        {
            if (this->grid[this->currentCell.x - 1][this->currentCell.y].visited == false)
            {
                this->currentCell.westAvailable = true;
                this->currentCell.numberOfDirections += 1;
            }
            else
            {
                this->currentCell.westAvailable = false;
            }
        }
        if (this->currentCell.x < (this->width - 1))
        {

            if (this->grid[this->currentCell.x + 1][this->currentCell.y].visited == false)
            {
                this->currentCell.eastAvailable = true;
                this->currentCell.numberOfDirections += 1;
            }
            else
            {
                this->currentCell.eastAvailable = false;
            }
        }
    }
}