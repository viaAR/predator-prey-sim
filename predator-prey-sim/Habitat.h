#pragma once

#include <iostream>
#include "Specs.h"
#include "windows.h"
#include <chrono>
#include <thread>

using namespace std;

class Organism;
class Prey;
class Predator;

class Habitat {
    friend class Organism;
    friend class Prey;
    friend class Predator;

private:
    Organism* grid[GRIDSIZE][GRIDSIZE]; // Generate a grid that can be populated with Organisms
    int timeSteps;                      // Track the time-step count
    int randomNumGen(int, int) const;   // Generate random number for placement
    int activePrey = 0;
    int activePredator = 0;
public:
    // Constructors
    Habitat();
    virtual ~Habitat();

    // City Methods
    void run();          // Start a new game
    void nextTimeStep(); // Move to the next time-step
    void render() const; // Display the grid to the user

    // Track populations
    int getTimeSteps();

    int getActivePrey();
    void increaseActivePrey();
    void decreaseActivePrey();

    int getActivePredators();
    void increaseActivePredator();
};