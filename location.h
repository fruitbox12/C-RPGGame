#pragma once

#include "constants.h"
#include <string>

// Avoid "include hell" by using "class forwaring". Must include level.h in the location source file.
class Level;

class Location {
	private:
		std::string		name;
		Level*			level;
		Location*		directions[static_cast<int>(DIRECTIONS::COUNT)];
		
	public:
		Location();
		Location(const std::string &name, Level* level);
		~Location();

		// Getters
		std::string		getName() const;
		Level*			getLevel() const;
		Location*		getDirection(const DIRECTIONS direction) const;

		// Setters
		void			setName(const std::string &name);
		void			setLevel(Level* level);
		void			setDirection(const DIRECTIONS direction, Location* location);
};

