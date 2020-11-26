#include "mountain.h"

Mountain::Mountain() {
	trees = 0;
}

Mountain::Mountain(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable, const DIRECTIONS direction, const int rows, const int cols) : ActorLevel(name, description, type, moveable, direction, rows, cols) {
	trees = 100;
}

Mountain::~Mountain() {
}
