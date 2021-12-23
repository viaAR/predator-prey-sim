#include "Habitat.h"
#include "Organism.h"
#include "Prey.h"
#include "Predator.h"

// Create a new city
Habitat::Habitat() {
    srand(time(NULL));
    timeSteps = 0;

    // Initialize the grid to a 2d array of null pointers
    for (int x = 0; x < GRIDSIZE; x++)
    {
        for (int y = 0; y < GRIDSIZE; y++)
        {
            grid[x][y] = nullptr;
        }
    }
}

Habitat::~Habitat() {}

// Generate a random number for organism placement
int Habitat::randomNumGen(int start, int end) const {
    // rand() % ... will generate a random number in range start, end
    return rand() % (end - start + 1) + start;
}

void Habitat::run() {
    int x, y;
    int humanCount = 0;
    int zombieCount = 0;

    while (humanCount < PREY_STARTCOUNT)
    {
        x = randomNumGen(0, GRIDSIZE - 1);
        y = randomNumGen(0, GRIDSIZE - 1);

        // Check to see if something is already there
        if (grid[x][y] != nullptr) continue;

        // Add a human to the grid
        grid[x][y] = new Prey(this, x, y);
        humanCount++;

        // Record new human
        activePrey++;
    }

    while (zombieCount < PREDATOR_STARTCOUNT)
    {
        x = randomNumGen(0, GRIDSIZE - 1);
        y = randomNumGen(0, GRIDSIZE - 1);

        if (grid[x][y] != nullptr) continue;

        // Add a zombie to the grid
        grid[x][y] = new Predator(this, x, y);

        zombieCount++;

        // Record new zombie
        activePredator++;
    }
}

// Walk through each timeStep and all associated organism actions
void Habitat::nextTimeStep() {

    timeSteps++;

    // Everyone moves
    for (int x = 0; x < GRIDSIZE; x++)
    {
        for (int y = 0; y < GRIDSIZE; y++)
        {
            if (grid[x][y] == nullptr) continue;

            grid[x][y]->move();
        }
    }

    //  Breeding routines
    for (int x = 0; x < GRIDSIZE; x++)
    {
        for (int y = 0; y < GRIDSIZE; y++)
        {
            if (grid[x][y] == nullptr) continue;
            grid[x][y]->breed();
        }
    }

    // Starve routine
    for (int x = 0; x < GRIDSIZE; x++)
    {
        for (int y = 0; y < GRIDSIZE; y++)
        {
            if (grid[x][y] == nullptr) continue;

            // If starve is true at x & y
            if (grid[x][y]->starve())
            {
                delete grid[x][y];
                grid[x][y] = nullptr;

                // Record the lost predator
                activePredator--;

                // Convert the predator back into prey
                grid[x][y] = new Prey(this, x, y);

                // Record a new prey
                activePrey++;

            }
        }
    }
}

// Display the grid
void Habitat::render() const {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int x = 0; x < GRIDSIZE; x++)
    {
        for (int y = 0; y < GRIDSIZE; y++)
        {
            if (grid[x][y] == nullptr)
            {
                cout << " " << SPACE_CH << " ";
            }
            else if (grid[x][y]->getType() == PREY_TYPE)
            {
                SetConsoleTextAttribute(hConsole, PREY_COLOR);
                cout << " " << PREY_CH << " ";

            }
            else if (grid[x][y]->getType() == PREDATOR_TYPE)
            {
                SetConsoleTextAttribute(hConsole, PREDATOR_COLOR);
                cout << " " << PREDATOR_CH << " ";
            }
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
        }
        cout << endl;
    }
}

int Habitat::getTimeSteps()
{
    // Add 1 because timeSteps is 0 based
    return timeSteps + 1;
}

int Habitat::getActivePrey()
{
    return activePrey;
}

void Habitat::increaseActivePrey()
{
    activePrey++;
}

void Habitat::decreaseActivePrey()
{
    activePrey--;
}

int Habitat::getActivePredators()
{
    return activePredator;
}

void Habitat::increaseActivePredator()
{
    activePredator++;
}
