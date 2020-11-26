#include "level.h"
#include "world.h"
#include "actorlevel.h"

Level::Level() {
	rows		= 0;
	cols		= 0;
	rules		= World::getRules();
	level		= nullptr;
}

Level::Level(const int rows, const int cols) {
	this->rows		= rows;
	this->cols		= cols;
	this->rules		= World::getRules();

	// Create a two-dimensional array:
	// 1. Create the rows (subtract the rows pointer)
	level = new Location**[rows];

	// 2. Create the cols for each row (subtract the cols pointer)
	for (int row = 0; row < rows; row++) {
		level[row] = new Location*[cols];
	}

	// 3. Initialize the contents of the array
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			level[row][col] = new Location("r" + std::to_string(row) + ", c" + std::to_string(col), this);

			for (int direction = 0; direction < static_cast<int>(DIRECTIONS::COUNT); direction++) {
				switch (direction) {
					case static_cast<int>(DIRECTIONS::NORTH) : {
						// Top row (0) columns do not have Location neighbors to the NORTH yet
						if (row == 0) {
							level[row][col]->setDirection(DIRECTIONS::NORTH, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::NORTH, level[row - 1][col]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::SOUTH) : {
						// Bottom row (rows - 1) columns do not have Location neighbors to the SOUTH yet
						if (row == rows - 1) {
							level[row][col]->setDirection(DIRECTIONS::SOUTH, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::SOUTH, level[row + 1][col]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::EAST) : {
						// Last col (cols - 1) rows do not have Location neighbors to the EAST yet
						if (col == col - 1) {
							level[row][col]->setDirection(DIRECTIONS::EAST, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::EAST, level[row][col + 1]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::WEST) : {
						// First col (0) rows do not have Location neighbors to the WEST yet
						if (col == 0) {
							level[row][col]->setDirection(DIRECTIONS::WEST, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::WEST, level[row][col - 1]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::NORTHEAST) : {
						// Top row (0) columns do not have Location neighbors to the NORTHEAST yet
						if (row == 0) {
							level[row][col]->setDirection(DIRECTIONS::NORTHEAST, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::NORTHEAST, level[row - 1][col + 1]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::NORTHWEST) : {
						// Top row (0) columns do not have Location neighbors to the NORTHWEST yet
						if (row == 0) {
							level[row][col]->setDirection(DIRECTIONS::NORTHWEST, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::NORTHWEST, level[row - 1][col - 1]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::SOUTHEAST) : {
						// Bottom row (rows - 1) columns do not have Location neighbors to the SOUTH yet
						if (row == rows - 1) {
							level[row][col]->setDirection(DIRECTIONS::SOUTHEAST, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::SOUTHEAST, level[row + 1][col + 1]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::SOUTHWEST) : {
						// Bottom row (rows - 1) columns do not have Location neighbors to the SOUTH yet
						if (row == rows - 1) {
							level[row][col]->setDirection(DIRECTIONS::SOUTHWEST, nullptr);
						}
						else {
							level[row][col]->setDirection(DIRECTIONS::SOUTHWEST, level[row + 1][col - 1]);
						}

						break;
					}
					case static_cast<int>(DIRECTIONS::UP) : {
						// Locations do not have neighbors above yet
						level[row][col]->setDirection(DIRECTIONS::UP, nullptr);

						break;
					}
					case static_cast<int>(DIRECTIONS::DOWN) : {
						// Locations do not have neighbors below yet
						level[row][col]->setDirection(DIRECTIONS::DOWN, nullptr);

						break;
					}
				}
			}
		}
	}
}

Level::~Level() {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			delete level[row][col];
		}
	}

	delete[] level;
}

int Level::getRows() const {
	return rows;
}

int Level::getCols() const {
	return cols;
}

Location* Level::getLocation(const int row, const int col) const {
	// Hope you called my getRows() and getCols() first!
	// You need to pass me array indexes, not row and col numbers!
	return level[row][col];
}

Location* Level::getLocation(const Actor* actor) const {
	Location* location = nullptr;

	const std::map<const Actor*, Location*>::const_iterator iterator = actorDirectory.find(actor);

	// Check if the Actor was found
	if (iterator != actorDirectory.end()) {
		location = iterator->second;
	}
	else {
		// Actor not found, blank Location returned
		location = new Location();
	}

	return location;
}

Location* Level::getLocation(const ActorLevel* actor) const {
	Location* location = nullptr;

	const std::map<const Actor*, Location*>::const_iterator iterator = actorDirectory.find(actor);

	// Check if the Actor was found
	if (iterator != actorDirectory.end()) {
		location = iterator->second;
	}
	else {
		// Actor not found, blank Location returned
		location = new Location();
	}

	return location;
}

void Level::setDirection(Location* location, const DIRECTIONS direction, Location* directionLocation) {
	location->setDirection(direction, directionLocation);
}

bool Level::add(Actor* actor, ActorLevel* parent) {
	bool added = false;

		const std::map<const Actor*, Location*>::const_iterator iterator = actorDirectory.find(actor);

		// Add the Actor if not already on this Level's Actor directory
		if (iterator == actorDirectory.end()) {
			// Randomly select a Location
			const std::uniform_int_distribution<int> randomRow{ 1, static_cast<int>(rows) };
			const int row = randomRow(mersenneTwisterEngine);
			const std::uniform_int_distribution<int> randomCol{ 1, static_cast<int>(cols) };
			const int col = randomCol(mersenneTwisterEngine);

			actorDirectory.emplace(std::make_pair(actor, level[row - 1][col - 1]));
			locationDirectory.emplace(std::make_pair(level[row - 1][col - 1], actor));

			// Randomly select a DIRECTION
			const std::uniform_int_distribution<int> randomDirection{ 1, static_cast<int>(DIRECTIONS::COUNT) };
			const int direction = randomDirection(mersenneTwisterEngine);

			// Update the Actor's DIRECTION
			actor->setDirection(static_cast<DIRECTIONS>(direction));

			// Update the Actor's parent
			actor->setParent(parent);
			
			added = true;
		}

	return added;
}

bool Level::add(Actor* actor, Location* location, const DIRECTIONS direction, ActorLevel* parent) {
	bool added = false;

	// Long way
	/*
	const std::pair<std::map<Actor*, Location*>::iterator, bool> result = actorDirectory.emplace(std::make_pair(actor, location));

	if (result.second) {
		added = true;
	}
	*/

	if (actorDirectory.emplace(std::make_pair(actor, location)).second) {
		// Update the Actor's DIRECTION
		actor->setDirection(direction);
		// Update the Actor's parent
		actor->setParent(parent);

		added = true;
	}

	return added;
}

bool Level::add(Actor* actor, const int row, const int col, const DIRECTIONS direction, ActorLevel* parent) {
	bool added = false;

	const std::map<const Actor*, Location*>::const_iterator iterator = actorDirectory.find(actor);

	// Add the Actor if not already on this Level's Actor directory
	if (iterator == actorDirectory.end()) {
		// Validate the requested row and col
		if (row >= 1 && row <= rows && col >= 1 && col <= cols) {
			actorDirectory.emplace(std::make_pair(actor, level[row - 1][col - 1]));
			locationDirectory.emplace(std::make_pair(level[row - 1][col - 1], actor));

			// Update the Actor's DIRECTION
			actor->setDirection(direction);
			// Update the Actor's parent
			actor->setParent(parent);

			added = true;
		}
	}

	return added;
}
