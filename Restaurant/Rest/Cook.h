#pragma once

#include "..\Defs.h"
#include	<iostream>
using namespace std;
#pragma once
class Cook
{
	int ID; // cook ID
	
	ORD_TYPE type;	//for each order type there is a corresponding cook type (VIP, Normal, Vegan)
	
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	
	int breakduration; // time needed for this cook to take a break
public:
	Cook(); // constructor
	
	virtual ~Cook(); // destructor (virtual as class is inherited)
	
	int GetID() const; // id getter
	
	ORD_TYPE GetType() const; // type getter
	
	void setID(int); //ID setter
	
	void setType(ORD_TYPE) ; // type setter
	
	void setSpeed(int s); // speed setter
	
	int getSpeed() const;//speed getter
	
	void setBreaks(int br); // Breaks setter
	
	int getBreaks() const; //Breaks getter
};
