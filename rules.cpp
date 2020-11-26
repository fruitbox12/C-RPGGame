#include "rules.h"

// Avoid linker errors
#include "tools.cpp"
#include "tree.cpp"
#include "subtree.cpp"
#include "node.cpp"

Rules::Rules() {
	// Add DIRECTIONS enum to Directions
	directions.emplace(std::make_pair("none", -1));
	directionIndexes.emplace(std::make_pair(-1, "none"));

	for (int direction = 0; direction < static_cast<int>(DIRECTIONS::COUNT); direction++) {
		directions.emplace(std::make_pair(DIRECTION_NAMES[direction], direction));
		directionIndexes.emplace(std::make_pair(direction, DIRECTION_NAMES[direction]));
	}

	// Read the Rules file into Rules object
	create();
}

Rules::~Rules() {
}

int Rules::getDirections() const {
	return directions.size();
}

int Rules::getDirection(const std::string &name) const {
	int direction = directions.find("none")->second;

	const std::map<const std::string, int>::const_iterator iterator = directions.find(name);

	// Check if the Actor was found
	if (iterator != directions.end()) {
		direction = iterator->second;
	}

	return direction;
}

std::vector<std::string> Rules::getMessages() const {
	return messages;
}

bool Rules::create() {
	bool valid			= true;
	bool nameFound		= false;
	bool nameValid		= false;
	bool aliasesFound	= false;
	std::string name	= "";

	std::vector<std::string> errors;
	std::vector<std::string> warnings;

	Tree<std::string, std::string>* rootTree = Tools::XMLParser(DATA_PATH, RULES_FILE_NAME, messages);

	// Test pre-order traversal
	std::vector<Tree<std::string, std::string>*> preOrderTraverse = rootTree->preOrderTraversal();
	std::vector<Tree<std::string, std::string>*> inOrderTraverse = rootTree->inOrderTraversal();
	std::vector<Tree<std::string, std::string>*> postOrderTraverse = rootTree->postOrderTraversal();

	if (rootTree->getSize() > 0 && rootTree->getErrors() == 0) {
		if (rootTree->getSubtreeSize() > 0) {

			// Get the root subtrees
			std::vector<Tree<std::string, std::string>*> rootSubTrees = rootTree->getTreesInOrder();

			for (Tree<std::string, std::string>* rootSubTree : rootSubTrees) {
				if (rootSubTree->getKey() == "directions") {

					// Get the first direction subtree
					SubTree<std::string, std::string>* directionSubTree = rootSubTree->getPrevSubtree();

					// Get the remaining direction subtrees
					std::vector<Tree<std::string, std::string>*> nextDirectionTrees = static_cast<Tree<std::string, std::string>*>(directionSubTree)->getTreesInOrder();
						
					//std::vector<Tree<std::string, std::string>*> nextDirectionTrees = static_cast<Tree<std::string, std::string>*>(directionSubTree)->getTreesInOrder();

					for (Tree<std::string, std::string>* nextDirectionTree : nextDirectionTrees) {
						if (nextDirectionTree->getKey() == "direction") {
							// Get the direction nodes. There should be a single <name> node
							std::vector<std::pair<std::string, std::string>> directionNodes = nextDirectionTree->getNodesInOrder();

							if (!directionNodes.empty()) {
								nameFound	= false;
								nameValid	= false;

								for (const std::pair<std::string, std::string> &directionNode : directionNodes) {
									if (directionNode.first == "name") {
										if (!nameFound) {
											name = directionNode.second;
											nameFound = true;
											
											// Validate direction name
											if (directions.find(name) != directions.end()) {
												nameValid = true;
											}
										}
										else {
											errors.emplace_back("Rules::create(): <directions>: duplicate <name> tag found");
										}
									}
									else {
										errors.emplace_back("Rules::create(): <directions>: unknown tag found: <" + directionNode.first + ">");
									}
								}
							}
							else {
								errors.emplace_back("Rules::create(): <directions>: no tags found");
							}

							// Get the aliases subtree. There should be a single <aliases> subtree
							std::vector<SubTree<std::string, std::string>*> subtrees = nextDirectionTree->getSubtreesInOrder();

							std::vector<Tree<std::string, std::string>*> aliasesSubTrees = nextDirectionTree->getPrevSubtree()->getTreesInOrder();

							if (!aliasesSubTrees.empty()) {
								aliasesFound = false;

								for (SubTree<std::string, std::string>* aliasesSubTree : aliasesSubTrees) {
									if (aliasesSubTree->getKey() == "aliases") {
										if (!aliasesFound) {

											// Get the aliases nodes
											std::vector<std::pair<std::string, std::string>> aliasesNodes = aliasesSubTree->getNodesInOrder();

											if (!aliasesNodes.empty()) {
												aliasesFound = true;

												for (std::pair<std::string, std::string> aliasNode : aliasesNodes) {
													if (!directionAliases.emplace(std::make_pair(aliasNode.second, name)).second) {
														errors.push_back("Rules::create(): <directions>: duplicate <alias> tag found: " + aliasNode.second);
													}
												}
											}
											else {
												errors.emplace_back("Rules::create(): <directions> <aliases>: no tags found");
											}
										}
										else {
											errors.emplace_back("Rules::create(): <directions>: duplicate <aliases> tag found");
										}
									}
									else {
										errors.emplace_back("Rules::create(): <directions>: unknown tag found: <" + aliasesSubTree->getKey() + ">");
									}
								}
							}
							else {
								errors.emplace_back("Rules::create(): <directions>: no <aliases> tag found");
							}
						}
					}
				}
				else if (rootSubTree->getKey() == "relational-directions") {
					
				}
			}
		}
		else {
			errors.emplace_back("Rules::create(): No Rules found");
		}
	}
	else {
		errors.emplace_back("Rules::create(): Rules file is empty or was not found");
	}

	if (!errors.empty()) {
		messages.insert(messages.begin(), errors.begin(), errors.end());
		valid = false;
	}

	if (!warnings.empty()) {
		messages.insert(messages.end(), warnings.begin(), warnings.end());
	}

	return valid;
}
