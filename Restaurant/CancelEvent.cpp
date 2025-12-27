#include "CancelEvent.h"
#include "Rest/Restaurant.h"

CancelEvent::CancelEvent(int ts, int id)
    : Event('X', ts, id)
{
}

void CancelEvent::Execute(Restaurant* pRest)
{
    //n cancel el normal orders bs
    if (pRest->CancelOrder(getOrderID())) 
    {
        cout << "order " << getOrderID() << " cancelled successfully :)" << endl;
    }
    else if (!pRest->CancelOrder(getOrderID())) 
    {
        cout << "order " << getOrderID() << " not found or cannot be cancelled xo" << endl;
    }
}
