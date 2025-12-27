#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"
#include "..\Rest\Order.h"

class ArrivalEvent : public Event
{
private:
    char OrderType;   //(N G V)
    int Size;
    double OrdMoney;
    int OrdDistance;

public:
    ArrivalEvent(int ts, char oType, int id, int size, double money, int dist);

    
    char getOrderType() const;
    int getSize() const;
    double getMoney() const;
    int getDistance() const;

    virtual void Execute(Restaurant* pRest); // overides pure virtaul function to be omplemented in this case adding orders
};

#endif
