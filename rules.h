#pragma once

#include "constants.h"
#include "tools.h"
#include <string>
#include <vector>
#include <map>

class Rules {
	private:
		std::map<std::string, int>				directions;
		std::map<int, std::string>				directionIndexes;
		std::map<std::string, std::string>		directionAliases;
		std::vector<std::string>				messages;

		// Helper functions
		bool create();

	public:
		Rules();
		~Rules();
		 
		// Getters
		int										getDirections() const;
		int										getDirection(const std::string &name) const;
		std::vector<std::string>				getMessages() const;
};
