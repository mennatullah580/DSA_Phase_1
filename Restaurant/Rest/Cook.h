#pragma once

#include "..\Defs.h"
#include	<iostream>
using namespace std;
#pragma once
class Cook
{
	int ID; // cook ID
	ORD_TYPE type;	//for each order type there is a corresponding cook type (VIP, Normal, Vegan)
	
	
	// hena el speed attributes:
	
	int baseSpeed;  // The original speed of the cook
	double current_speed; // current speed b3d el fatigue



	// hena el break attributes:

	int ordersDone; // Number of orders completed since last break
	int ordersBeforeBreak; // Number of orders before taking a break
	int breakduration; // time needed for this cook to take a break
	int breakremaining;

	// hena el fatigue attributes:
	static constexpr double fatigue_factor = 0.98; // Speed multiplier after each order
	static constexpr double speed_ratio = 0.5; // Minimum speed ratio (50% of base)

	// hena el overtime attributes:

	bool overtime; // is the cook currently in overtime?
	int overtimeserved; // 3dd el orders ely served during OT
	static constexpr double overtime_penalty = 0.90; // Extra fatigue for overtime

	// hena el cook health emergency health system attributes:

	bool is_injured; // hl el cook injured wla la2
	int injRecovery_time; //el cook 23d 2d eh bra unavailable
	int totalinj; // total number of injuries
	static constexpr int MAX_INJURIES = 3; // Maximum injuries allowed
	static constexpr double injury_penalty = 0.5; // Speed when forced to work injured

	int totalOrdersServed;
	int totalBreaksTaken;
	int breakTimesTaken;


public:
	Cook(); // constructor
	
	virtual ~Cook(); // destructor (virtual as class is inherited)
	
	
	// primary setters
	void setID(int id);
	void setType(ORD_TYPE t);
	
	// primary getters
	int GetID() const;
	ORD_TYPE GetType() const;


	// speed setters
	void setBaseSpeed(int s);

	void Reset_Speed(); // resets speed 


	//speed getters
	int getBaseSpeed() const;
	double getCurrentSpeed() const;

	// break setters
	void setbreakduration(int b);
	void setOrdersbeforebreak(int orders);

	// break getters
	int getbreakduration() const;
	int getOrdersbeforebreak() const;

	//break managment:
	bool needsBreak() const;
	void startBreak();
	void updateBreak(); // Call each timestep
	bool isOnBreak() const;
	int getBreakTimeRemaining() const;


	// Fatigue system
	void applyFatigue(); // hena called b3d kol order to apply fatigue
	void applyOvertimeFatigue(); // Extra fatigue for overtime
	double getSpeedRatio() const; // Returns currentSpeed / baseSpeed


	// Overtime management
	void enterOvertime();
	void exitOvertime();
	bool isOnOvertime() const;
	bool canSkipBreak() const; // Check if can enter overtime

	// Health emergency system
	void triggerInjury(int recoveryDuration);
	void updateInjuryRecovery(); // Call each timestep
	bool isInjuredStatus() const;
	int getInjuryRecoveryTime() const;
	bool canBeInjured() const; // Check if reached max injuries
	void forceWorkWhileInjured(); // Apply penalty for working injured
	int getTotalInjuries() const;

	// Order completion tracking
	void completeOrder(); // Call when cook finishes an order
	int getTotalOrdersServed() const;

	// Availability check
	bool isAvailable() const; // hena bt2ked en el order availble not on break or injured

	// Statistics
	int getTotalBreaksTaken() const;
	int getBreakTimeTaken() const;

	// Calculate service time for an order
	int calculateServiceTime(int orderSize) const;



};
