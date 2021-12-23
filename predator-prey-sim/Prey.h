#pragma once

#include "Organism.h"

class Prey : public Organism {

public:
    // Constructors
    Prey() : Organism() {};
    Prey(Habitat* city, int hX, int hY);
    virtual ~Prey();

    // Human Methods
    void breed();
    int getType() { return PREY_TYPE; }
};