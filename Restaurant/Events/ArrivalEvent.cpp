#include "ArrivalEvent.h"
#include "..\\Rest\\Restaurant.h"
#include "..\\Defs.h"
#include "..\\Rest\\Order.h"

ArrivalEvent::ArrivalEvent(int ts, char oType, int id, int size, double money, int dist) // constructor
    : Event('R', ts, id) // calls constructor of base class as it is inherited
{
    OrderType = oType;
    Size = size;
    OrdMoney = money;
    OrdDistance = dist;
}

char ArrivalEvent::getOrderType() const 
{
    return OrderType;
}
int  ArrivalEvent::getSize() const 
{ 
    return Size; 
}
double ArrivalEvent::getMoney() const 
{ 
    return OrdMoney; 
}
int ArrivalEvent::getDistance() const
{
    return OrdDistance;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
    //This function should create an order and fills its data 
    // Then adds it to normal, vegan, or VIP order lists that you will create in phase1
    
    	
    ///For the sake of demo, this function will just create an order and add it to DemoQueue
    ///Remove the next code lines in phases 1&2
    /*Order* pOrd = new Order(OrderID,OrdType);
    pRest->AddtoDemoQueue(pOrd);*/

    // n create order bs 
    
    Order* newOrder = new Order(getOrderID(), getOrderType(), getDistance(), getMoney(), getSize(), EventTime ); // event time is time order arrivd
    newOrder->setArrTime(EventTime);
    pRest->AddOrder(newOrder); // arrivalevent creates an order and handes it to restaurant to correctly allocate it to the normal queue
}
