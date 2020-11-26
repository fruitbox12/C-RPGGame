#pragma once

#include "actor.h"
#include "level.h"

// Multiple inheritance
class ActorLevel : public Actor, public Level {
	private:

	public:
		ActorLevel();
		ActorLevel(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const DIRECTIONS direction, const int rows, const int cols);
		virtual ~ActorLevel();

		// Setters
		bool		add(Actor* actor);
		bool		add(Actor* actor, Location* location, const DIRECTIONS direction);
		bool		add(Actor* actor, const int row, const int col, const DIRECTIONS direction);
};

