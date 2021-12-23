#include "Specs.h"
#include "Organism.h"

// Initialize a new organism in the current city
Organism::Organism(Habitat* _city, int _x, int _y)
{
    city = _city;
    Xcoord = _x;
    Ycoord = _y;
    breedCountdown = 0;
    timeSteps = _city->timeSteps;
}

Organism::~Organism() {}

// Create a vector of all the possible moves an organism can make
vector<int> Organism::getPossibleMoves(int x, int y) const
{
    vector<int> possibleMoves;
    int tmpX, tmpY;
    for (int move = EAST; move <= NORTH; move++)
    {
        tmpX = x;
        tmpY = y;

        // Validation of next move
        getValidCoord(tmpX, tmpY, move);

        // If the next cell is out of bounds
        if (!isValidMove(tmpX, tmpY)) continue;

        // If the next cell is available
        if (city->grid[tmpX][tmpY] == nullptr)
        {
            possibleMoves.push_back(move);
        }
    }
    return possibleMoves;
}

// Check if the next move is out of bounds
bool Organism::isValidMove(int x, int y) const
{
    // Set the out-of-bounds condition
    if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
    {
        return false;
    }
    return true;
}

// Get a valid coord
void Organism::getValidCoord(int& x, int& y, int move) const
{
    // Zombies can move diagonally
    if (city->grid[x][y]->getType() == PREDATOR_TYPE)
    {
        // Horizontal plane
        if (move == EAST) x--;
        if (move == WEST) x++;
        // Vertical plane
        if (move == SOUTH) y--;
        if (move == NORTH) y++;
        // Diagonals
        if (move == SOUTH_EAST) x--, y--;
        if (move == SOUTH_WEST) x++, y--;
        if (move == NORTH_EAST) x--, y++;
        if (move == NORTH_WEST) x++, y++;
    }
    else
    {
        // Horizontal plane
        if (move == EAST) x--;
        if (move == WEST) x++;
        // Vertical plane
        if (move == SOUTH) y--;
        if (move == NORTH) y++;
    }
}

// Move the organism - Human and Zombie can move differently
void Organism::move()
{
    // Check to make sure the same organism didn't move twice in one time step
    if (timeSteps == city->timeSteps) return;

    timeSteps++;
    breedCountdown--;

    // Generate a new position for the organism to move to
    int newMove = city->randomNumGen(EAST, NORTH);
    int newX = Xcoord;
    int newY = Ycoord;

    // Make sure the new move is valid
    getValidCoord(newX, newY, newMove);

    if (isValidMove(newX, newY))
    {
        // If the new move has something there
        if (city->grid[newX][newY] != nullptr) return;

        city->grid[Xcoord][Ycoord] = nullptr; // Initialize the next space
        city->grid[newX][newY] = this;        // Place the organism at the next space

        Xcoord = newX;
        Ycoord = newY;
    }
}


