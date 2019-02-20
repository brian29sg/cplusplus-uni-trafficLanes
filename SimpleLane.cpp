#include "SimpleLane.hpp"

// TODO: Write your implementation for the SimpleLane class here

SimpleLane::SimpleLane()
{
	counting = 0;
	first = 0;
	last = 0;
}

SimpleLane::~SimpleLane()
{
	/*create the dequeue function, and loop it until there aren't any more vehicles in the lane.
	Memory is claimed in the dequeue function as well*/
	while(count()!= 0)
	{
		dequeue(); 
	}
}

void SimpleLane::enqueue(Vehicle* vehicle)
{ 
	 Node *nodeToAdd = new Node(vehicle);
	 //if the lane is initially empty, first and last pointers point to the new instance of "node"
	 if(empty() == true)
	 {
		first = nodeToAdd;
		last = nodeToAdd;
	 }
	 //add the next few instances of node to the back 
	 else
	 {
		nodeToAdd->setNext(last);
		last = nodeToAdd;
	 }
	 //increment the counter for the number of nodes 
	 counting++;	
}

Vehicle* SimpleLane::dequeue()
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

bool SimpleLane::empty() const
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

unsigned int SimpleLane::count() const
{
	return counting;
}

const Vehicle* SimpleLane::front() const
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

const Vehicle* SimpleLane::back() const
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
