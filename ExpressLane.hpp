#ifndef EXPRESSLANE_HPP
#define EXPRESSLANE_HPP

#include "SimpleLane.hpp"
#include "Vehicle.hpp"

/*
The ExpressLane class simulates a single lane of a road. It is a FIFO queue for Vehicle objects.

ExpressLane implements the same behavior as SimpleLane, except when a Vehicle of type VT_MOTORCYCLE is enqueued, that
Vehicle is inserted ahead of all Vehicles of type VT_CAR and VT_BUS, but behind other motorcycles that have already been
enqueued.
*/
class ExpressLane : public SimpleLane {
    // TODO: Complete this class
protected:
	//pointer that iterates through each instance of "Node"
    Node* iterator;
	//pointer that points at the first instance of "Node" that was created, impying the front vehicle in a lane
    Node *first;
	//pointer that points at the last instance of "Node" that was created, impying the back vehicle in a lane
    Node *last;
	//an arbitrary counter that indicates how many "Node" instances there, implying the number of vehicles in a lane. 
    unsigned int counting;
public:
    /*
    Create a new empty traffic lane. Remember to initialize member variables where necessary.
    */
    ExpressLane();

    /*
    Destroy the lane; the destructor should delete *all* vehicles currently enqueued in the lane.
    */
    virtual ~ExpressLane();

    /*
    Add a Vehicle to the back of the lane.
    */
    virtual void enqueue(Vehicle* vehicle);

    /*
    Remove a vehicle from the front of the lane, returning a pointer to the removed vehicle. If there is no vehicle to
    remove, this method should return 0 instead.
    */
    virtual Vehicle* dequeue();

    /*
    Return whether or not the lane is empty; the returned value is `true` if there are no vehicles in the lane, or
    `false` if there is at least one vehicle in the lane.
    */
    virtual bool empty() const;

    /*
    Get the exact number of vehicles currently in the lane; e.g. should return 0 if there are no vehicles in the lane,
    or 4 if there are four vehicles in the lane.
    */
    virtual unsigned int count() const;

    /*
    Return a pointer to the vehicle at the front of the lane without removing it from the lane. If there are no vehicles
    in the lane this method should return 0.
    */
    virtual const Vehicle* front() const;

    /*
    Return a pointer to the vehicle at the back of the lane without removing it from the lane. If there are no vehicles
    in the lane this method should return 0.
    */
    virtual const Vehicle* back() const;
};

#endif /* end of include guard: EXPRESSLANE_HPP */
