#include "location.h"
#include "level.h"

Location::Location() {
	name	= "";
	level	= nullptr;

	// BUG: DO NOT INVALIDATE LOCATION POINTERS, ALREADY SET BY LEVEL
	/*
	for (Location *location : directions) {
		location = nullptr;
	}
	*/
}

Location::Location(const std::string &name, Level* level) {
	this->name	= name;
	this->level = level;

	// BUG: DO NOT INVALIDATE LOCATION POINTERS, ALREADY SET BY LEVEL
	/*
	for (Location *location : directions) {
		location = nullptr;
	}
	*/
}

Location::~Location() {
	// We only delete what we create, not what we're passed!
}

std::string Location::getName() const {
	return name;
}

Level* Location::getLevel() const {
	return level;
}

Location* Location::getDirection(const DIRECTIONS direction) const {
	return directions[static_cast<int>(direction)];
}

void Location::setName(const std::string &name) {
	this->name = name;
}

void Location::setLevel(Level* level) {
	this->level = level;
}

void Location::setDirection(const DIRECTIONS direction, Location* location) {
	directions[static_cast<int>(direction)] = location;
}
