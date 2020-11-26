#pragma once

#include "constants.h"
#include "location.h"
#include "actor.h"
#include "rules.h"
#include <map>
#include <random>		// For std::random_device and std::mt19937
#include <string>

// Avoid "include hell" by using "class forwaring". Must include level.h in the location source file.
class World;
class ActorLevel;

// Best for performance to create it only once.
// C++11 std::mt19937 provides pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
static std::mt19937 mersenneTwisterEngine{ std::random_device{}() };

class Level {
	private:
		int									rows;
		int									cols;
		Rules*								rules;
		Location***							level;
		std::map<const Actor*, Location*>	actorDirectory;
		std::multimap<Location*, Actor*>	locationDirectory;

	public:
		Level();
		Level(const int rows, const int cols);

		// A parent class that has a virtual function is called "a polymorphic class".
		// A parent class must have at least one virtual function:
		//
		// 1. To avoid "Object Slicing" (the loss of child class variable data when storing
		//	  child objects in a variable of type parent class):
		//
		// A. DO NOT USE AUTOMATIC OBJECTS!
		// B. MAKE SURE AT LEAST ONE PARENT CLASS FUNCTION IS VIRTUAL!
		//
		// Problem example:
		// class Actor
		// class Island : public Actor {
		//	 private:
		//		int		volcanoes;	
		// }
		//
		//	If you create an instance/object of the parent class, you will lose your Child's instance variables (volcanoes)!
		//	Actor* island = new Island();
		//
		//	Declare the array of Actor type to be able to store all kinds of Actor objects:
		//	Actor** actors[10];
		//	Actor* cuba = new Island()
		//	actors[0] = cuba;
		//	Actor* puertorico = new Island()
		//	actors[1] = puertorico;
		//	Actor* goat = new Goat()
		//	actors[2] = goat;
		//
		// 2  To avoid memory leaks:
		//    Destructor should be declared virtual in parent class and child classes.
		//	  If your clild class destructor is virtual then objects will be deleted
		//	  in order (first child object destructor is called then parent object destructor).
		//	  If your child class destructor is NOT virtual then only parent class objects
		//	  will get deleted. There will be memory leak for child object.
		//
		// 3. In order to use dynamic_cast<>

		virtual ~Level();

		// Getters
		int			getRows() const;
		int			getCols() const;
		Location*	getLocation(const int row, const int col) const;
		Location*	getLocation(const Actor* actor) const;
		Location*	getLocation(const ActorLevel* actor) const;

		// Setters
		void		setDirection(Location* location, const DIRECTIONS direction, Location* directionLocation);
		bool		add(Actor* actor, ActorLevel* parent);
		bool		add(Actor* actor, Location* location, const DIRECTIONS direction, ActorLevel* parent);
		bool		add(Actor* actor, const int row, const int col, const DIRECTIONS direction, ActorLevel* parent);
};
