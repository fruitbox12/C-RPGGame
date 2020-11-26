#pragma once

#include "constants.h"
#include "location.h"
#include <string>
#include <iostream>

// Avoid "include hell" by using "class forwarding". Must include the headers in the actor source file.
class World;
class ActorLevel;
class Level;

class Actor {
	private:
		// Actor object IS and HAS attributes/characteristics
		int				id;
		std::string		name;
		std::string		description;
		ACTOR_TYPES		type;
		bool			moveable;
		DIRECTIONS		direction;
		ActorLevel*		parent;

	public:
		// Actor object CAN DO actions
		// Constructors
		Actor();
		Actor(const std::string &name, const std::string &description, const ACTOR_TYPES type, const bool moveable);

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

		virtual ~Actor();

		// Getters
		int				getId() const;
		std::string		getName() const;
		std::string		getDescription() const;
		ACTOR_TYPES		getType() const;
		std::string		getTypeName() const;
		bool			isMoveable() const;
		DIRECTIONS		getDirection() const;
		ActorLevel*		getParent() const;

		// Ambiguity in Multiple Inheritance:
		// Occurs when a child class has more than one parent class that defines a function with the SAME NAME, REGARDLESS of signature (parameter list)
		//
		// Possible solutions:
		// 1. Use composition instead of multiple inheritance:
		// class ActorLevel : Actor
		//		private:
		//			Level	level
		// 2. Prefix the function call with the name of the class:
		// mountain->Actor::getLocation()		// mountain is an ActorLevel
		// 3. Rename the function in one of the two parent classes to avoid ambiguity:
		// Actor's getLocation() is renamed getMyLocation() 
		Location*		getMyLocation() const;

		// Setters
		void			setName(const std::string &name);
		void			setDescription(const std::string &description);
		void			setType(const ACTOR_TYPES type);
		void			setMoveable(const bool moveable);
		void			setDirection(const DIRECTIONS direction);
		void			setParent(ActorLevel* parent);

		// Child classes MAY opt to implement their own move functions, or use our do-nothing move function (e.g., islands don't move).
		// PURE virtual functions MUST be declared and implemented in ALL child classes: virtual bool move() = 0;
		virtual bool	move();
};
