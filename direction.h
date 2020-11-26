#pragma once

#include "direction.h"
#include "level.h"
#include "constants.h"

// Avoid "include hell" by using "class forwaring". Must include location.h in the direction source file.
class Location;

class Direction {
	private:
		Location*		location;
		
	public:
		// Default constructor (no parameters)
		Direction();
		Direction(Location* location);
		~Direction();

		// Getters
		Location* getLocation();

		// Setters
		void setLocation(Location* location);
};

