#pragma once

#include "..\Defs.h"
#include	<iostream>
using namespace std;
enum ORD_TYPE 
{
	NRMc,
	VEGANc,
	VIPc,
};
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int breakduration;
public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;
	void setSpeed();
	int getSpeed() const;
	void setBreaks();
	int getBreaks() const;
};
