#pragma once

// Grid
const int GRIDSIZE = 20;

// Directions
const int EAST = 1;
const int WEST = 2;
const int SOUTH = 3;
const int NORTH = 4;
const int SOUTH_EAST = SOUTH + EAST; // 4
const int SOUTH_WEST = SOUTH + WEST; // 5
const int NORTH_EAST = NORTH + EAST; // 5
const int NORTH_WEST = NORTH + WEST; // 6

// Organisms
const int PREY_STARTCOUNT = 100;
const int PREDATOR_STARTCOUNT = 5;

const int PREY_TYPE = 1;
const int PREDATOR_TYPE = 2;

const int PREY_SPAWN_TIMER = 3;
const int PREDATOR_CONVERT_TIMER = 8;
const int PREDATOR_STARVE_TIMER = 3;

// Organism styles
const char PREY_CH = 62;	// 62 - ">"
const char SPACE_CH = 45;   // 32 - " "
const char PREDATOR_CH = 60;  // 60 - "<"

const int PREY_COLOR = 3;   // Turquoise
const int PREDATOR_COLOR = 4;  // Red
const int DEFAULT_COLOR = 7; // Default White	

// Run constraints
const int PAUSE_SECONDS = 1;
const int MAX_ITERATIONS = 250;