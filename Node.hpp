#ifndef NODE_HPP
#define NODE_HPP

#include "Lane.hpp"

class Node {
private:
	//pointer to the vehicle class
	Vehicle* veh;
	//pointer for the node class, that points to the next instance of "node"
	Node *next;
public:
	// constructor of the node class, that takes in a pointer to a vehicle
	Node(Vehicle* a);
	// takes in an arbitrary pointer and stores it to the "next" pointer of node
	void setNext(Node *n);
	// returns the pointer "next"
	Node* getNext() const;
	// returns the vehicle pointer stored by the constructor
	Vehicle* getPointer() const;
	// destructor for the node class
	virtual ~Node();
};

#endif
