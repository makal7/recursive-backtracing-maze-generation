#pragma once

namespace makal7
{

    //definition of the cardinal directions
    enum CardinalDirections {
        EAST = 1,
        WEST = 2,
        NORTH = 3,
        SOUTH = 4
    };

    //datatype of maze
    struct Cell
    {
        bool eastWall, westWall, northWall, southWall;
        bool visited;
    };

    //datatype of current cell
    struct CurrentCell
    {
        unsigned int x, y;
        unsigned int direction, numberOfDirections;
        bool eastAvailable, westAvailable, northAvailable, southAvailable;
    };
}