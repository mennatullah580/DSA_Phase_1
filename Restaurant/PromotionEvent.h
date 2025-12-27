#ifndef __PROMOTION_EVENT_H_
#define __PROMOTION_EVENT_H_

#include "Events/Event.h"


class PromotionEvent : public Event 
{
private:
    int ExtraMoney;
public:
    PromotionEvent(int ts, int id, int extra);
    void Execute(Restaurant* pRest) override;
};

#endif


