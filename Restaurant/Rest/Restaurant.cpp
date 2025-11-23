
using namespace std;
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "../linkedStack.h"
#include "../linkedQueue.h"



int orderID;
int cookID;



Order* CreateRandomOrder(int id5, ORD_TYPE type)
{

	int r = rand() % 3;
	switch (r)
	{
	case 0:
		type = TYPE_NRM;
		break;
	case 1:
		type = TYPE_VGAN;
		break;
	case 2:
		type = TYPE_VIP;
		break;
	}
	return new Order(id5, type);
}





Restaurant::Restaurant() // constructor
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		break;
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant() // destructor
{
	if (pGUI)
		delete pGUI;
}


//This function should be implemented in phase1
//It should add ALL orders and Cooks to the drawing list
//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);



void Restaurant::AddOrder(Order* ord)
{


	switch (ord->GetType()) {
	case TYPE_NRM:

		break;
	case TYPE_VGAN:

		break;
	case TYPE_VIP:


	}


	void Restaurant::FillDrawingList()
	{
		pGUI->ResetDrawingList();

		pGUI->AddToDrawingList(CreateRandomOrder(orderID, TYPE_NRM));
		pGUI->AddToDrawingList(CreateRandomOrder(orderID, TYPE_VGAN));
		pGUI->AddToDrawingList(CreateRandomOrder(orderID, TYPE_VIP));

	}






