#pragma once

#include <vector>
#include "Habitat.h"

using namespace std;

class Organism {
protected:
    Habitat* city;         // Point to the current instance of the city
    int Xcoord, Ycoord; // Track the X & Y coords of every organism (for modification)
    int breedCountdown; // Keep track of the time to breed (override)
    int timeSteps;      // Track the count of time-steps

    // Determine the possible moves and if they are valid
    vector<int> getPossibleMoves(int, int) const;
    bool isValidMove(int, int) const;

    // Get the coords of a validated move to push to the organism
    void getValidCoord(int&, int&, int) const;

public:
    // Constructors
    Organism() : city(nullptr), Xcoord(0), Ycoord(0), breedCountdown(0), timeSteps(0) {};
    Organism(Habitat*, int, int);
    virtual ~Organism();

    // Organism Methods - Virtual because we need to overload zombie and human
    virtual void breed() = 0;
    virtual void move();
    virtual int getType() = 0;
    virtual bool starve() { return false; }
};