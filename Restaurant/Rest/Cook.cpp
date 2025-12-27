#include "Cook.h"


Cook::Cook() // constructor
{
	speed = 0;
	breakduration = 0;
}


Cook::~Cook() // destructor
{
}


int Cook::GetID() const // cook id getter
{
	return ID;
}

	
ORD_TYPE Cook::GetType() const // cook type getter
{
	return type;
}


void Cook::setID(int id) // cook id setter
{
	ID = id;
}

void Cook::setType(ORD_TYPE t) // cook type setter
{
	type = t;
}
void Cook::setSpeed(int s) // cook speed setter
{
	speed = s;
}
int Cook::getSpeed() const // cook speed setter
{
	return speed;
}
void Cook::setBreaks(int br) // cook breaks setter
{
	breakduration = br;
}
int Cook::getBreaks() const // cook breaks getter
{
	return breakduration;
}


