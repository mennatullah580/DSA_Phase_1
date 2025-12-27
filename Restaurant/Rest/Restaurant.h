#ifndef _RESTAURANT_H
#define _RESTAURANT_H
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
	
	LinkedQueue<Order*> normal_orders; //Queue of all normal orders
	
	LinkedQueue<Order*> vegan_orders;// Queue of all vegan orders
	
	priQueue<Order*> vip_orders; // Queue of all vip orders (requires priority so that is why it is linked)
	
	LinkedQueue<Cook*> Normal_cooks; // Queue of all normal cooks
	
	LinkedQueue<Cook*> Vegan_cooks; //Queue of all vegan cooks
	
	LinkedQueue<Cook*> VIP_cook; // Queue of all VIP cooks
	
	LinkedQueue<Order*> inservice_normal_orders; // preparing normal orders queue
	
	LinkedQueue<Order*> inservice_Vegan_orders; // preparing vegan orders queue
	
	LinkedQueue<Order*> inservice_VIP_orders; // preparing VIP orders queue
	
	LinkedQueue<Order*> finished_Orders; // Finished orders queue


public:

	Restaurant(); //constructor

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep

	void RunSimulation(); //runs the simulation

	void FillDrawingList(); // presents all queues and current events at current timestep on screen by GUI

	void LoadFile(const string& filename); // Loads data from text file to be read and registered

	void AddOrder(Order*& pOrd); // Adds orders to correct queue

	bool CancelOrder(int id); // removes wanted order from queue

	double calc_vipweight(int size, double price, int arrival_time); // sused to calculate priority of vip orders
	
	Cook* CreateCook(int speed, int breakTime, ORD_TYPE type, int id); // Creates Cook instances to help finish orders
	void AssignOrdersToCooks(int currentTimeStep);
	
	~Restaurant(); // destructor

};

#endif