#include "Node.hpp"

Node::Node(Vehicle* a){
	veh = a;
	next = 0;
}

void Node::setNext(Node* n) {
	next = n;
}

Node* Node::getNext() const {
	return next;
}

Vehicle* Node::getPointer() const {
	return veh;
}

Node::~Node(){
}
