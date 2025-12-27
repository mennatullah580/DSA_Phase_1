#ifndef DYNAMIC_BEHAVIOR_MANAGER_H
#define DYNAMIC_BEHAVIOR_MANAGER_H

#include <random>
#include <ctime>
#include "Rest/Cook.h"
#include "LinkedQueue.h"

// Manages dynamic behavior for cooks (injuries, overtime decisions)
class DynamicBehaviorManager
{
private:
	// Random number generation
	std::mt19937 rng;
	std::uniform_real_distribution<double> probDist;

	// Injury parameters
	static constexpr double BASE_INJURY_PROBABILITY = 0.001; // 0.1% per timestep
	static constexpr double OVERTIME_INJURY_MULTIPLIER = 3.0; // 3x more likely when overtime
	static constexpr int MIN_INJURY_RECOVERY = 10; // Minimum recovery time
	static constexpr int MAX_INJURY_RECOVERY = 30; // Maximum recovery time

	// Overtime threshold
	int vipOvertimeThreshold; // Number of waiting VIP orders to trigger overtime

public:
	DynamicBehaviorManager()
		: probDist(0.0, 1.0)
	{
		// Seed with current time
		rng.seed(static_cast<unsigned int>(time(nullptr)));
		vipOvertimeThreshold = 5; // Default threshold
	}

	void setVIPOvertimeThreshold(int threshold)
	{
		vipOvertimeThreshold = threshold;
	}

	int getVIPOvertimeThreshold() const
	{
		return vipOvertimeThreshold;
	}

	// Check if cook should get injured this timestep
	bool shouldTriggerInjury(Cook* cook)
	{
		if (!cook || !cook->canBeInjured() || !cook->isAvailable())
			return false;

		double probability = BASE_INJURY_PROBABILITY;

		// Increase probability if on overtime
		if (cook->isOnOvertime())
			probability *= OVERTIME_INJURY_MULTIPLIER;

		// Increase probability based on fatigue level
		double speedRatio = cook->getSpeedRatio();
		if (speedRatio < 0.7) // If speed dropped below 70%
			probability *= 2.0;

		double roll = probDist(rng);
		return roll < probability;
	}

	// Generate random injury recovery time
	int generateInjuryRecoveryTime()
	{
		std::uniform_int_distribution<int> recoveryDist(MIN_INJURY_RECOVERY, MAX_INJURY_RECOVERY);
		return recoveryDist(rng);
	}

	// Decide if system should force overtime based on VIP queue
	bool shouldEnterOvertime(int waitingVIPCount)
	{
		return waitingVIPCount >= vipOvertimeThreshold;
	}

	// Decide which cook should enter overtime (prefer least fatigued)
	Cook* selectCookForOvertime(LinkedQueue<Cook*>& cookQueue, ORD_TYPE type)
	{
		Cook* selectedCook = nullptr;
		double bestSpeedRatio = 0.0;

		// Find cook with highest speed ratio (least fatigued) who needs break
		LinkedQueue<Cook*> tempQueue;
		Cook* c = nullptr;

		while (cookQueue.dequeue(c))
		{
			if (c->GetType() == type && c->canSkipBreak())
			{
				double ratio = c->getSpeedRatio();
				if (ratio > bestSpeedRatio)
				{
					bestSpeedRatio = ratio;
					selectedCook = c;
				}
			}
			tempQueue.enqueue(c);
		}

		// Restore queue
		while (tempQueue.dequeue(c))
			cookQueue.enqueue(c);

		return selectedCook;
	}

	// Check if injured cook should be forced to work
	bool shouldForceInjuredCook(int waitingOrdersCount, int availableCooksCount)
	{
		// Force injured cook only in extreme overload
		return (availableCooksCount == 0 && waitingOrdersCount > 10);
	}
};

#endif // DYNAMIC_BEHAVIOR_MANAGER_H