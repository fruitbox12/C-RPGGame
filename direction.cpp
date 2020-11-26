#include "direction.h"
#include "location.h"

Direction::Direction() {
	location	= nullptr;
}

Direction::Direction(Location* location) {
	this->location	= location;
}

Direction::~Direction() {
	// Only delete what you create, not what you are passed!
}

Location* Direction::getLocation() {
	return location;
}

void Direction::setLocation(Location* location) {
	this->location = location;
}

