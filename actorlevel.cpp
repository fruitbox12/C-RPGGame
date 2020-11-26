#include "actorlevel.h"

ActorLevel::ActorLevel() {
}

// Child class constructors must initialize their parent constructors thru initialzer lists (:)
ActorLevel::ActorLevel(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const DIRECTIONS direction, const int rows, const int cols) : Actor(name, description, type, moveable), Level(rows, cols) {
}

ActorLevel::~ActorLevel() {
}

// Pass the ActorLevel parent information (this)
bool ActorLevel::add(Actor* actor) {
	return Level::add(actor, this);
}

// Pass the ActorLevel parent information (this)
bool ActorLevel::add(Actor* actor, Location* location, const DIRECTIONS direction) {
	return Level::add(actor, location, direction, this);
}

// Pass the ActorLevel parent information (this)
bool ActorLevel::add(Actor* actor, const int row, const int col, const DIRECTIONS direction) {
	return Level::add(actor, row, col, direction, this);
}
