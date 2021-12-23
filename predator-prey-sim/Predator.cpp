#include "Predator.h"

Predator::Predator(Habitat* city, int zX, int zY) : Organism(city, zX, zY) {
    breedCountdown = PREDATOR_CONVERT_TIMER;
    starveCountdown = PREDATOR_STARVE_TIMER;
}

Predator::~Predator() {}

void Predator::breed() {
    // If the timer hasn't expired, exit
    if (breedCountdown > 0) return;

    // Find the prey targets in range to convert
    vector<int> findConvert = scanForPrey(Xcoord, Ycoord);

    if (findConvert.empty())
    {
        return;
    }

    int convertPrey = findConvert[city->randomNumGen(0, findConvert.size() - 1)];

    int targetX = Xcoord;
    int targetY = Ycoord;

    // Validate the new location and place
    getValidCoord(targetX, targetY, convertPrey);

    // Delete the human in the target space
    delete city->grid[targetX][targetY];

    // Record the lost prey
    city->decreaseActivePrey();

    // Replace (Convert) the space to a predator
    city->grid[targetX][targetY] = new Predator(city, targetX, targetY);

    // Record a new predator
    city->increaseActivePredator();

    // Reset the timer
    breedCountdown = PREDATOR_CONVERT_TIMER;

}

// Determine what cells have prey in them and go that way
vector<int> Predator::scanForPrey(int zX, int zY) const {
    vector<int> moveTowardPrey;
    int tmpX, tmpY;

    // Predators have the ability to move and track diagonally 
    for (int move = EAST; move <= NORTH_WEST; move++)
    {
        tmpX = zX;
        tmpY = zY;

        // Validation
        getValidCoord(tmpX, tmpY, move);
        if (!isValidMove(tmpX, tmpY)) continue;

        // Look for a cell with prey in it
        if (city->grid[tmpX][tmpY] == nullptr) continue;
        if (city->grid[tmpX][tmpY]->getType() == PREY_TYPE)
        {
            moveTowardPrey.push_back(move);
        }
    }
    return moveTowardPrey;
}

void Predator::move() {
    if (timeSteps == city->timeSteps) return;
    // Providing current location
    vector<int> moveTowardPrey = scanForPrey(Xcoord, Ycoord);

    // If there are no prey close by
    if (moveTowardPrey.empty())
    {
        // Use the default move pattern
        Organism::move();

        starveCountdown--;

        return;
    }

    timeSteps++;

    // Reset the timer
    starveCountdown = PREDATOR_STARVE_TIMER;
    breedCountdown--;

    // If there is prey in range
    int movePredator = moveTowardPrey[city->randomNumGen(0, moveTowardPrey.size() - 1)];
    int targetX = Xcoord;
    int targetY = Ycoord;

    getValidCoord(targetX, targetY, movePredator);

    // Predator eats the prey
    delete city->grid[targetX][targetY];

    // Record the lost prey
    city->decreaseActivePrey();

    city->grid[targetX][targetY] = this;
    city->grid[Xcoord][Ycoord] = nullptr;

    Xcoord = targetX;
    Ycoord = targetY;
}

bool Predator::starve() {
    if (starveCountdown == 0)
    {
        return true;
    }
    return false;
}
