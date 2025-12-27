using namespace std;
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <iostream>

#include <sstream>
using namespace std;
#include"Cook.h"
#include"Order.h"
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "../CancelEvent.h"
#include "../linkedStack.h"
#include "../linkedQueue.h"
#include "../QueueADT.h"

//LOJIIII

Restaurant::Restaurant() {} // constructor

Restaurant::~Restaurant() // destructor
{
	if (pGUI)
		delete pGUI;
}


double Restaurant::calc_vipweight(int size, double price, int arrival_time) // function bt calculate el priority bta3 el vip order based on size , price , arrival time
{

	double weight = (size + price) / arrival_time; // the bigger and the more expensive the order , the higher the priority and the earlier the arrival time the bigger the weight.

	return weight;

}

void Restaurant::AddOrder(Order*& ord) //Hena bya5od el order object as a paramater we be assain every order to a specific queue list
{

	char type=ord->GetType();

	switch (type) {
	case 'N':
		normal_orders.enqueue(ord); // lw normal enqueue fi el normal queue
		break;
	case 'G':
		vegan_orders.enqueue(ord); // lw vegan enqueue fi el vegan queue
		break;
	case 'V': 

		double priority = calc_vipweight(ord->getOrderSize(), ord->getMoney(), ord->getArrTime()); //lw vip calculate el priority first as priority queue takes 2 parameters the item itself tgen its priority

		vip_orders.enqueue(ord, priority);
	}

}

//////////////////////////////////  Event handling functions   /////////////////////////////


void Restaurant::ExecuteEvents(int CurrentTimeStep) // executes all events where time == currentstep
{
	Event* pE; // pointer by temporarily store el current events

	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	// lw el event schedulued for the future dont execute it 3shan yeb2a fe order
			return;

		pE->Execute(this); // execute order

		EventsQueue.dequeue(pE);	//remove event from the queue after execution

		delete pE;		//deallocate event object from memory to free memory
	}

}




bool Restaurant::CancelOrder(int id) // el function de benedeha id bta3 order 3shan nshelo mn el waiting list
{
	Queue<Order*> tempQueue; // hena el queue de bt store el orders temporarily l7d ma nela2y el order ely 3ayzeen nshelo
	bool found = false; // inidicates if the order is found 
	Order* pOrd; // temporarily holds each order to check
	while (normal_orders.dequeue(pOrd)) // as long as normal_orders is able to dequeue loop 
	{
		if (pOrd->GetID() == id)   // check if the current id of the pointer matches the wqanted id we want to remove
		{
			if (pOrd->getStatus() == WAIT) // check if it is waiting 
			{
				delete pOrd;   //remove order by deallocating memory
				found = true;  // sets found to true 
			}
			else
			{
				tempQueue.enqueue(pOrd); // order mynfa3sh yeb2a deleted 3shan fe el waiting 
 			}
		}
		else
		{
			tempQueue.enqueue(pOrd); // order mynfa3sh yeb2a deleted 3shan fe el id is not matching 
		}
	}

	while (tempQueue.dequeue(pOrd))
	{
		normal_orders.enqueue(pOrd); // hena barg3 el original queue zy ma howa
	}

	return found; // 3shan  ashof deleted wla la2
}



void Restaurant::FillDrawingList() // this functions draws every action happening in the program at every time step in the Gui
{

	pGUI->ResetDrawingList(); // byfdy el drawing list array at each timestep 

	// waiting normal order 
	{
		Order* ptr = nullptr; // pointer byshawer 3la el current order fe el normal order queue list
		LinkedQueue<Order*> temp;   // creates temporary queue to hold removed orders from normal orders

		while (normal_orders.dequeue(ptr)) // as long as normal orders has orders
		{
			pGUI->AddToDrawingList(ptr); // hyrsm el current order ely el ptr byshawer 3leh (GUI reads its colour , id , region etccc)
			temp.enqueue(ptr); // store ptr in temp to avoid it being lost
		}
		while (temp.dequeue(ptr))
			normal_orders.enqueue(ptr); // bnrga3 el original list zy ma heya b3d ma 3dena 3la kol order we rsmnah
	}

	// waiting vegan order
	{
		Order* ptr = nullptr;
		LinkedQueue<Order*> temp;

		while (vegan_orders.dequeue(ptr))
		{
			pGUI->AddToDrawingList(ptr);
			temp.enqueue(ptr);
		}
		while (temp.dequeue(ptr))
			vegan_orders.enqueue(ptr); // same as before
	}

	// waiting VIP order
	{
		Order* ptr = nullptr;
		priQueue<Order*> temp;   
		int pr = 0; // as vip is a priorityt queue it must take a priority as a parameter

		
		while (vip_orders.dequeue(ptr, pr))
		{
			pGUI->AddToDrawingList(ptr);
			temp.enqueue(ptr, pr);
		}
		while (temp.dequeue(ptr, pr))
			vip_orders.enqueue(ptr, pr); 
	}

	// all available cooks 
	{
		Cook* c = nullptr;
		LinkedQueue<Cook*> temp;

		while (Normal_cooks.dequeue(c))
		{
			pGUI->AddToDrawingList(c);
			temp.enqueue(c);
		}
		while (temp.dequeue(c))
			Normal_cooks.enqueue(c);  // same as before
	}

	{
		Cook* c = nullptr;
		LinkedQueue<Cook*> temp;

		while (Vegan_cooks.dequeue(c))
		{
			pGUI->AddToDrawingList(c);
			temp.enqueue(c);
		}
		while (temp.dequeue(c))
			Vegan_cooks.enqueue(c); //same
	}

	{
		Cook* c = nullptr;
		LinkedQueue<Cook*> temp;

		while (VIP_cook.dequeue(c))
		{
			pGUI->AddToDrawingList(c);
			temp.enqueue(c);
		}
		while (temp.dequeue(c))
			VIP_cook.enqueue(c);//same
	}

	// in service order
	{
		Order* ptr = nullptr;
		LinkedQueue<Order*> temp;

		while (inservice_normal_orders.dequeue(ptr))
		{
			pGUI->AddToDrawingList(ptr);
			temp.enqueue(ptr);
		}
		while (temp.dequeue(ptr))
			inservice_normal_orders.enqueue(ptr); //same
	}

	{
		Order* ptr = nullptr;
		LinkedQueue<Order*> temp;

		while (inservice_Vegan_orders.dequeue(ptr))
		{
			pGUI->AddToDrawingList(ptr);
			temp.enqueue(ptr);
		}
		while (temp.dequeue(ptr))
			inservice_Vegan_orders.enqueue(ptr); //same
	}

	{
		Order* ptr = nullptr;
		LinkedQueue<Order*> temp;

		while (inservice_VIP_orders.dequeue(ptr))
		{
			pGUI->AddToDrawingList(ptr);
			temp.enqueue(ptr);
		}
		while (temp.dequeue(ptr))
			inservice_VIP_orders.enqueue(ptr); //same
	}

	// finished order
	{
		Order* ptr = nullptr;
		LinkedQueue<Order*> temp;

		while (finished_Orders.dequeue(ptr))
		{
			pGUI->AddToDrawingList(ptr);
			temp.enqueue(ptr);
		}
		while (temp.dequeue(ptr))
			finished_Orders.enqueue(ptr);
	}

	
	pGUI->UpdateInterface(); // redraws everything in the drawing list  and after drawing everthing it  refreshes the page 

}

Cook* Restaurant::CreateCook(int speed, int breakTime, ORD_TYPE type, int id)
{
	Cook* c = new Cook(); // creates a new pointer that point to the new dynamically cook object
	c->setSpeed(speed);
	c->setBreaks(breakTime);
	c->setType(type);
	c->setID(id);
	return c; // sets all cook atributes and returns a complete cook object
}

void Restaurant::LoadFile(const string& filename)
{
	ifstream infile(filename); // hene bn open el text file w lw msh mwgood print error
	if (!infile.is_open())
	{
		cout << "error! cannot open file!" << endl;
	}
	int N, G, V; //no. cooks 
	int SN, SG, SV; //speed cooks
	int BO, BN, BG, BV; //no. orders before break and break duration
	int AutoP; //auto promo
	int M; //descibe events
	 // all these are declarations for variables we are going to need
	string line;

	getline(infile, line);
	stringstream l1(line);
	l1 >> N >> G >> V;
	getline(infile, line);
	stringstream l2(line);
	l2 >> SN >> SG >> SV;
	getline(infile, line);
	stringstream l3(line);
	l3 >> BO >> BN >> BG >> BV;
	getline(infile, line);
	stringstream l4(line);
	l4 >> AutoP;
	getline(infile, line);
	stringstream l5(line);
	l5 >> M;
	getline(infile, line);
	stringstream l6(line);

	for (int i = 0; i < N; i++)
	{
		Normal_cooks.enqueue(CreateCook(SN, BN, TYPE_NRM, i + 1));
	}

	for (int i = 0; i < G; i++)
	{
		Vegan_cooks.enqueue(CreateCook(SG, BG, TYPE_VGAN, i + 1));
	}

	for (int i = 0; i < V; i++)
	{
		VIP_cook.enqueue(CreateCook(SV, BV, TYPE_VIP, i + 1));
	}

	
	getline(infile, line);

	for (int i = 0; i < M; i++)
	{
		getline(infile, line);
		stringstream ss(line);
		char eventType;
		ss >> eventType;

		if (eventType == 'R') //arrival
		{ 
			char type;
			int TS, ID, size, dist;
			double price;
			ss >> type >> TS >> ID >> size >> price >> dist;
			Event* e = new ArrivalEvent(TS,type,ID,size,price,dist);
			EventsQueue.enqueue(e);
		}
		else if (eventType == 'X') //cancel
		{ 
			int TS, ID;
			ss >> TS >> ID;
			Event* e = new CancelEvent(TS, ID);
			EventsQueue.enqueue(e);
		}
		else if (eventType == 'P') // promotion
		{
			continue;
		}
		else
		{
			return;
		}
	}

	infile.close();
}



template<typename Q, typename T>

int GetQueueCount(Q& q)
{
	T ptr = nullptr;
	Q temp;
	int cnt = 0;

	while (q.dequeue(ptr))
	{
		cnt++;
		temp.enqueue(ptr);
	}
	while (temp.dequeue(ptr))
		q.enqueue(ptr);

	return cnt;
}
void Restaurant::AssignOrdersToCooks(int currentTimeStep)
{
	// vip->normal->vegan

	while (!vip_orders.isEmpty())
	{
		Order* vipOrder = nullptr;
		int priority = 0;

		// ba3ml highest priority ll VIP order
		if (!vip_orders.peek(vipOrder, priority))
			break;

		Cook* assignedCook = nullptr;

		// ba3ml VIP cook elawl
		if (VIP_cook.dequeue(assignedCook))
		{
			// VIP cook is available
			vip_orders.dequeue(vipOrder, priority); // bashel order mn elwaiting
			vipOrder->setStatus(SRV);
			vipOrder->setArrTime(currentTimeStep); //  service start time
			inservice_VIP_orders.enqueue(vipOrder);

			// Return cook to queue			
			VIP_cook.enqueue(assignedCook);
			continue;
		}

		// Try Normal cook if VIP cook not available
		if (Normal_cooks.dequeue(assignedCook))
		{
			vip_orders.dequeue(vipOrder, priority);
			vipOrder->setStatus(SRV);
			vipOrder->setArrTime(currentTimeStep);
			inservice_VIP_orders.enqueue(vipOrder);

			Normal_cooks.enqueue(assignedCook);
			continue;
		}

		// Try Vegan cook as last resort
		if (Vegan_cooks.dequeue(assignedCook))
		{
			vip_orders.dequeue(vipOrder, priority);
			vipOrder->setStatus(SRV);
			vipOrder->setArrTime(currentTimeStep);
			inservice_VIP_orders.enqueue(vipOrder);

			Vegan_cooks.enqueue(assignedCook);
			continue;
		}

		// No cook available, order must wait
		break;
	}

	//vegan baas

	while (!vegan_orders.isEmpty())
	{
		Order* veganOrder = nullptr;

		// Check if vegan order exists
		if (!vegan_orders.peek(veganOrder))
			break;

		Cook* assignedCook = nullptr;

		// Try to get Vegan cook
		if (Vegan_cooks.dequeue(assignedCook))
		{
			vegan_orders.dequeue(veganOrder); // Remove from waiting
			veganOrder->setStatus(SRV);
			veganOrder->setArrTime(currentTimeStep);
			inservice_Vegan_orders.enqueue(veganOrder);

			Vegan_cooks.enqueue(assignedCook);
			continue;
		}

		// No Vegan cook available, order must wait
		break;
	}

	//normal  l  vip mn 8er vegan

	while (!normal_orders.isEmpty())
	{
		Order* normalOrder = nullptr;

		// Check if normal order exists
		if (!normal_orders.peek(normalOrder))
			break;

		Cook* assignedCook = nullptr;

		// Try Normal cook first
		if (Normal_cooks.dequeue(assignedCook))
		{
			normal_orders.dequeue(normalOrder);
			normalOrder->setStatus(SRV);
			normalOrder->setArrTime(currentTimeStep);
			inservice_normal_orders.enqueue(normalOrder);

			Normal_cooks.enqueue(assignedCook);
			continue;
		}

		// Try VIP cook if Normal cook not available
		if (VIP_cook.dequeue(assignedCook))
		{
			normal_orders.dequeue(normalOrder);
			normalOrder->setStatus(SRV);
			normalOrder->setArrTime(currentTimeStep);
			inservice_normal_orders.enqueue(normalOrder);

			VIP_cook.enqueue(assignedCook);
			continue;
		}

		// mafesh cook available (Vegan cooks mayenfa3sh te3ml Normal orders)
		break;
	}
}



int GetVIPQueueCount(priQueue<Order*>& q)
{
	Order* ptr = nullptr;
	int pr = 0;
	priQueue<Order*> temp;
	int cnt = 0;

	while (q.dequeue(ptr, pr))
	{
		cnt++;
		temp.enqueue(ptr, pr);
	}
	while (temp.dequeue(ptr, pr))
		q.enqueue(ptr, pr);

	return cnt;
}


void Restaurant::RunSimulation()
{
	pGUI = new GUI; //creates a new object of GUI in heap (creates interface)
	PROG_MODE mode = pGUI->getGUIMode(); // reads user choice of the mode (interactive , step by step  , silent)

	// ask user for input file name
	pGUI->PrintMessage("Enter input filename (e.g., input.txt) then press ENTER:");
	string filename = pGUI->GetString();

	if (filename.empty()) {
		filename = "input.txt";
		// lw el mode msh silent eb2y warri message
		if (mode != MODE_SLNT) {
			pGUI->PrintMessage("Using default: input.txt");
			Sleep(1500);
		}
	}
	else {
		// message en file bytla3
		if (mode != MODE_SLNT) {
			pGUI->PrintMessage("Loading: " + filename + "...");
			Sleep(1000);
		}
	}

	// load file yenaam el cooks w el events
	LoadFile(filename);

	int TimeStep = 1;

	// bne-warri el initial state abl el simulation tebda2
	FillDrawingList();

	pGUI->PrintMessage("Time Step: 0 (Initial State)\nPress any key to start simulation...");
	if (mode == MODE_INTR) {
		pGUI->waitForClick();
	}
	else if (mode == MODE_STEP) {
		Sleep(1000);
	}

	while (true)
	{
		// 1) run kol el events el 3la el timestep da
		ExecuteEvents(TimeStep);


		// 2) na7awel wa7ed bas mn waiting -> in-service 
		Order* o = nullptr;
		if (normal_orders.dequeue(o))
		{
			o->setStatus(SRV);
			inservice_normal_orders.enqueue(o);
		}
		if (vegan_orders.dequeue(o))
		{
			o->setStatus(SRV);
			inservice_Vegan_orders.enqueue(o);
		}
		{
			int pr;
			if (vip_orders.dequeue(o, pr))
			{
				o->setStatus(SRV);
				inservice_VIP_orders.enqueue(o);
			}
		}

		// 3) kol 5 time steps bn5alles order wa7ed mn el in-service
		if (TimeStep % 5 == 0)
		{
			Order* p = nullptr;
			if (inservice_normal_orders.dequeue(p))
			{
				p->setStatus(DONE); finished_Orders.enqueue(p);
			}
			if (inservice_Vegan_orders.dequeue(p))
			{
				p->setStatus(DONE); finished_Orders.enqueue(p);
			}
			if (inservice_VIP_orders.dequeue(p))
			{
				p->setStatus(DONE); finished_Orders.enqueue(p);
			}
		}


		// 4) n-update el GUI
		FillDrawingList();

		// 5) bn-build el message bta3 el status
		int waitingNorm = GetQueueCount<LinkedQueue<Order*>, Order*>(normal_orders);
		int waitingVeg = GetQueueCount<LinkedQueue<Order*>, Order*>(vegan_orders);
		int waitingVIP = GetVIPQueueCount(vip_orders);
		int cookNorm = GetQueueCount<LinkedQueue<Cook*>, Cook*>(Normal_cooks);
		int cookVeg = GetQueueCount<LinkedQueue<Cook*>, Cook*>(Vegan_cooks);
		int cookVIP = GetQueueCount<LinkedQueue<Cook*>, Cook*>(VIP_cook);


		int inServiceN = GetQueueCount<LinkedQueue<Order*>, Order*>(inservice_normal_orders);
		int inServiceG = GetQueueCount<LinkedQueue<Order*>, Order*>(inservice_Vegan_orders);
		int inServiceV = GetQueueCount<LinkedQueue<Order*>, Order*>(inservice_VIP_orders);
		int finishedC = GetQueueCount<LinkedQueue<Order*>, Order*>(finished_Orders);

		stringstream ss;
		ss << "Time Step: " << TimeStep << "\n";
		ss << "Waiting Orders -> N:" << waitingNorm << "  G:" << waitingVeg << "  V:" << waitingVIP << "\n";
		ss << "Available Cooks -> N:" << cookNorm << "  G:" << cookVeg << "  V:" << cookVIP << "\n";
		ss << "In-service -> N:" << inServiceN << "  G:" << inServiceG << "  V:" << inServiceV
			<< "   Finished: " << finishedC;


		pGUI->PrintMessage(ss.str());

		// 6) lw mafish events w mafish orders yb2a el simulation 5elset
		bool eventsEmpty = true;
		Event* pe = nullptr;
		if (EventsQueue.peekFront(pe)) eventsEmpty = false;

		bool anyActive = false;
		if (!normal_orders.isEmpty() || !vegan_orders.isEmpty() || !vip_orders.isEmpty() ||
			!inservice_normal_orders.isEmpty() || !inservice_Vegan_orders.isEmpty() || !inservice_VIP_orders.isEmpty())
			anyActive = true;

		if (eventsEmpty && !anyActive)
			break;

		// 7) el mode by7km el wait
		if (mode == MODE_INTR)
		{
			pGUI->waitForClick(); // wait for click
		}
		else if (mode == MODE_STEP)
		{
			Sleep(1000); // wait 1 sec
		}
		else // MODE_SILENT
		{
			// no wait fe silent 
		}

		TimeStep++;
	}


	// message fe el end
	pGUI->PrintMessage("simulation done! all orders processed.");
	pGUI->waitForClick();

	delete pGUI;
	pGUI = nullptr;
}

