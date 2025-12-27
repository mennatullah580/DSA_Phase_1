#include "Event.h"

Event::Event(char type,int eTime, int ordID)  // constructor
{
    Type = type;
    EventTime = eTime; //ts
    OrderID = ordID;
}


char Event::getType() const // type getter
{
    return Type;
}

int Event::getEventTime() const // time step getter
{ 
    return EventTime; 
}

int Event::getOrderID()  // ID getter
{
    return OrderID; 
}

Event::~Event() // destructor
{
}


