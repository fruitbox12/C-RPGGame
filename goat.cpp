#include "goat.h"

Goat::Goat() {
	legs = 0;
}

Goat::Goat(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const DIRECTIONS direction) : Actor(name, description, type, moveable) {
	legs = 4;
}

Goat::~Goat() {
}

bool Goat::move() {
	return true;
}