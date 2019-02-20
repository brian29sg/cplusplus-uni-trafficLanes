#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "Lane.hpp"
#include "Vehicle.hpp"

// forward declaration
class Lane;

/*
The Intersection class aggregates a set of lanes together to simulate traffic flow through an intersection. Traffic may
enter the intersection through incoming lanes, and exit through outgoing lanes. Lanes may be connected to the 
Intersection as either incoming lanes or outgoing lanes in one of four directions; north, south, east and west. 

If a lane is connected as an incoming lane, traffic may be dequeued from that lane each time the Intersection's
`simulate` method is called. If a lane is connected as an outgoing lane, traffic may be enqueued into that lane each
time the Intersection's `simulate` method is called. What lanes vehicles flow from and to each time `simulate` is called
will be determined by the Vehicle's `nextTurn` method and the give way rules that apply to the intersection.
*/
class Intersection {
private:
	//Lane pointers labeled as North, South, East and West
    Lane* North;
    Lane* South;
    Lane* East;
    Lane* West;

	/*These variables hold the LaneDirection passed by the "connect" function, 
	to indicate which lanes are incoming or outgoing*/
    int north_direction;
    int south_direction;
    int east_direction;
    int west_direction;
public:
    /*
    The LaneDirection enum is used to indicate which end of a Lane is connected to this intersection. If LD_INCOMING is
    specified, then this Intersection will only dequeue traffic from the Lane. If LD_OUTGOING is specified, then this
    Intersection will only enqueue traffic into the Lane.
    */
    enum LaneDirection { LD_INCOMING, LD_OUTGOING };

    /*
    Intersection constructor. Initializes a new Intersection with no Lanes attached.
    */
    Intersection();

    /*
    This method is used to determine if the Intersection has been fully and properly initialized and can be used for
    simulation.

    For an Intersection to be valid it must have a Lane attached for each direction of the Intersection (north, east,
    south, west). If the Intersection is valid this method will return `true`, otherwise it will return `false`.
    */
    bool valid();

    /*
    This method can be used to add a Lane to the northern side of the Intersection. The `direction` parameter specifies
    whether traffic flows into the Intersection (LD_INCOMING) or out of the Intersection (LD_OUTGOING) via the Lane.

    If a Lane has already previously been assigned using this method, subsequent calls to this method will replace the
    existing Lane with the new one. It is valid to pass a null pointer (0) as the Lane parameter, effectively
    unassigning the existing Lane and assigning 0 in its place. The previously assigned Lane* should be returned by this
    method, or 0 should be returned if no Lane was previously assigned.
    
    The Intersection is *not* responsible for cleaning up attached Lanes when it is destroyed.
    */
    Lane* connectNorth(Lane* lane, LaneDirection direction);

    /*
    This method can be used to add a Lane to the eastern side of the Intersection. The behavior of this method is
    identical to `connectNorth`, but for the eastern Lane of the Intersection.
    */
    Lane* connectEast(Lane* lane, LaneDirection direction);

    /*
    This method can be used to add a Lane to the southern side of the Intersection. The behavior of this method is
    identical to `connectNorth`, but for the southern Lane of the Intersection.
    */
    Lane* connectSouth(Lane* lane, LaneDirection direction);

    /*
    This method can be used to add a Lane to the western side of the Intersection. The behavior of this method is
    identical to `connectNorth`, but for the western Lane of the Intersection.
    */
    Lane* connectWest(Lane* lane, LaneDirection direction);

    /*
    Execute a single simulation iteration, allowing up to one car from each incoming Lane to pass through the 
    Intersection. The give way rules for the intersection are as follows:
     - Right-turning Vehicles must give way to other Vehicles turning left or traveling straight through the
       Intersection.
     - Left-turning Vehicles must give way to other Vehicles traveling straight through the Intersection.
     - Any remaining vehicles waiting at the intersection that don't have to give way may proceed through the
       intersection.

    This method should do nothing if this Intersection is not valid (i.e. the valid() method returns `false`).
    */
    void simulate();

	/*These additional functions separate each cases of:
	1) One Incoming Lane, Three Outgoing
	2) Two incoming, Two ougoing(opposite) AND Two incoming, Two outgoing(adjacent)
	3) Three incoming, One outgoing
	respectively.*/
    void simulate_1();
    void simulate_2();
    void simulate_3();

	/*these functions serve to handle the direction of turn for each vehicle in each lane,
	which will be called in the "simulate" functions*/
    void northTurn();
    void southTurn();
    void eastTurn();
    void westTurn();
};

#endif /* end of include guard: INTERSECTION_HPP */
