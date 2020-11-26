#include "world.h"

// Prevent error LNK2001 : unresolved external symbol "private: static int, Rules*
int World::actorId	= 0;
Rules* World::rules = nullptr;

World::World() {
	rules = new Rules();
}

// Child class constructors must initialize their parent constructors thru initialzer lists (:)
World::World(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const int rows, const int cols) : ActorLevel(name, description, type, moveable, DIRECTIONS::NONE, rows, cols) {
	rules = new Rules();
}

World::~World() {
	delete rules;
}

int World::getActorId() {
	// Increment, then return the new Actor id
	return ++actorId;
}

Rules* World::getRules() {
	return rules;
}
