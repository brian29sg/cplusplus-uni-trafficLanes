#include "ExpressLane.hpp"

// TODO: Write your implementation for the ExpressLane class here

ExpressLane::ExpressLane()
{
	counting = 0;
	first = 0;
	last = 0;
}

ExpressLane::~ExpressLane()
{
	/*create the dequeue function, and loop it until there aren't any more vehicles in the lane.
	Memory is claimed in the dequeue function as well*/
	while(count()!= 0)
	{
		dequeue(); 
	}
}

void ExpressLane::enqueue(Vehicle* vehicle)
{
	 //create a new instance of Node, which stores the vehicle pointer variable stored by enqueue
	 Node *nodeToAdd = new Node(vehicle);

	 //if the lane is initially empty, the first and last pointers point to the new instance of Node
	 if(empty() == true)
	 {
		first = nodeToAdd;
		last = nodeToAdd;
	 }
	 else
	 {
		//if a motorbike is being added, and there are no motorbikes in front
		if(nodeToAdd->getPointer()->type() == Vehicle::VT_MOTORCYCLE && front()->type() != Vehicle::VT_MOTORCYCLE)
		{
			first->setNext(nodeToAdd);
			first = nodeToAdd;
		}
		//if a motorbike is being added, but there is a motorbike in front
		else if(nodeToAdd->getPointer()->type() == Vehicle::VT_MOTORCYCLE && front()->type() == Vehicle::VT_MOTORCYCLE)
		{
			//checks if there are more than one vehicle in the lane
			if(counting != 1)
			{
				iterator = last;
				//while the next vehicle isn't a motorcycle, iterate through all the vehicles in the lane
				while(iterator->getNext()->getPointer()->type() != Vehicle::VT_MOTORCYCLE)
				{
					iterator = iterator->getNext();
				}
				//node to add now points to the first instance of node(a motorbike)
				nodeToAdd->setNext(iterator->getNext());
				//the vehicle instance pointed to by the iterator now points to node to add, preventing the chain of pointers from being broken
				iterator->setNext(nodeToAdd);
			}
			//specifically handles the case when only one vehicle is in the lane(ie, a Motorbike)
			else if(counting == 1)
			{
				nodeToAdd->setNext(last);
				last = nodeToAdd;
			}
		}
		//queues any other vehicle to the back
		else
		{		
			nodeToAdd->setNext(last);
			last = nodeToAdd;
		}
	 }
	 //each time the enqueue function is called, this increases by one, indicating that a vehicle has been added to the lane
	 counting++;	
}

Vehicle* ExpressLane::dequeue()
{
	Node* nodeToDelete = 0;
    //if the lane is already empty, initialize the nodeToDelete pointer and return a zero as stated
	if(empty() == true)
	{
		nodeToDelete = 0;
		return 0;
	}
	else
	{
		//if there are vehicles in the lane.
		if(counting > 1)
		{
			nodeToDelete = first;
			iterator = last;
			while(iterator->getNext() != first)
			{
				iterator = iterator->getNext();
			}
			iterator->setNext(0);
			first = iterator;
		}
		//when there is only one vehicle in the lane(as the previous case doesn't handle this situation well)
		else if(counting == 1)
		{
			nodeToDelete = first;
			iterator = 0;
			first = iterator;
		}
		//reduce the counter for the number of vehicles, reclaim memory, then return the vehicle instance that was deleted. 
		counting --;
		delete nodeToDelete;
		return nodeToDelete->getPointer();
	}	
}

bool ExpressLane::empty() const
{
	if(count() == 0)
	{
		return true;
	}
	else
	{	
		return false;
	}
}

unsigned int ExpressLane::count() const
{
	return counting;
}

const Vehicle* ExpressLane::front() const
{
	if(empty() == true)
	{
		return 0;
	}
	else
	{
		return first->getPointer();
	}
}

const Vehicle* ExpressLane::back() const
{
	if(empty() == true)
	{
		return 0;
	}
	else
	{
		return last->getPointer();
	}
}
