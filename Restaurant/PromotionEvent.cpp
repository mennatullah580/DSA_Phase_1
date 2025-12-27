#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int ts, int id, int extra) : Event('P', ts, id)
{
    EventTime = ts;
    OrderID = id;
    ExtraMoney = extra;
}

void PromotionEvent::Execute(Restaurant* pRest)
{
   
}