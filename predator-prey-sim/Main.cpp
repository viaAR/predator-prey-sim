#include <iostream>
#include "Habitat.h"

using namespace std;

int main() {

    // Prompt the user to start the simulation
    cout << "Press enter to start the simulation";
    cin.get();

    // Timer to run each timestep
    chrono::seconds interval(PAUSE_SECONDS);

    // Initialize the city
    Habitat city;

    // Populate the city
    city.run();

    // Color the symbols in the legend
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 1; i <= MAX_ITERATIONS; ++i)
    {
        city.render();

        // City population
        cout << "GENERATION: " << city.getTimeSteps() << endl;
        
        // Prey tracker
        SetConsoleTextAttribute(hConsole, PREY_COLOR);
        cout << PREY_CH;
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
        cout << " " << city.getActivePrey() << endl;

        // Predator tracker
        SetConsoleTextAttribute(hConsole, PREDATOR_COLOR);
        cout << PREDATOR_CH;
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
        cout << " " << city.getActivePredators() << endl;

        // Check for an extinction
        if (city.getActivePrey() <= 0 || city.getActivePredators() <= 0)
        {
            cout << "Extinction has occured!";
            exit(0);
        }

        city.nextTimeStep();

        this_thread::sleep_for(interval);
    }
}