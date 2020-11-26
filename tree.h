#pragma once

#include "subtree.h"
#include <map>
#include <string>
#include <vector>

template <typename T1, typename T2>

class Tree : public SubTree<T1, T2> {
	private:
		static int					nodeId;
		int							errors;
		int							warnings;
		static std::map<int, T1>	nodeDirectory;

		// Additional set of Tree links for Subtrees of the root Tree
		Tree<T1, T2>*				prevTree;
		Tree<T1, T2>*				nextTree;

		// Helper functions
		Tree<T1, T2>*				findTree(T1 key);

		// Recursive helper functions
		Tree<T1, T2>*				findTreeRecursive(Tree<T1, T2>* subTree, T1 key);
		void						preOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse);
		void						inOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse);
		void						postOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse);
		void						levelOrderTraversalRecursive(Tree<T1, T2>* nextTree, std::vector<Tree<T1, T2>*> &traverse);




		int							addTreeRecursive(Tree<T1, T2>* subTree, Tree<T1, T2>* newTree);
	
	public:
		Tree();
		Tree(int level, T1 key, bool allowDuplicates = false);
		~Tree();

		// Getters
		static int					genNodeId();
		int							getErrors() const;
		int							getWarnings() const;
		Tree<T1, T2>*				getPrevTree() const;
		Tree<T1, T2>*				getNextTree() const;
		
		// Setters
		void						setErrors(int errors);
		void						setWarnings(int warnings);
		void						setPrevTree(Tree<T1, T2>* newTree);
		void						setNextTree(Tree<T1, T2>* newTree);
		
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
		std::vector<Tree<T1, T2>*>	preOrderTraversal();

		// In-Order Traversal: LEFT-SIDE (PREV) BOTTOM-UP, THEN RIGHT-SIDE BOTTOM-UP (A-B-C-D-E-F-G-H-I)
		// In case of binary search trees (BST), Inorder traversal gives nodes in increasing order (e.g., alphabetical order)
		std::vector<Tree<T1, T2>*>	inOrderTraversal();

		// Post-Order Traversal: LEFT-SIDE (PREV) BOTTOM-UP, THEN RIGHT-SIDE BOTTOM-UP (A-C-D-E-B-H-I-G-F)
		// Used to delete the tree. Also useful to get the postfix expression of an expression tree.
		// Please see http://en.wikipedia.org/wiki/Reverse_Polish_notation
		// for the usage of postfix expression.
		std::vector<Tree<T1, T2>*>	postOrderTraversal();

		// Breadth First Traversals:
		//
		// Level-Order Traversal: LEFT-SIDE (PREV), THEN RIGHT-SIDE, REPEAT (B-G-A-D-I-C-E-H)
		// Visit every node on a level before going to a lower level.
		std::vector<Tree<T1, T2>*>	levelOrderTraversal();

		// Other Tree operations
		Tree<T1, T2>*				findTree();
		int							addTree(Tree<T1, T2>* newTree);
};
