#include "Cook.h"


Cook::Cook() // constructor
{
	ID = 0;
	
	type = TYPE_NRM;
	
	baseSpeed = 0;
	
	current_speed = 0;
	
	breakduration = 0;
	
	ordersBeforeBreak = 0;
	
	ordersDone = 0;
	
	breakremaining = 0;
	
	overtime = false;
	
	overtimeserved = 0;
	
	is_injured = false;
	
	injRecovery_time = 0;
	
	totalinj = 0;
	
	
	totalOrdersServed = 0;
	
	totalBreaksTaken = 0;
	
	breakTimesTaken = 0;

}


Cook::~Cook() // destructor
{
}


int Cook::GetID() const // cook id getter
{
	return ID;
}

	
ORD_TYPE Cook::GetType() const // cook type getter
{
	return type;
}


void Cook::setID(int id) // cook id setter
{
	ID = id;
}

void Cook::setType(ORD_TYPE t) // cook type setter
{
	type = t;
}

void Cook::setBaseSpeed(int s) // cook speed setter
{
	baseSpeed = s; // Initialize baseSpeed when speed is set
	current_speed = 0;
}

int Cook::getBaseSpeed() const // cook speed setter
{
	return baseSpeed;
}

double Cook::getCurrentSpeed() const {

	return current_speed;
}


void Cook::setbreakduration(int br) // cook breaks setter
{
	breakduration = br;
}

int Cook::getbreakduration() const // cook breaks getter
{
	return breakduration;
}


void Cook::setOrdersbeforebreak(int n)
{
	ordersBeforeBreak = n;
}

int Cook::getOrdersbeforebreak() const {

	return ordersBeforeBreak;
}

bool Cook::needsBreak() const
{
	return ordersDone >= ordersBeforeBreak && !overtime;
}


void Cook::Reset_Speed()
{
	current_speed = baseSpeed;
	overtime = false;
	overtimeserved = 0;
}




void Cook::startBreak()
{
	breakremaining = breakduration;
	ordersDone = 0; // Reset order counter
	Reset_Speed(); // Restore speed to base
	totalBreaksTaken++;
}

void Cook::updateBreak()
{
	if (breakremaining > 0)
	{
		breakremaining--;
		breakTimesTaken++;
	}
}

bool Cook::isOnBreak() const { return breakremaining > 0; }
int Cook::getBreakTimeRemaining() const { return breakremaining; }

// Fatigue system
void Cook::applyFatigue()
{
	// Apply normal fatigue
	current_speed *= fatigue_factor;

	// Ensure speed doesn't fall below minimum
	double minSpeed = baseSpeed * speed_ratio;
	if (current_speed < minSpeed)
		current_speed = minSpeed;
}

void Cook::applyOvertimeFatigue()
{
	// Extra fatigue penalty for working overtime
	current_speed *= overtime_penalty;

	double minSpeed = baseSpeed * speed_ratio;
	if (current_speed < minSpeed)
		current_speed = minSpeed;
}

double Cook::getSpeedRatio() const
{
	if (baseSpeed == 0) return 0;
	return current_speed / baseSpeed;
}

// Overtime management
void Cook::enterOvertime()
{
	overtime = true;
	overtimeserved = 0;
}

void Cook::exitOvertime()
{
	overtime = false;
	// Apply penalty: reduce speed or increase required break time
	applyOvertimeFatigue();
}

bool Cook::isOnOvertime() const { return overtime; }

bool Cook::canSkipBreak() const
{
	// Can skip break if not already on overtime and needs break
	return needsBreak() && !overtime && !is_injured;
}

// Health emergency system
void Cook::triggerInjury(int recoveryDuration)
{
	if (totalinj < MAX_INJURIES)
	{
		is_injured = true;
		injRecovery_time = recoveryDuration;
		totalinj++;
	}
}

void Cook::updateInjuryRecovery()
{
	if (injRecovery_time > 0)
	{
		injRecovery_time--;
		if (injRecovery_time == 0)
			is_injured = false;
	}
}

bool Cook::isInjuredStatus() const { return is_injured; }
int Cook::getInjuryRecoveryTime() const { return injRecovery_time; }

bool Cook::canBeInjured() const
{
	return totalinj < MAX_INJURIES && !is_injured;
}

void Cook::forceWorkWhileInjured()
{
	// Reduce speed to half when forced to work injured
	current_speed = baseSpeed * injury_penalty;
}

int Cook::getTotalInjuries() const { return totalinj; }

// Order completion tracking
void Cook::completeOrder()
{
	ordersDone++;
	totalOrdersServed++;

	if (overtime)
		overtimeserved++;

	// Apply fatigue after each order
	applyFatigue();

	// Check if needs break
	if (needsBreak() && !overtime)
	{
		startBreak();
	}
}

int Cook::getTotalOrdersServed() const { return totalOrdersServed; }

// Availability check
bool Cook::isAvailable() const
{
	return !isOnBreak() && !is_injured;
}

// Statistics
int Cook::getTotalBreaksTaken() const { return totalBreaksTaken; }
int Cook::getBreakTimeTaken() const { return breakTimesTaken; }

// Calculate service time for an order
int Cook::calculateServiceTime(int orderSize) const
{
	if (current_speed <= 0) return 999999; // Infinite time if no speed

	// Service time = ceiling(orderSize / currentSpeed)
	return (int)ceil((double)orderSize / current_speed);
}


