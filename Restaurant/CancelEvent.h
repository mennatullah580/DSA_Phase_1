#ifndef __CANCEL_EVENT_H_
#define __CANCEL_EVENT_H_

#include "Events/Event.h"

class CancelEvent : public Event
{
public:
    CancelEvent(int ts, int id);

    virtual void Execute(Restaurant* pRest);   
};

#endif


