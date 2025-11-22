#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "../linkedStack.h"
#include "../ArrayStack.h"
#include "../linkedQueue.h"
#include "../QueueADT.h"
#include "../StackADT.h"
#include "../CircularArrayQueue.h"


#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	/*priQueue<Order*> VIP_waiting;*/
	Queue<Order*> Vegan_waiting;
	Queue<Order*> Normal_waiting;
	Queue<Order*> In_Service;
	ArrayStack<Order*> Serviced;
	Queue<Cook*> VIP_cook;
	Queue<Cook*> Vegan_cook;
	Queue<Cook*> Normal_cook;
	/*priQueue<Cook*> In_break;*/
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	/*Queue<Order*> DEMO_Queue;*/	//Important: This is just for demo
	/// ==>
	
	
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	


	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 



};

#endif