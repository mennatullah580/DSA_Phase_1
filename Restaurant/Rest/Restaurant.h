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
#include "../Dynamic behaviour.h"
#include"../Cookassaignment.h"

// it is the maestro of the project
// Restaurant is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue; // Queue of all events that will be loaded from file
	
	// ========== ORDER QUEUES ==========
	LinkedQueue<Order*> normal_orders;  // Queue of all waiting normal orders
	LinkedQueue<Order*> vegan_orders;   // Queue of all waiting vegan orders
	priQueue<Order*> vip_orders;        // Priority queue of all waiting VIP orders
	
	LinkedQueue<Order*> inservice_normal_orders;  // Normal orders being prepared
	LinkedQueue<Order*> inservice_Vegan_orders;   // Vegan orders being prepared
	LinkedQueue<Order*> inservice_VIP_orders;     // VIP orders being prepared
	
	LinkedQueue<Order*> finished_Orders;  // Finished orders queue
	
	// ========== COOK QUEUES ==========
	LinkedQueue<Cook*> Normal_cooks;  // Available Normal cooks
	LinkedQueue<Cook*> Vegan_cooks;   // Available Vegan cooks
	LinkedQueue<Cook*> VIP_cook;      // Available VIP cooks
	
	// PHASE 2: Additional cook queues
	LinkedQueue<Cook*> onBreak_cooks;   // Cooks currently on break
	LinkedQueue<Cook*> injured_cooks;   // Cooks currently injured/recovering
	
	// ========== PHASE 2: DYNAMIC BEHAVIOR MANAGEMENT ==========
	DynamicBehaviorManager behaviorManager;  // Manages injuries, overtime, etc.
	AssignmentManager assignmentManager;     // Tracks cook-order assignments
	
	// ========== SIMULATION PARAMETERS ==========
	int ordersBeforeBreak;  // BO: Number of orders before cook needs break
	int autoPromotionTime;  // AutoP: Timesteps before auto-promotion
	
	// ========== STATISTICS ==========
	int totalInjuries;              // Total injuries during simulation
	int totalOvertimeActivations;   // Total times overtime was activated
	int totalBreaksTaken;           // Total breaks taken by all cooks
	int totalAutoPromotions;        // Total auto-promotions that occurred
	
public:
	// ========== CONSTRUCTOR & DESTRUCTOR ==========
	Restaurant();
	~Restaurant();
	
	// ========== MAIN SIMULATION FUNCTIONS ==========
	void RunSimulation();           // Runs the entire simulation
	void ExecuteEvents(int TimeStep); // Executes all events at current timestep
	void LoadFile(const string& filename); // Loads data from input file
	
	// ========== ORDER MANAGEMENT ==========
	void AddOrder(Order*& pOrd);     // Adds order to appropriate waiting queue
	bool CancelOrder(int id);        // Removes order from waiting queue
	double calc_vipweight(int size, double price, int arrival_time); // VIP priority calculation
	
	// ========== COOK MANAGEMENT ==========
	Cook* CreateCook(int speed, int breakTime, ORD_TYPE type, int id); // Creates cook instance
	Cook* getAvailableCook(ORD_TYPE type); // Gets first available cook of specified type
	
	// ========== PHASE 2: DYNAMIC BEHAVIOR FUNCTIONS ==========
	void updateAllCooks();           // Update breaks and injuries for all cooks each timestep
	void checkForInjuries();         // Random injury checks for available cooks
	void handleOvertime();           // Check and activate overtime if needed
	void handleInjuredCooks();       // Process injured cooks, check for forced work
	
	// ========== PHASE 2: ORDER ASSIGNMENT & COMPLETION ==========
	void assignOrderToCook(Order* order, Cook* cook, int currentTime);
	void processCompletedOrders(int currentTime); // Check for finished orders and process them
	
	// ========== GUI & DISPLAY ==========
	void FillDrawingList();          // Updates GUI drawing list with current state
};

// ========== HELPER TEMPLATE FUNCTIONS ==========
// These are used for counting items in queues

template<typename Q, typename T>
int GetQueueCount(Q& q);
// Specialized version for VIP priority queue
int GetVIPQueueCount(priQueue<Order*>& q);

#endif