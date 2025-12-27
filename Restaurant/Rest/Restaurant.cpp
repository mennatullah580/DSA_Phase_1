using namespace std;
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <iostream>

#include <sstream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "../CancelEvent.h"
#include "../linkedStack.h"
#include "../linkedQueue.h"
#include "../QueueADT.h"


//LOJIIII

Restaurant::Restaurant() {
	pGUI = nullptr;
	ordersBeforeBreak = 0;
	autoPromotionTime = 0;
	totalInjuries = 0;
	totalOvertimeActivations = 0;
	totalBreaksTaken = 0;
	totalAutoPromotions = 0;
} // constructor

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
	Cook* c = new Cook();
	c->setBaseSpeed(speed);      // PHASE 2: Use setBaseSpeed instead of setSpeed
	c->setbreakduration(breakTime);
	c->setType(type);
	c->setID(id);
	return c;
}

void Restaurant::LoadFile(const string& filename)
{
	ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << "Error! Cannot open file: " << filename << endl;
		return;
	}

	int N, G, V;    // Number of cooks for each type
	int SN, SG, SV; // Speed of cooks for each type
	int BO, BN, BG, BV; // BO: orders before break, BN/BG/BV: break duration for each type
	int AutoP;      // Auto-promotion limit
	int M;          // Number of events

	string line;

	// Line 1: Number of cooks (N G V)
	getline(infile, line);
	stringstream l1(line);
	l1 >> N >> G >> V;

	// Line 2: Cook speeds (SN SG SV)
	getline(infile, line);
	stringstream l2(line);
	l2 >> SN >> SG >> SV;

	// Line 3: Break info (BO BN BG BV)
	getline(infile, line);
	stringstream l3(line);
	l3 >> BO >> BN >> BG >> BV;

	

	// Line 4: Auto-promotion limit
	getline(infile, line);
	stringstream l4(line);
	l4 >> AutoP;

	// Line 5: Number of events
	getline(infile, line);
	stringstream l5(line);
	l5 >> M;

	// Create Normal cooks
	for (int i = 0; i < N; i++)
	{
		Cook* c = CreateCook(SN, BN, TYPE_NRM, i + 1);
		c->setOrdersbeforebreak(BO); // PHASE 2: Set orders before break
		Normal_cooks.enqueue(c);
	}

	// Create Vegan cooks
	for (int i = 0; i < G; i++)
	{
		Cook* c = CreateCook(SG, BG, TYPE_VGAN, i + 1);
		c->setOrdersbeforebreak(BO); // PHASE 2: Set orders before break
		Vegan_cooks.enqueue(c);
	}

	// Create VIP cooks
	for (int i = 0; i < V; i++)
	{
		Cook* c = CreateCook(SV, BV, TYPE_VIP, i + 1);
		c->setOrdersbeforebreak(BO); // PHASE 2: Set orders before break
		VIP_cook.enqueue(c);
	}

	// Read and process events
	for (int i = 0; i < M; i++)
	{
		getline(infile, line);
		stringstream ss(line);
		char eventType;
		ss >> eventType;

		if (eventType == 'R') // Arrival event
		{
			char type;      // Order type (N, G, V)
			int TS;         // Timestamp
			int ID;         // Order ID
			int size;       // Order size (number of dishes)
			double price;   // Order price
			int dist;       // Distance (if used in your input format)

			ss >> type >> TS >> ID >> size >> price >> dist;

			Event* e = new ArrivalEvent(TS, type, ID, size, price, dist);
			EventsQueue.enqueue(e);
		}
		else if (eventType == 'X') // Cancellation event
		{
			int TS;  // Timestamp
			int ID;  // Order ID to cancel

			ss >> TS >> ID;

			Event* e = new CancelEvent(TS, ID);
			EventsQueue.enqueue(e);
		}
		else if (eventType == 'P') // Promotion event
		{
			int TS;        // Timestamp
			int ID;        // Order ID to promote
			int ExMony;    // Extra money paid

			ss >> TS >> ID >> ExMony;

			//Event* e = new PromotionEvent(TS, ID, ExMony);
			//EventsQueue.enqueue(e);
			// Note: You'll need to implement PromotionEvent::Execute() in Phase 2
		}
		else
		{
			cout << "Warning: Unknown event type '" << eventType << "' on line " << (i + 6) << endl;
			// Continue reading other events instead of returning
		}
	}

	infile.close();

	cout << "File loaded successfully!" << endl;
	cout << "Cooks created - Normal: " << N << ", Vegan: " << G << ", VIP: " << V << endl;
	cout << "Events loaded: " << M << endl;
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

// special version for VIP priority queue
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


void Restaurant::updateAllCooks()
{
	// Lambda to update cooks in a queue
	auto updateQueue = [](LinkedQueue<Cook*>& queue)
		{
			Cook* c = nullptr;
			LinkedQueue<Cook*> temp;
			while (queue.dequeue(c))
			{
				c->updateBreak();
				c->updateInjuryRecovery();
				temp.enqueue(c);
			}
			while (temp.dequeue(c))
				queue.enqueue(c);
		};

	// Update all available cooks
	updateQueue(Normal_cooks);
	updateQueue(Vegan_cooks);
	updateQueue(VIP_cook);

	// Move cooks from break back to available
	{
		Cook* c = nullptr;
		LinkedQueue<Cook*> temp;
		while (onBreak_cooks.dequeue(c))
		{
			c->updateBreak();
			if (!c->isOnBreak())
			{
				// Break finished, return to appropriate queue
				switch (c->GetType())
				{
				case TYPE_NRM:
					Normal_cooks.enqueue(c);
					break;
				case TYPE_VGAN:
					Vegan_cooks.enqueue(c);
					break;
				case TYPE_VIP:
					VIP_cook.enqueue(c);
					break;
				}
			}
			else
			{
				temp.enqueue(c);
			}
		}
		while (temp.dequeue(c))
			onBreak_cooks.enqueue(c);
	}

	// Move cooks from injured back to available
	{
		Cook* c = nullptr;
		LinkedQueue<Cook*> temp;
		while (injured_cooks.dequeue(c))
		{
			c->updateInjuryRecovery();
			if (!c->isInjuredStatus())
			{
				// Recovery complete, return to appropriate queue
				switch (c->GetType())
				{
				case TYPE_NRM:
					Normal_cooks.enqueue(c);
					break;
				case TYPE_VGAN:
					Vegan_cooks.enqueue(c);
					break;
				case TYPE_VIP:
					VIP_cook.enqueue(c);
					break;
				}
			}
			else
			{
				temp.enqueue(c);
			}
		}
		while (temp.dequeue(c))
			injured_cooks.enqueue(c);
	}
}

void Restaurant::checkForInjuries()
{
	// Lambda to check injuries in a queue
	auto checkQueue = [this](LinkedQueue<Cook*>& queue)
		{
			Cook* c = nullptr;
			LinkedQueue<Cook*> temp;

			while (queue.dequeue(c))
			{
				// Only check if cook is available and not busy
				if (c->isAvailable() && !assignmentManager.isCookBusy(c))
				{
					if (behaviorManager.shouldTriggerInjury(c))
					{
						int recoveryTime = behaviorManager.generateInjuryRecoveryTime();
						c->triggerInjury(recoveryTime);
						injured_cooks.enqueue(c);
						totalInjuries++;

						cout << "INJURY! Cook " << c->GetID() << " (Type: "
							<< (c->GetType() == TYPE_NRM ? "Normal" :
								c->GetType() == TYPE_VGAN ? "Vegan" : "VIP")
							<< ") needs " << recoveryTime << " timesteps recovery" << endl;
					}
					else
					{
						temp.enqueue(c);
					}
				}
				else
				{
					temp.enqueue(c);
				}
			}

			while (temp.dequeue(c))
				queue.enqueue(c);
		};

	checkQueue(Normal_cooks);
	checkQueue(Vegan_cooks);
	checkQueue(VIP_cook);
}

void Restaurant::handleOvertime()
{
	int vipWaiting = GetVIPQueueCount(vip_orders);

	if (behaviorManager.shouldEnterOvertime(vipWaiting))
	{
		// Try Normal cooks first
		Cook* c = nullptr;
		LinkedQueue<Cook*> temp;
		bool foundOvertimeCook = false;

		while (Normal_cooks.dequeue(c))
		{
			if (!foundOvertimeCook && c->canSkipBreak() && !assignmentManager.isCookBusy(c))
			{
				c->enterOvertime();
				totalOvertimeActivations++;
				foundOvertimeCook = true;

				cout << "OVERTIME! Normal Cook " << c->GetID()
					<< " skipping break due to " << vipWaiting
					<< " waiting VIP orders!" << endl;
			}
			temp.enqueue(c);
		}

		while (temp.dequeue(c))
			Normal_cooks.enqueue(c);

		// Could also check VIP cooks if needed
		if (!foundOvertimeCook)
		{
			LinkedQueue<Cook*> temp2;
			while (VIP_cook.dequeue(c))
			{
				if (!foundOvertimeCook && c->canSkipBreak() && !assignmentManager.isCookBusy(c))
				{
					c->enterOvertime();
					totalOvertimeActivations++;
					foundOvertimeCook = true;

					cout << "OVERTIME! VIP Cook " << c->GetID()
						<< " skipping break due to " << vipWaiting
						<< " waiting VIP orders!" << endl;
				}
				temp2.enqueue(c);
			}

			while (temp2.dequeue(c))
				VIP_cook.enqueue(c);
		}
	}
}

void Restaurant::handleInjuredCooks()
{
	// Count waiting orders
	int waitingOrders = GetQueueCount<LinkedQueue<Order*>, Order*>(normal_orders) +
		GetQueueCount<LinkedQueue<Order*>, Order*>(vegan_orders) +
		GetVIPQueueCount(vip_orders);

	// Count available cooks
	int availableCooks = GetQueueCount<LinkedQueue<Cook*>, Cook*>(Normal_cooks) +
		GetQueueCount<LinkedQueue<Cook*>, Cook*>(Vegan_cooks) +
		GetQueueCount<LinkedQueue<Cook*>, Cook*>(VIP_cook);

	// Force injured cooks to work if system is overloaded
	if (behaviorManager.shouldForceInjuredCook(waitingOrders, availableCooks))
	{
		Cook* c = nullptr;
		LinkedQueue<Cook*> temp;
		bool forcedCook = false;

		while (injured_cooks.dequeue(c) && !forcedCook)
		{
			c->forceWorkWhileInjured();

			// Return to appropriate queue
			switch (c->GetType())
			{
			case TYPE_NRM:
				Normal_cooks.enqueue(c);
				break;
			case TYPE_VGAN:
				Vegan_cooks.enqueue(c);
				break;
			case TYPE_VIP:
				VIP_cook.enqueue(c);
				break;
			}

			forcedCook = true;

			cout << "EMERGENCY! Forcing injured Cook " << c->GetID()
				<< " to work at reduced speed" << endl;
		}

		// Put remaining injured cooks back
		while (temp.dequeue(c))
			injured_cooks.enqueue(c);
	}
}

Cook* Restaurant::getAvailableCook(ORD_TYPE type)
{
	LinkedQueue<Cook*>* targetQueue = nullptr;

	switch (type)
	{
	case TYPE_NRM:
		targetQueue = &Normal_cooks;
		break;
	case TYPE_VGAN:
		targetQueue = &Vegan_cooks;
		break;
	case TYPE_VIP:
		targetQueue = &VIP_cook;
		break;
	default:
		return nullptr;
	}

	Cook* c = nullptr;
	LinkedQueue<Cook*> temp;
	Cook* availableCook = nullptr;

	while (targetQueue->dequeue(c))
	{
		if (!availableCook && c->isAvailable() && !assignmentManager.isCookBusy(c))
		{
			availableCook = c;
		}
		temp.enqueue(c);
	}

	while (temp.dequeue(c))
		targetQueue->enqueue(c);

	return availableCook;
}


void Restaurant::assignOrderToCook(Order* order, Cook* cook, int currentTime)
{
	// Create assignment
	assignmentManager.addAssignment(cook, order, currentTime);

	// Mark order as in-service
	order->setStatus(SRV);

	// Add to appropriate in-service queue
	switch (order->GetType())
	{
	case 'N':
		inservice_normal_orders.enqueue(order);
		break;
	case 'G':
		inservice_Vegan_orders.enqueue(order);
		break;
	case 'V':
		inservice_VIP_orders.enqueue(order);
		break;
	}

	cout << "Assigned Order " << order->GetID() << " to Cook "
		<< cook->GetID() << " (Service Time: "
		<< cook->calculateServiceTime(order->getOrderSize()) << ")" << endl;
}

void Restaurant::processCompletedOrders(int currentTime)
{
	LinkedQueue<CookAssignment*> completed =
		assignmentManager.checkCompletedAssignments(currentTime);

	CookAssignment* assignment;
	while (completed.dequeue(assignment))
	{
		Order* order = assignment->order;
		Cook* cook = assignment->cook;

		// Remove from in-service queue
		{
			LinkedQueue<Order*>* inServiceQueue = nullptr;
			switch (order->GetType())
			{
			case 'N':
				inServiceQueue = &inservice_normal_orders;
				break;
			case 'G':
				inServiceQueue = &inservice_Vegan_orders;
				break;
			case 'V':
				inServiceQueue = &inservice_VIP_orders;
				break;
			}

			if (inServiceQueue)
			{
				Order* o = nullptr;
				LinkedQueue<Order*> temp;
				while (inServiceQueue->dequeue(o))
				{
					if (o != order)
						temp.enqueue(o);
				}
				while (temp.dequeue(o))
					inServiceQueue->enqueue(o);
			}
		}

		// Mark order as done
		order->setStatus(DONE);
		finished_Orders.enqueue(order);

		// Cook completes order (applies fatigue, checks break)
		cook->completeOrder();

		// Handle cook's next state
		if (cook->needsBreak() && !cook->isOnOvertime())
		{
			cook->startBreak();
			onBreak_cooks.enqueue(cook);
			totalBreaksTaken++;
			cout << "Cook " << cook->GetID() << " taking break for "
				<< cook->getbreakduration() << " timesteps" << endl;
		}
		else
		{
			// Check if should exit overtime
			if (cook->isOnOvertime())
			{
				int vipCount = GetVIPQueueCount(vip_orders);
				if (vipCount < 3) // Exit overtime when VIP load is low
				{
					cook->exitOvertime();
					cout << "Cook " << cook->GetID() << " exiting overtime" << endl;
				}
			}

			// Cook remains in available queue
		}

		cout << "Order " << order->GetID() << " completed by Cook "
			<< cook->GetID() << " at timestep " << currentTime << endl;

		delete assignment;
	}
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();

	// Ask user for input file name
	pGUI->PrintMessage("Enter input filename (e.g., input.txt) then press ENTER:");
	string filename = pGUI->GetString();

	if (filename.empty())
	{
		filename = "input.txt";
		if (mode != MODE_SLNT)
		{
			pGUI->PrintMessage("Using default: input.txt");
			Sleep(1500);
		}
	}
	else
	{
		if (mode != MODE_SLNT)
		{
			pGUI->PrintMessage("Loading: " + filename + "...");
			Sleep(1000);
		}
	}

	// Load file (creates cooks and events)
	LoadFile(filename);

	int TimeStep = 1;

	// Display initial state
	FillDrawingList();

	pGUI->PrintMessage("Time Step: 0 (Initial State)\nPress any key to start simulation...");
	if (mode == MODE_INTR)
	{
		pGUI->waitForClick();
	}
	else if (mode == MODE_STEP)
	{
		Sleep(1000);
	}

	// Main simulation loop
	while (true)
	{
		// ===== STEP 1: EXECUTE EVENTS =====
		ExecuteEvents(TimeStep);

		// ===== STEP 2: UPDATE ALL COOKS (BREAKS AND INJURIES) =====
		updateAllCooks();

		// ===== STEP 3: CHECK FOR INJURIES (EVERY 5 TIMESTEPS) =====
		if (TimeStep % 5 == 0)
		{
			checkForInjuries();
		}

		// ===== STEP 4: HANDLE OVERTIME =====
		handleOvertime();

		// ===== STEP 5: HANDLE INJURED COOKS (FORCED WORK) =====
		handleInjuredCooks();

		// ===== STEP 6: PROCESS COMPLETED ORDERS =====
		processCompletedOrders(TimeStep);

		// ===== STEP 7: ASSIGN NEW ORDERS TO AVAILABLE COOKS =====

		// Priority 1: VIP Orders
		// VIP orders should be served by: VIP cooks -> Normal cooks -> Vegan cooks
		{
			Order* o = nullptr;
			int pr = 0;
			if (vip_orders.peek(o, pr))
			{
				Cook* cook = getAvailableCook(TYPE_VIP);
				if (!cook) cook = getAvailableCook(TYPE_NRM);
				if (!cook) cook = getAvailableCook(TYPE_VGAN);

				if (cook)
				{
					vip_orders.dequeue(o, pr);
					assignOrderToCook(o, cook, TimeStep);
				}
			}
		}

		// Priority 2: Vegan Orders
		// Vegan orders can ONLY be served by Vegan cooks
		{
			Order* o = nullptr;
			if (vegan_orders.peek(o))
			{
				Cook* cook = getAvailableCook(TYPE_VGAN);

				if (cook)
				{
					vegan_orders.dequeue(o);
					assignOrderToCook(o, cook, TimeStep);
				}
			}
		}

		// Priority 3: Normal Orders
		// Normal orders should be served by: Normal cooks -> VIP cooks
		{
			Order* o = nullptr;
			if (normal_orders.peek(o))
			{
				Cook* cook = getAvailableCook(TYPE_NRM);
				if (!cook) cook = getAvailableCook(TYPE_VIP);

				if (cook)
				{
					normal_orders.dequeue(o);
					assignOrderToCook(o, cook, TimeStep);
				}
			}
		}

		// ===== STEP 8: UPDATE GUI =====
		FillDrawingList();

		// ===== STEP 9: BUILD STATUS MESSAGE =====
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

		int onBreak = GetQueueCount<LinkedQueue<Cook*>, Cook*>(onBreak_cooks);
		int injured = GetQueueCount<LinkedQueue<Cook*>, Cook*>(injured_cooks);

		stringstream ss;
		ss << "Time Step: " << TimeStep << "\n";
		ss << "Waiting Orders -> N:" << waitingNorm << "  G:" << waitingVeg << "  V:" << waitingVIP << "\n";
		ss << "Available Cooks -> N:" << cookNorm << "  G:" << cookVeg << "  V:" << cookVIP << "\n";
		ss << "In-service -> N:" << inServiceN << "  G:" << inServiceG << "  V:" << inServiceV << "\n";
		ss << "On Break: " << onBreak << "  Injured: " << injured << "  Finished: " << finishedC << "\n";
		ss << "Total Injuries: " << totalInjuries << "  Overtime: " << totalOvertimeActivations;

		pGUI->PrintMessage(ss.str());

		// ===== STEP 10: CHECK FOR TERMINATION =====
		bool eventsEmpty = true;
		Event* pe = nullptr;
		if (EventsQueue.peekFront(pe))
			eventsEmpty = false;

		bool anyActive = false;
		if (!normal_orders.isEmpty() || !vegan_orders.isEmpty() || !vip_orders.isEmpty() ||
			!inservice_normal_orders.isEmpty() || !inservice_Vegan_orders.isEmpty() ||
			!inservice_VIP_orders.isEmpty() || assignmentManager.getActiveCount() > 0)
			anyActive = true;

		if (eventsEmpty && !anyActive)
			break;

		// ===== STEP 11: HANDLE MODE DELAYS =====
		if (mode == MODE_INTR)
		{
			pGUI->waitForClick();
		}
		else if (mode == MODE_STEP)
		{
			Sleep(1000);
		}
		// MODE_SLNT: no delay

		TimeStep++;
	}

	// ===== SIMULATION COMPLETE =====
	stringstream finalMsg;
	finalMsg << "Simulation Complete!\n";
	finalMsg << "Final Statistics:\n";
	finalMsg << "Total Orders Finished: " << GetQueueCount<LinkedQueue<Order*>, Order*>(finished_Orders) << "\n";
	finalMsg << "Total Injuries: " << totalInjuries << "\n";
	finalMsg << "Total Overtime Activations: " << totalOvertimeActivations << "\n";
	finalMsg << "Total Breaks Taken: " << totalBreaksTaken;

	pGUI->PrintMessage(finalMsg.str());

	if (mode != MODE_SLNT)
	{
		pGUI->waitForClick();
	}

	delete pGUI;
	pGUI = nullptr;
}