#pragma once

#include "actorlevel.h"
#include "rules.h"

// The top level
// OOP Inheritance: World "IS A" ActorLevel
class World : public ActorLevel {
	private:
		static int		actorId;
		static Rules*	rules;

	public:
		World();
		World(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const int rows, const int cols);
		~World();

		// Getters
		static int		getActorId();
		static Rules*	getRules();
};
