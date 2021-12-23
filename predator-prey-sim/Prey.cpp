#include "Prey.h"

Prey::Prey(Habitat* city, int hX, int hY) : Organism(city, hX, hY) {
    // Set the prey recruit timer
    breedCountdown = PREY_SPAWN_TIMER;
}

Prey::~Prey() {}

// Recruit routine
void Prey::breed() {
    // Cannot breed if counter has not expired
    if (breedCountdown > 0) return;

    // Get the validated potential moves based on the current instance organism X & Y coords
    vector<int> potentialMoves = getPossibleMoves(Xcoord, Ycoord);
    if (potentialMoves.empty())
    {
        // Resetting recruit counter - Unable to recruit
        breedCountdown = PREY_SPAWN_TIMER;
        return;
    }

    // Determine a placement for the recruit
    int movePrey = potentialMoves[city->randomNumGen(0, potentialMoves.size() - 1)];
    int newX = Xcoord;
    int newY = Ycoord;

    // Validate the new location and place
    getValidCoord(newX, newY, movePrey);
    city->grid[newX][newY] = new Prey(city, newX, newY);

    // Record a new human on the grid
    city->increaseActivePrey();

    // Reset the recruit counter
    breedCountdown = PREY_SPAWN_TIMER;
}


