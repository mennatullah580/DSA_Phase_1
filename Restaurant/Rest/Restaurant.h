#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"

#include "..\CMUgraphicsLib\CMUgraphics.h"

#include "..\GUI\GUI.h"


#include "..\Events\Event.h"


#include "Order.h"

#include "Cook.h"

//data structures needed for the project:

#include "..\Generic_DS\Queue.h" // -> queue 
#include "../LinkedQueue.h" // -> linked queue 
#include "../LinkedStack.h" // -> linked stack 
#include "../StackADT.h" // -> stack 
#include "../QueueADT.h" // -> queue
#include "../CircularArrayQueue.h"
#include "../ArrayStack.h"
#include"..\Generic_DS\Node.h"
#include"../priorityQueue.h"


// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	LinkedQueue<Order*> normal_orders ; 
	LinkedQueue<Order*> vegan_orders;
	priQueue<Order*> vip_orders;

public:

	Restaurant(); //constructor

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep

	void RunSimulation(); //runs the simulation

	void FillDrawingList();

	void AddOrder(Order* &pOrd);

	int calc_vipweight(int size , int price , int arrival_time);

	~Restaurant();

};

#endif