#include "node.h"
#include "tree.h"

template <typename T1, typename T2>
// Shows how to use the initializer list to tell c++11 or later compiler to init the templated
// class variables to the default values for their actual types.
// Prior to c++11:
// Node<T1, T2>::Node() : key(), value() {
// }
Node<T1, T2>::Node() : key {}, value {}  {
	id		= Tree<T1, T2>::genNodeId();
	empty	= true;
	prev	= nullptr;
	next	= nullptr;
}

template <typename T1, typename T2>
Node<T1,T2>::Node(T1 key, T2 value) {
	id			= Tree<T1, T2>::genNodeId();;
	this->key	= key;
	this->value = value;
	empty		= false;
	prev		= nullptr;
	next		= nullptr;
}

template <typename T1, typename T2>
Node<T1,T2>::~Node() {
}

/*
 * Getters
 */

template <typename T1, typename T2>
int	Node<T1, T2>::getNodeId() const {
	return id;
}

template <typename T1, typename T2>
T1 Node<T1,T2>::getNodeKey() const {
	return key;
}

template <typename T1, typename T2>
T2 Node<T1,T2>::getNodeValue() const {
	return value;
}

template <typename T1, typename T2>
bool Node<T1, T2>::isEmpty() const {
	return empty;
}

template <typename T1, typename T2>
Node<T1,T2>* Node<T1,T2>::getPrev() const {
	return prev;
}

template <typename T1, typename T2>
Node<T1,T2>* Node<T1,T2>::getNext() const {
	return next;
}

/*
 * Setters
 */

template <typename T1, typename T2>
void Node<T1, T2>::setKey(T1 key) {
	this->key	= key;
	empty		= false;
}

template <typename T1, typename T2>
void Node<T1, T2>::setValue(T2 value) {
	this->value = value;
}

template <typename T1, typename T2>
void Node<T1,T2>::setPrev(Node<T1,T2>* prev) {
	this->prev = prev;
}

template <typename T1, typename T2>
void Node<T1,T2>::setNext(Node<T1,T2>* next) {
	this->next = next;
}
