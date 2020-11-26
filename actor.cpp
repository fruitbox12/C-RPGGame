#include "actor.h"
#include "world.h"
#include "actorlevel.h"
#include "level.h"

Actor::Actor() {
	id					= World::getActorId();
	name				= "";
	description			= "";
	type				= ACTOR_TYPES::DUMMY_ACTOR;
	moveable			= false;
	direction			= DIRECTIONS::NONE;
	parent				= nullptr;
}

Actor::Actor(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable) {
	this->id			= World::getActorId();
	this->name			= name;
	this->description	= description;
	this->type			= type;
	this->moveable		= moveable;
	this->direction		= DIRECTIONS::NONE;
	parent				= nullptr;
}

Actor::~Actor() {
}

int Actor::getId() const {
	return id;
}

std::string Actor::getName() const {
	return name;
}

std::string Actor::getDescription() const {
	return description;
}

ACTOR_TYPES Actor::getType() const {
	return type;
}

std::string	Actor::getTypeName() const {
	return ACTOR_TYPE_NAMES[static_cast<int>(type)];
}

bool Actor::isMoveable() const {
	return moveable;
}

DIRECTIONS Actor::getDirection() const {
	return direction;
}

ActorLevel* Actor::getParent() const {
	return parent;
}

Location* Actor::getMyLocation() const {
	return getParent()->Level::getLocation(this);
}

void Actor::setName(const std::string &name) {
	this->name = name;
}

void Actor::setDescription(const std::string &description) {
	this->description = description;
}

void Actor::setType(const ACTOR_TYPES type) {
	this->type = type;
}

void Actor::setMoveable(const bool moveable) {
	this->moveable = moveable;
}

void Actor::setDirection(const DIRECTIONS direction) {
	this->direction = direction;
}

void Actor::setParent(ActorLevel* parent) {
	this->parent = parent;
}

bool Actor::move() {
	return false;
}
