#include "RecursiveBacktracking.hpp"

void RecursiveBacktracking::generateMaze()
{

	currentCell.x = rand() % this->width;
	currentCell.y = rand() % this->height;

    this->grid[currentCell.x][0].northWall = false; //vstup do bludiska

	this->grid[currentCell.x][currentCell.y].visited = true;

    do //pokial exstuje nenavstivena bunka
    {
        if (this->setDirection() == -1)
            continue;

        //pohni sa - sekcia
        stackX.push(this->currentCell.x);
        stackY.push(this->currentCell.y);

        switch (this->currentCell.direction)
        {
        case EAST:  this->grid[this->currentCell.x][this->currentCell.y].eastWall = false; this->currentCell.x += 1; this->grid[this->currentCell.x][this->currentCell.y].westWall = false; break;
        case WEST:  this->grid[this->currentCell.x][this->currentCell.y].westWall = false; this->currentCell.x -= 1; this->grid[this->currentCell.x][this->currentCell.y].eastWall = false; break;
        case NORTH: this->grid[this->currentCell.x][this->currentCell.y].northWall = false; this->currentCell.y -= 1; this->grid[this->currentCell.x][this->currentCell.y].southWall = false; break;
        case SOUTH: this->grid[this->currentCell.x][this->currentCell.y].southWall = false; this->currentCell.y += 1; this->grid[this->currentCell.x][this->currentCell.y].northWall = false; break;
        }

        grid[currentCell.x][currentCell.y].visited = true;

    } while (!allVisited());

    this->grid[currentCell.x][height - 1].southWall = false; //vychod z bludiska
}

std::vector<std::vector<Cell>> RecursiveBacktracking::getMaze()
{
	return grid;
}

void RecursiveBacktracking::printMaze()
{
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            printf("+");
            if (this->grid[j][i].northWall)
                printf("--");
            else
                printf("  ");
        }
        printf("+\n");

        for (int j = 0; j < this->width; j++) {
            if (this->grid[j][i].westWall)
                printf("|");
            else
                printf(" ");

            printf(" ");
            // Prostredný znak (bunka) - môžete prispôsobi pod¾a potreby
            printf(" ");
        }

        if (this->grid[this->width - 1][i].eastWall)
            printf("|\n");
        else
            printf(" \n");
    }

    // Posledný riadok
    for (int j = 0; j < this->width; j++) {
        printf("+");
        if (this->grid[j][this->height - 1].southWall)
            printf("--");
        else
            printf("  ");
    }
    printf("+\n");
}

RecursiveBacktracking::RecursiveBacktracking(int width_, int height_)
{
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

	time_t t;
	this->seed = time(&t);
	srand(seed);

}

bool RecursiveBacktracking::allVisited()
{
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			if (this->grid[i][j].visited == false)
				return false;

	return true;
}

int RecursiveBacktracking::setDirection()
{
    //vyber smer
    this->currentCell.direction = 0;
    this->currentCell.eastAvailable = false;
    this->currentCell.westAvailable = false;
    this->currentCell.northAvailable = false;
    this->currentCell.southAvailable = false;

    if (this->currentCell.y >= 1)
    {
        if (this->grid[this->currentCell.x][this->currentCell.y - 1].visited == false) //hore sever
            this->currentCell.northAvailable = true;
        else
            this->currentCell.northAvailable = false;
    }

    if (this->currentCell.y < (this->height - 1))
    {
        if (this->grid[this->currentCell.x][this->currentCell.y + 1].visited == false) //dole juh
            this->currentCell.southAvailable = true;
        else
            this->currentCell.southAvailable = false;
    }
    if (this->currentCell.x >= 1)
    {
        if (this->grid[this->currentCell.x - 1][this->currentCell.y].visited == false) //vlavo zapad
            this->currentCell.westAvailable = true;
        else
            this->currentCell.westAvailable = false;
    }
    if (this->currentCell.x < (this->width - 1))
    {

        if (this->grid[this->currentCell.x + 1][this->currentCell.y].visited == false) //vpravo vychod
            this->currentCell.eastAvailable = true;
        else
            this->currentCell.eastAvailable = false;
    }

    if ((this->currentCell.northAvailable + this->currentCell.southAvailable + this->currentCell.westAvailable + this->currentCell.eastAvailable) == 1) //ak je iba jeden smer volny chod tam
    {
        if (this->currentCell.northAvailable)
            this->currentCell.direction = NORTH;
        if (this->currentCell.southAvailable)
            this->currentCell.direction = SOUTH;
        if (this->currentCell.westAvailable)
            this->currentCell.direction = WEST;
        if (this->currentCell.eastAvailable)
            this->currentCell.direction = EAST;

    }

    if (((this->currentCell.northAvailable + this->currentCell.southAvailable + this->currentCell.westAvailable + this->currentCell.eastAvailable) == 0) && !allVisited()) //ak nie je dostupny ziadny smer vrat sa o 1
    {
        stackX.pop();
        stackY.pop();
        this->currentCell.x = stackX.top();
        this->currentCell.y = stackY.top();
        return -1;
    }

    if ((this->currentCell.direction == 0) && (!allVisited() && !(this->currentCell.northAvailable + this->currentCell.southAvailable + this->currentCell.westAvailable + this->currentCell.eastAvailable) == 0)) //inak vyber smer nahodne
    {

        bool randSus;
        int randomDirection;
        do
        {
            randomDirection = (rand() % 4) + 1;
            randSus = false;
            if (randomDirection == NORTH)
                if (this->currentCell.northAvailable)
                {
                    this->currentCell.direction = NORTH;
                    randSus = true;
                }

            if (randomDirection == SOUTH)
                if (this->currentCell.southAvailable)
                {
                    this->currentCell.direction = SOUTH;
                    randSus = true;
                }

            if (randomDirection == WEST)
                if (this->currentCell.westAvailable)
                {
                    this->currentCell.direction = WEST;
                    randSus = true;
                }

            if (randomDirection == EAST)
                if (this->currentCell.eastAvailable)
                {
                    this->currentCell.direction = EAST;
                    randSus = true;
                }

        } while (randSus == false);
    }

    return 0;
}
