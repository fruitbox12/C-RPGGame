#pragma once

#include "constants.h"
#include "node.h"
#include <vector>

// Class forwarding
template <typename T1, typename T2>
class Tree;

template <typename T1, typename T2>

class SubTree : public Node<T1, T2> {
	private:
		// The SubTree IS A Node, it has its own root Node, no need to add it.
		// A tree's Nodes are linked off its root Node.
		int								id;
		int								level;
		T1								key;
		T2								value;
		int								size;
		int								nodeSize;
		int								subtreeSize;
		bool							allowDuplicates;

		// SubTree links for a SubTree's own subtrees.
		// The root tree's Subtree's Tree links are always null.
		Tree<T1, T2>*					prevSubtree;
		Tree<T1, T2>*					nextSubtree;

		// Helper functions
		Tree<T1, T2>*					findSubtree(T1 key);
		Node<T1, T2>*					findNode(T1 key);
		std::vector<SubTree<T1, T2>*>	inOrderSubtreeTraversal();




		std::vector<SubTree<T1, T2>*>	inOrderSubtreeTraversal(int level);
		std::vector<std::pair<T1, T2>>	inOrderNodeTraversal();

		// Recursive helper functions
		Tree<T1, T2>*					findSubtreeRecursive(Tree<T1, T2>* subTree, T1 key);
		Node<T1, T2>*					findNodeRecursive(Node<T1, T2>* nextNode, T1 key);
		void							preOrderTraversalRecursive(SubTree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse);
		void							inOrderTraversalRecursive(SubTree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse);
		void							postOrderTraversalRecursive(SubTree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse);



		int								addSubtreeRecursive(Tree<T1, T2>* subTree, Tree<T1, T2>* newTree);
		int								addNodeRecursive(Node<T1, T2>* nextNode, T1 key, T2 value);
		void							inOrderSubtreeTraversalRecursive(SubTree<T1, T2>* nextTree, std::vector<SubTree<T1, T2>*> &traverse);

		// TEMP
		void							inOrderSubtreeTraversalRecursive2(SubTree<T1, T2>* nextTree, std::vector<SubTree<T1, T2>*> &traverse);

		void							inOrderSubtreeTraversalRecursive(SubTree<T1, T2>* nextTree, std::vector<SubTree<T1, T2>*> &traverse, int level);
		void							inOrderNodeTraversalRecursive(Node<T1, T2>* nextNode, std::vector<std::pair<T1, T2>> &traverse);

	public:
		SubTree();
		SubTree(int level, T1 key, bool allowDuplicates = false);
		~SubTree();
	
		// Getters
		int								getNodeId() const;
		int								getLevel() const;
		bool							isRoot() const;
		T1								getKey() const;
		T2								getValue() const;
		int								getSize() const;
		int								getSubtreeSize() const;
		int								getNodeSize() const;
		bool							isEmpty() const;
		bool							duplicatesAllowed() const;
		Tree<T1, T2>*					getPrevSubtree() const;
		Tree<T1, T2>*					getNextSubtree() const;

		// Setters
		void							setLevel(int level);
		void							setKey(T1 key);
		void							setValue(T2 value);
		void							setSize(int size);
		void							setSubtreeSize(int size);
		void							setNodeSize(int size);
		void							setAllowDuplicates(bool allowDuplicates);
		void							setPrevSubtree(Tree<T1, T2>* newTree);
		void							setNextSubtree(Tree<T1, T2>* newTree);
		
		// Traversals:
		// Binary Tree Example:
		//				F (ROOT)
		//		B				G
		// A		D				I
		//		C		E		H

		// Tree Traversals
		// Please see https://en.wikipedia.org/wiki/Tree_traversal
		//
		// Depth First Traversals:
		//
		// Pre-Order Traversal: LEFT-SIDE (PREV) TOP-DOWN, THEN RIGHT-SIDE TOP-DOWN (F-B-A-D-C-E-G-I-H)
		// Used to create a copy of the tree. Also used to get prefix expression on of an expression tree.
		// Please see http://en.wikipedia.org/wiki/Polish_notation
		// to know why prefix expressions are useful.
		std::vector<SubTree<T1, T2>*>	preOrderTraversal();
		void							preOrderTraversal(std::vector<Tree<T1, T2>*> &traverse);

		// In-Order Traversal: LEFT-SIDE (PREV) BOTTOM-UP, THEN RIGHT-SIDE BOTTOM-UP (A-B-C-D-E-F-G-H-I)
		// In case of binary search trees (BST), Inorder traversal gives nodes in increasing order (e.g., alphabetical order)
		std::vector<SubTree<T1, T2>*>	inOrderTraversal();
		void							inOrderTraversal(std::vector<Tree<T1, T2>*> &traverse);

		// Post-Order Traversal: LEFT-SIDE (PREV) BOTTOM-UP, THEN RIGHT-SIDE BOTTOM-UP (A-C-D-E-B-H-I-G-F)
		// Used to delete the tree. Also useful to get the postfix expression of an expression tree.
		// Please see http://en.wikipedia.org/wiki/Reverse_Polish_notation
		// for the usage of postfix expression.
		std::vector<SubTree<T1, T2>*>	postOrderTraversal();
		void							postOrderTraversal(std::vector<Tree<T1, T2>*> &traverse);

		// Breadth First Traversals:
		//
		// Level-Order Traversal: LEFT-SIDE (PREV), THEN RIGHT-SIDE, REPEAT (B-G-A-D-I-C-E-H)
		// Visit every node on a level before going to a lower level.
		std::vector<SubTree<T1, T2>*>	levelOrderTraversal();
		void							levelOrderTraversal(std::vector<Tree<T1, T2>*> &traverse);



		std::vector<SubTree<T1, T2>*>	getSubtreesInOrder(int level);
		std::vector<std::pair<T1, T2>>	getNodesInOrder();

		// Other Tree operations
		int								addSubtree(Tree<T1, T2>* newTree);
		int								addNode(T1 key, T2 value);
		void							updateSubtree();
		void							updateNode();
		void							deleteSubtree();
		void							deleteNode();
		void							copySubtree();
		void							copyNode();
};
