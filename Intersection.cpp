#include "Intersection.hpp"
#include <iostream>

// TODO: Write your implementation for the Intersection class here

Intersection::Intersection()
{
	North = 0;
	South = 0;
	East = 0;
    West = 0;
}

bool Intersection::valid()
{
	/* checks if there are instances of "Lane" */
	if(North != 0 && South != 0 && East != 0 && West != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Lane* Intersection::connectNorth(Lane* lane, LaneDirection direction)
{
	//create a pointer that points to a previous instance of the North lane
	Lane* previousNorth = North;
	//The lane pointer now points to the new lane held by "connect"
    North = lane;
	//store the LaneDirection held by "connect" 
	//to indicate if this lane is incoming or outgoing
	north_direction = direction;
	if(previousNorth == 0)
	{
		return 0;
	}
	else
	{
		return previousNorth;
	}
}

Lane* Intersection::connectEast(Lane* lane, LaneDirection direction)
{
	//create a pointer that points to a previous instance of the East lane
	Lane* previousEast = East;
	//The lane pointer now points to the new lane held by "connect"
    East = lane;
	//store the LaneDirection held by "connect" 
	//to indicate if this lane is incoming or outgoing
    east_direction = direction;
	if(previousEast == 0)
	{
		return 0;
	}
	else
	{
		return previousEast;
	}
}

Lane* Intersection::connectSouth(Lane* lane, LaneDirection direction)
{
	//create a pointer that points to a previous instance of the South lane
	Lane* previousSouth = South;
	//The lane pointer now points to the new lane held by "connect"
    South = lane;
	//store the LaneDirection held by "connect" 
	//to indicate if this lane is incoming or outgoing
	south_direction = direction;
	if(previousSouth == 0)
	{
		return 0;
	}
	else
	{
		return previousSouth;
	}
}

Lane* Intersection::connectWest(Lane* lane, LaneDirection direction)
{
	//create a pointer that points to a previous instance of the South lane
	Lane* previousWest = West;
	//The lane pointer now points to the new lane held by "connect"
    West = lane;
	//store the LaneDirection held by "connect" 
	//to indicate if this lane is incoming or outgoing
	west_direction = direction;
	if(previousWest == 0)
	{
		return 0;
	}
	else
	{
		return previousWest;
	}
}

void Intersection::simulate()
{
	/*This function will be calling three other functions, to simulate the 4 situations mentioned.
	1) One Incoming Lane, Three Outgoing
	2) Two incoming, Two ougoing(opposite) AND Two incoming, Two outgoing(adjacent)
	3) Three incoming, One outgoing
	*/

	//outNumber indicates the number of outgoing lanes, 
	//via the special characteristic of enums being integers
	//As LaneDirection only consists of 2 cases, outNumber will be a sum of '0's and '1's
	int outNumber = north_direction + south_direction + east_direction + west_direction;

	//switches between the three situations mentioned above.
	switch (outNumber)
	{
		case 1:
			simulate_3();
			break;
		case 2:
			simulate_2();
			break;
		case 3:
			simulate_1();
		default:
			break;
	}
}

void Intersection::simulate_1()
{
	/*The logic behind each case is to see which Lane is an incoming,
	and whether that incoming lane has vehicles in it*/

	if(north_direction == 0 && North->count() > 0)
	{
		northTurn();
	}
	else if(south_direction == 0 && South->count() > 0)
	{
		southTurn();
	}
	else if(east_direction == 0 && East->count() > 0)
	{
		eastTurn();
	}
	else if(west_direction == 0 && West->count() > 0)
	{
		westTurn();
	}
}

void Intersection::simulate_2()
{
	/*A much more complex simulation, the first level of checking is whether 
	the two incoming lanes are opposite or adjacent to each other.

	The next level of check ensures that there are vehicles in the lane,
	or if one of the lanes are empty.

	Finally, the give way rules are applied accordingly depending on whether
	the lanes are adjacent or opposite, followed by a call to turn the vehicle.
	Note that it is assumed that an incoming lane won't drive into another incoming lane */

	if(north_direction == 0 && south_direction == 0)
	{	
		if(North->count() > 0 && South->count() > 0)
		{
			if(North->front()->nextTurn() == 0 && South->front()->nextTurn() == 2)
			{
				northTurn();
			}
			else if(North->front()->nextTurn() == 2 && South->front()->nextTurn() == 0)
			{
				southTurn();	
			}
			else if(North->front()->nextTurn() == South->front()->nextTurn())
			{
				northTurn();
				southTurn();	
			}
		}
		else if(North->count() > 0 && South->count() == 0)
		{	
			northTurn();	
		}
		else if(North->count() == 0 && South->count() > 0)
		{
			southTurn();
		}
	}
	else if(west_direction == 0 && east_direction == 0)
	{	
		if(West->count() > 0 && East->count() > 0)
		{
			if(West->front()->nextTurn() == 0 && East->front()->nextTurn() == 2)
			{
				westTurn();
			}
			else if(West->front()->nextTurn() == 2 && East->front()->nextTurn() == 0 )
			{
				eastTurn();	
			}  
			else if(West->front()->nextTurn() == East->front()->nextTurn())
			{
				westTurn();
				eastTurn();	
			}
		}
		else if(West->count() > 0 && East->count() == 0)
		{	
			westTurn();	
		}
		else if(West->count() == 0 && East->count() > 0)
		{
			eastTurn();
		}
	}
	else if(north_direction == 0 && west_direction == 0)
	{	
		if(North->count() > 0 && West->count() > 0)
		{
			if(North->front()->nextTurn() == 0 && West->front()->nextTurn() == 2)
			{
				northTurn();
			}
			else if(North->front()->nextTurn() == 1 && West->front()->nextTurn() == 2)
			{
				northTurn();	
			}
			else if(North->front()->nextTurn() == 0 && East->front()->nextTurn() == 1)
			{
				westTurn();	
			}
			else if(North->front()->nextTurn() == West->front()->nextTurn())
			{
				northTurn();
				westTurn();	
			}
		}
		else if(North->count() > 0 && West->count() == 0)
		{	
			northTurn();	
		}
		else if(North->count() == 0 && West->count() > 0)
		{
			westTurn();
		}
	}
	else if(west_direction == 0 && south_direction == 0)
	{	
		if(West->count() > 0 && South->count() > 0)
		{
			if(West->front()->nextTurn() == 0 && South->front()->nextTurn() == 2)
			{
				westTurn();
			}
			else if(West->front()->nextTurn() == 1 && South->front()->nextTurn() == 2)
			{
				westTurn();	
			}
			else if(West->front()->nextTurn() == 0 && South->front()->nextTurn() == 1)
			{
				southTurn();	
			}
			else if(North->front()->nextTurn() == West->front()->nextTurn())
			{
				westTurn();
				southTurn();	
			}
		}
		else if(West->count() > 0 && South->count() == 0)
		{	
			westTurn();	
		}
		else if(West->count() == 0 && South->count() > 0)
		{
			southTurn();
		}
	}
	else if(south_direction == 0 && east_direction == 0)
	{	
		if(South->count() > 0 && East->count() > 0)
		{
			if(South->front()->nextTurn() == 0 && East->front()->nextTurn() == 2)
			{
				southTurn();
			}
			else if(South->front()->nextTurn() == 1 && East->front()->nextTurn() == 2)
			{
				southTurn();	
			}
			else if(South->front()->nextTurn() == 0 && East->front()->nextTurn() == 1)
			{
				eastTurn();	
			}
			else if(South->front()->nextTurn() == East->front()->nextTurn())
			{
				southTurn();
				eastTurn();	
			}
		}
		else if(South->count() > 0 && East->count() == 0)
		{	
			southTurn();	
		}
		else if(South->count() == 0 && East->count() > 0)
		{
			eastTurn();
		}
	}
	else if(east_direction == 0 && north_direction == 0)
	{	
		
		if(East->count() > 0 && North->count() > 0)
		{
			if(East->front()->nextTurn() == 0 && North->front()->nextTurn() == 2)
			{
				eastTurn();
			}
			else if(East->front()->nextTurn() == 1 && North->front()->nextTurn() == 2)
			{
				eastTurn();	
			}
			else if(East->front()->nextTurn() == 0 && North->front()->nextTurn() == 1)
			{
				northTurn();	
			}
			else if(East->front()->nextTurn() == North->front()->nextTurn())
			{
				eastTurn();
				northTurn();	
			}
		}
		else if(East->count() > 0 && North->count() == 0)
		{	
			eastTurn();	
		}
		else if(East->count() == 0 && North->count() > 0)
		{
			northTurn();
		}
	}
	
}

void Intersection::simulate_3()
{
	/*The first level of check identifies which lane is the outgoing lane,
	after which the orientation of the other lanes determine which lane goes first.
	e.g.
	if the north lane is the outgoing lane, as the other lanes can only go to one
	outgoing lane:
	1)South goes first as it goes straight
	2)When there aren't anymore vehicles in the South lane, vehicles in the 
	west lane go next as they are turning left.
	3)Finally when there aren't any vehicles in the South or West lanes, 
	vehicles in the east can finally proceed.*/

	if(north_direction == 1)
	{
		if(South->count() > 0)
		{
			southTurn();
		}
		else if(South->count() == 0 && West->count() > 0)
		{
			westTurn();
		}
		else if(South->count() == 0 && West->count() == 0 && East->count() > 0)
		{
			eastTurn();
		}
	}
	else if(east_direction == 1)
	{
		if(West->count() > 0)
		{
			westTurn();
		}
		else if(West->count() == 0 && North->count() > 0)
		{
			northTurn();
		}
		else if(West->count() == 0 && North->count() == 0 && South->count() > 0)
		{
			southTurn();
		}
	}
	else if(south_direction == 1)
	{
		if(North->count() > 0)
		{
			northTurn();
		}
		else if(North->count() == 0 && East->count() > 0)
		{
			eastTurn();
		}
		else if(North->count() == 0 && East->count() == 0 && West->count() > 0)
		{
			westTurn();
		}
	}
	else if(west_direction == 1)
	{
		if(East->count() > 0)
		{
			eastTurn();
		}
		else if(East->count() == 0 && South->count() > 0)
		{
			southTurn();
		}
		else if(East->count() == 0 && South->count() == 0 && North->count() > 0)
		{
			northTurn();
		}
	}	
}
	
void Intersection::northTurn()
{
	Vehicle* pointing = North->dequeue();
	int turn_type = pointing->makeTurn();
	switch(turn_type)
	{
		case 0:
			East->enqueue(pointing);
			break;
		case 1:
			South->enqueue(pointing);
			break;
		case 2:
			West->enqueue(pointing);
			break;
		default:
			break;
	}
}

void Intersection::southTurn()
{
	Vehicle* pointing = South->dequeue();
	int turn_type = pointing->makeTurn();
	switch(turn_type)
	{
		case 0:
			West->enqueue(pointing);
			break;
		case 1:
			North->enqueue(pointing);
			break;
		case 2:
			East->enqueue(pointing);
			break;
		default:
			break;
	}
}

void Intersection::eastTurn()
{
	Vehicle* pointing = East->dequeue();
	int turn_type = pointing->makeTurn();
	switch(turn_type)
	{
		case 0:
			South->enqueue(pointing);
			break;
		case 1:
			West->enqueue(pointing);
			break;
		case 2:
			North->enqueue(pointing);
			break;
		default:
			break;
	}
}

void Intersection::westTurn()
{
	Vehicle* pointing = West->dequeue();
	int turn_type = pointing->makeTurn();
	switch(turn_type)
	{
		case 0:
			North->enqueue(pointing);
			break;
		case 1:
			East->enqueue(pointing);
			break;
		case 2:
			South->enqueue(pointing);
			break;
		default:
			break;
	}
}
