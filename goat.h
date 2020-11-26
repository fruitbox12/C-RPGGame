#pragma once

#include "constants.h"
#include "actor.h"
#include <string>

class Goat : public Actor {
	private:
		int	legs;

	public:
		Goat();
		Goat(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const DIRECTIONS direction);
		~Goat();

		bool move() override;
};

