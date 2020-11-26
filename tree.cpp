#include "tree.h"

// Prevent error LNK2001 : unresolved external symbol static int
template <typename T1, typename T2>
int Tree<T1, T2>::nodeId = 0;

template <typename T1, typename T2>
Tree<T1, T2>::Tree() : SubTree<T1, T2>() {
	errors	 = 0;
	warnings = 0;
}

template <typename T1, typename T2>
Tree<T1, T2>::Tree(int level, T1 key, bool allowDuplicates) : SubTree<T1, T2>(level, key, allowDuplicates) {
	errors	 = 0;
	warnings = 0;
}

template <typename T1, typename T2>
Tree<T1, T2>::~Tree() {
	// NOT YET IMPLEMENTED
}

/*
 * Helper functions
 */

 /*
	findTree will return a pointer to the Tree containing the key,
	or nullptr if the key is not found anywhere in the Tree
 */
template <typename T1, typename T2>
Tree<T1, T2>* Tree<T1, T2>::findTree(T1 key) {
	Tree<T1, T2>* tree = nullptr;

	// Get the our Tree's root Node key
	T1 nodeKey = SubTree<T1, T2>::getKey();

	// Check the root Node of our own Tree
	if (key == nodeKey) {
		tree = this;
	}
	else {
		// Recursively check if key comes before our Tree's root Node key
		if (key < nodeKey) {
			Tree<T1, T2>* prevTree = getPrevTree();

			if (prevTree != nullptr) {
				tree = findTreeRecursive(prevTree, key);
			}
		}
		// Key must come after our Tree's root Node key. Recursively check.
		else {
			Tree<T1, T2>* nextTree = getNextTree();

			if (nextTree != nullptr) {
				tree = findTreeRecursive(nextTree, key);
			}
		}
	}

	return tree;
}

/*
 * Recursive Helper Functions
 */

/*
	findTreeRecursive will return a pointer to the Tree containing the root Node key,
	or nullptr if the key is not found anywhere in the Tree
*/
template <typename T1, typename T2>
Tree<T1, T2>* Tree<T1, T2>::findTreeRecursive(Tree<T1, T2>* subTree, T1 key) {
	Tree<T1, T2>* tree = nullptr;

	// Get the subtree's root Node key
	T1 nodeKey = subTree->getKey();

	// Check the subtree's root Node
	if (key == nodeKey) {
		tree = subTree;
	}
	else {
		// Recursively check if key comes before the subtree's root Node key
		if (key < nodeKey) {
			Tree<T1, T2>* prevTree = subTree->getPrevTree();

			if (prevTree != nullptr) {
				tree = findTreeRecursive(prevTree, key);
			}
		}
		// Key must come after the subtree's root Node key. Recursively check.
		else {
			Tree<T1, T2>* nextTree = subTree->getNextTree();

			if (nextTree != nullptr) {
				tree = findTreeRecursive(nextTree, key);
			}
		}
	}

	return tree;
}

template <typename T1, typename T2>
void Tree<T1, T2>::preOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse) {
	// 1. Check if the current node is empty or null.
	// 2. Display the data part of the root(or current node).
	// 3. Traverse the left subtree by recursively calling the pre - order function.
	// 4. Traverse the right subtree by recursively calling the pre - order function.

	if (nextTree != nullptr) {
		// Omit the root Tree
		if (nextTree->getLevel() > 0) {
			traverse.push_back(nextTree);

			// Recurse through this Tree's subtrees
			nextTree->SubTree<T1, T2>::preOrderTraversal(traverse);
		}

		// Recursively traverse the left (previous) tree
		preOrderTraversalRecursive(nextTree->getPrevTree(), traverse);

		// Recursively traverse the right (next) tree
		preOrderTraversalRecursive(nextTree->getNextTree(), traverse);
	}
}

template <typename T1, typename T2>
void Tree<T1, T2>::inOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse) {
	// 1. Check if the current node is empty or null.
	// 2. Traverse the left subtree by recursively calling the in - order function.
	// 3. Display the data part of the root(or current node).
	// 4. Traverse the right subtree by recursively calling the in - order function.

	if (nextTree != nullptr) {
		// Recursively traverse the left (previous) tree
		inOrderTraversalRecursive(nextTree->getPrevTree(), traverse);

		// Recurse through this Tree's subtrees
		nextTree->SubTree<T1, T2>::inOrderTraversal(traverse);

		// Recursively traverse the right (next) tree
		inOrderTraversalRecursive(nextTree->getNextTree(), traverse);
	}
}

template <typename T1, typename T2>
void Tree<T1, T2>::postOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse) {
	// 1. Check if the current node is empty or null.
	// 2. Traverse the left subtree by recursively calling the post - order function.
	// 3. Traverse the right subtree by recursively calling the post - order function.
	// 4. Display the data part of the root(or current node).

	if (nextTree != nullptr) {
		// Recursively traverse the left (previous) tree
		postOrderTraversalRecursive(nextTree->getPrevTree(), traverse);

		// Recursively traverse the right (next) tree
		postOrderTraversalRecursive(nextTree->getNextTree(), traverse);

		// Recurse through this Tree's subtrees
		nextTree->SubTree<T1, T2>::postOrderTraversal(traverse);
	}
}

template <typename T1, typename T2>
void Tree<T1, T2>::levelOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse) {
	
	if (nextTree != nullptr) {
		// Recursively traverse the left (previous) tree
		levelOrderTraversalRecursive(nextTree->getPrevTree(), traverse);

		// Recursively traverse the right (next) tree
		levelOrderTraversalRecursive(nextTree->getNextTree(), traverse);

		// Recurse through this Tree's subtrees
		nextTree->SubTree<T1, T2>::levelOrderTraversal(traverse);
	}
}

template <typename T1, typename T2>
int Tree<T1, T2>::addTreeRecursive(Tree<T1, T2>* subTree, Tree<T1, T2>* newTree) {
	int added = NODE_ADDED;

	// Get the subtree's root Node keys
	T1 subTreeRootNodeKey = subTree->getKey();
	T1 newTreeRootNodeKey = newTree->getKey();

	// If duplicates are not allowed, find out if the new Tree's root Node key is already in the Tree
	// and if so do not add the new Node
	if (!subTree->duplicatesAllowed()) {
		Tree<T1, T2>* tree = findTree(newTreeRootNodeKey);
		if (tree != nullptr) {
			added = DUPLICATE_NODE;
		}
	}

	if (added != DUPLICATE_NODE) {
		// Recursively check if the new Tree's root Node key
		// is equal to the root Node key or comes before it
		if (newTreeRootNodeKey <= subTreeRootNodeKey) {
			Tree<T1, T2>* prevTree = nullptr;

			// Compare level numbers. If same, link newTree as previous Tree
			if (newTree->getLevel() == 1 || (newTree->getLevel() == subTree->getLevel())) {
				prevTree = subTree->getPrevTree();

				if (prevTree == nullptr) {
					// Add the new Tree to the root tree
					subTree->setPrevTree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(prevTree, newTree);
				}
			}
			else {
				prevTree = subTree->getPrevSubtree();

				if (prevTree == nullptr) {
					// Add the new Tree to the parent tree
					subTree->setPrevSubtree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(prevTree, newTree);
				}
			}
		}
		// The new Tree's root Node key must come after the subtree's Node key. Recursively check.
		else {
			Tree<T1, T2>* nextTree = nullptr;

			if (newTree->getLevel() == 1) {
				nextTree = subTree->getNextTree();

				if (nextTree == nullptr) {
					// Add the new Tree to the root tree
					subTree->setNextTree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(nextTree, newTree);
				}
			}
			else {
				nextTree = subTree->getNextSubtree();

				if (nextTree == nullptr) {
					// Add the new Tree to the parent tree
					subTree->setNextSubtree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(nextTree, newTree);
				}
			}
		}
	}

	return added;
}

/*
 * Getters
 */

template <typename T1, typename T2>
int Tree<T1, T2>::genNodeId() {
	// Increment, then return the new Node id
	return ++nodeId;
}

template <typename T1, typename T2>
int Tree<T1, T2>::getErrors() const {
	return errors;
}

template <typename T1, typename T2>
int Tree<T1, T2>::getWarnings() const {
	return warnings;
}

template <typename T1, typename T2>
Tree<T1, T2>* Tree<T1, T2>::getPrevTree() const {
	return prevTree;
}

template <typename T1, typename T2>
Tree<T1, T2>* Tree<T1, T2>::getNextTree() const {
	return nextTree;
}

/*
 * Setters
 */

template <typename T1, typename T2>
void Tree<T1, T2>::setErrors(int errors) {
	this->errors = errors;
}

template <typename T1, typename T2>
void Tree<T1, T2>::setWarnings(int warnings) {
	this->warnings = warnings;
}

template <typename T1, typename T2>
void Tree<T1, T2>::setPrevTree(Tree<T1, T2>* newTree) {
	prevTree = newTree;
}

template <typename T1, typename T2>
void Tree<T1, T2>::setNextTree(Tree<T1, T2>* newTree) {
	nextTree = newTree;
}

/*
 * Traversals
 */

template <typename T1, typename T2>
std::vector<Tree<T1, T2>*> Tree<T1, T2>::preOrderTraversal() {
	// 1. Check if the current node is empty or null.
	// 2. Display the data part of the root(or current node).
	// 3. Traverse the left subtree by recursively calling the pre - order function.
	// 4. Traverse the right subtree by recursively calling the pre - order function.

	std::vector<Tree<T1, T2>*> traverse;

	// Recursively begin at the root tree
	preOrderTraversalRecursive(this, traverse);

	return traverse;
}

template <typename T1, typename T2>
std::vector<Tree<T1, T2>*> Tree<T1, T2>::inOrderTraversal() {
	// 1. Check if the current node is empty or null.
	// 2. Traverse the left subtree by recursively calling the in - order function.
	// 3. Display the data part of the root(or current node).
	// 4. Traverse the right subtree by recursively calling the in - order function.

	std::vector<Tree<T1, T2>*> traverse;

	// Recursively begin at the root tree
	inOrderTraversalRecursive(this, traverse);

	return traverse;
}

template <typename T1, typename T2>
std::vector<Tree<T1, T2>*> Tree<T1, T2>::postOrderTraversal() {
	// 1. Check if the current node is empty or null.
	// 2. Traverse the left subtree by recursively calling the post - order function.
	// 3. Traverse the right subtree by recursively calling the post - order function.
	// 4. Display the data part of the root(or current node).

	std::vector<Tree<T1, T2>*> traverse;

	// Recursively begin at the root tree
	postOrderTraversalRecursive(this, traverse);

	return traverse;
}

template <typename T1, typename T2>
std::vector<Tree<T1, T2>*> Tree<T1, T2>::levelOrderTraversal() {
	std::vector<Tree<T1, T2>*> traverse;

	// Recursively begin at the root tree
	levelOrderTraversalRecursive(this, traverse);

	return traverse;
}

/*
 * Other Tree operations
 */

template <typename T1, typename T2>
Tree<T1, T2>* Tree<T1, T2>::findTree() {
	// NOT YET IMPLEMENTED
	return nullptr;
}

template <typename T1, typename T2>
int Tree<T1, T2>::addTree(Tree<T1, T2>* newTree) {
	int added = NODE_ADDED;

	// Get the parent Tree keys
	T1 parentRootNodeKey	= SubTree<T1, T2>::getKey();
	T1 newTreeRootNodeKey	= newTree->getKey();

	// If duplicates are not allowed, find out if the new Tree's parent Node key is already in the Tree
	// and if so do not add the new Tree
	if (!SubTree<T1, T2>::duplicatesAllowed()) {
		Tree<T1, T2>* tree = Tree<T1,T2>::findTree(newTreeRootNodeKey);
		if (tree != nullptr) {
			added = DUPLICATE_NODE;
		}
	}

	if (added != DUPLICATE_NODE) {
		// Recursively check if the new Tree's root Node key
		// is equal to the parent root Node key or comes before it
		if (newTreeRootNodeKey <= parentRootNodeKey) {
			Tree<T1, T2>* prevTree = nullptr;

			if (newTree->getLevel() == 1) {
				prevTree = getPrevTree();

				if (prevTree == nullptr) {
					// Add the new Tree to the root tree
					setPrevTree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(prevTree, newTree);
				}
			}
			else {
				prevTree = SubTree<T1, T2>::getPrevSubtree();

				if (prevTree == nullptr) {
					// Add the new Tree to the parent tree
					SubTree<T1, T2>::setPrevSubtree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(prevTree, newTree);
				}
			}
		}
		// The new Tree's root Node key must come after the parent Tree root Node key. Recursively check.
		else {
			Tree<T1, T2>* nextTree = nullptr;

			if (newTree->getLevel() == 1) {
				nextTree = getNextTree();

				if (nextTree == nullptr) {
					// Add the new Tree to the root tree
					setNextTree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(prevTree, newTree);
				}
			}
			else {
				nextTree = SubTree<T1, T2>::getNextSubtree();

				if (nextTree == nullptr) {
					// Add the new Tree to the parent tree
					SubTree<T1, T2>::setNextSubtree(newTree);

					SubTree<T1, T2>::setSize(SubTree<T1, T2>::getSize() + 1);
					SubTree<T1, T2>::setSubtreeSize(SubTree<T1, T2>::getSubtreeSize() + 1);
				}
				else {
					added = addTreeRecursive(nextTree, newTree);
				}
			}
		}
	}

	return added;
}
