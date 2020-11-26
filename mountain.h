#pragma once

#include "constants.h"
#include "actorlevel.h"
#include <string>

class Mountain : public ActorLevel {
	private:
		int trees;

	public:
		Mountain();
		Mountain(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const DIRECTIONS direction, const int rows, const int cols);
		~Mountain();
};

