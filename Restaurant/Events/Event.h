#ifndef __EVENT_H_
#define __EVENT_H_

class Restaurant;   // forward declaration

// hena b2ol ll compliler en hygelk class esmo restaurant 2bl ma ygeko 3shan mygbsh error

// Base class for all events
class Event
{
protected:
    char Type;       // R=arrival event X=cancel events  P= promotion events

    int EventTime; //Timestep when this event takes place 

    int OrderID; //each event is related to certain order
public:


    Event(char type, int eTime, int ordID); // construcor

    char getType() const; // type getter

    int getEventTime() const; //get time step
   
    int getOrderID(); // ID getter

    virtual void Execute(Restaurant* pRest) = 0; // this function is a virtual pure function as it doesny know what it will be used for so it is decided by subclasses
    // it takes a pointer that points to restaurant so it can change its data


    virtual ~Event(); //  destructor
};

#endif
