#include "Cook.h"


Cook::Cook()
{
	speed = 0;
	breakduration = 0;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}

	
ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}
void Cook::setSpeed(int s)
{
	speed = s;
}
int Cook::getSpeed() const
{
	return speed;
}
void Cook::setBreaks(int br)
{
	breakduration = br;
}
int Cook::getBreaks() const
{
	return breakduration;
}


