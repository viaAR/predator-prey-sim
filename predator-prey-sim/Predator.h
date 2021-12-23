#pragma once

#include "Organism.h"

class Predator : public Organism {
private:
    int starveCountdown;
    vector<int> scanForPrey(int, int) const;

public:
    // Constructors
    Predator() : Organism(), starveCountdown(0) {}
    Predator(Habitat* city, int zX, int zY);
    virtual ~Predator();

    // Predator Methods
    void breed();
    void move();
    int getType() { return PREDATOR_TYPE; }
    bool starve();
};