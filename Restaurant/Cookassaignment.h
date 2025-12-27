#pragma once
#ifndef COOK_ASSIGNMENT_H
#define COOK_ASSIGNMENT_H

#include "Rest/Cook.h"
#include "Rest/Order.h"
#include "LinkedQueue.h"

// Structure to track which cook is working on which order
struct CookAssignment
{
	Cook* cook;
	Order* order;
	int startTime;
	int estimatedFinishTime;

	CookAssignment(Cook* c, Order* o, int start)
		: cook(c), order(o), startTime(start)
	{
		// Calculate finish time based on cook's current speed
		int serviceTime = c->calculateServiceTime(o->getOrderSize());
		estimatedFinishTime = start + serviceTime;
	}
};

// Manager class to handle all active assignments
class AssignmentManager
{
private:
	LinkedQueue<CookAssignment*> activeAssignments;

public:
	AssignmentManager() {}

	~AssignmentManager()
	{
		// Clean up all assignments
		CookAssignment* assignment;
		while (activeAssignments.dequeue(assignment))
		{
			delete assignment;
		}
	}

	// Add new assignment
	void addAssignment(Cook* cook, Order* order, int currentTime)
	{
		CookAssignment* assignment = new CookAssignment(cook, order, currentTime);
		activeAssignments.enqueue(assignment);
	}

	// Check for completed assignments at current time
	// Returns queue of finished assignments
	LinkedQueue<CookAssignment*> checkCompletedAssignments(int currentTime)
	{
		LinkedQueue<CookAssignment*> completed;
		LinkedQueue<CookAssignment*> stillActive;

		CookAssignment* assignment;
		while (activeAssignments.dequeue(assignment))
		{
			if (currentTime >= assignment->estimatedFinishTime)
			{
				completed.enqueue(assignment);
			}
			else
			{
				stillActive.enqueue(assignment);
			}
		}

		// Put still-active assignments back
		while (stillActive.dequeue(assignment))
		{
			activeAssignments.enqueue(assignment);
		}

		return completed;
	}

	// Get count of active assignments
	int getActiveCount() const
	{
		int count = 0;
		CookAssignment* assignment;
		LinkedQueue<CookAssignment*> temp;

		// Cast away const for temporary operations
		LinkedQueue<CookAssignment*>& queue =
			const_cast<LinkedQueue<CookAssignment*>&>(activeAssignments);

		while (queue.dequeue(assignment))
		{
			count++;
			temp.enqueue(assignment);
		}

		while (temp.dequeue(assignment))
		{
			queue.enqueue(assignment);
		}

		return count;
	}

	// Check if specific cook is busy
	bool isCookBusy(Cook* cook) const
	{
		bool busy = false;
		CookAssignment* assignment;
		LinkedQueue<CookAssignment*> temp;

		LinkedQueue<CookAssignment*>& queue =
			const_cast<LinkedQueue<CookAssignment*>&>(activeAssignments);

		while (queue.dequeue(assignment))
		{
			if (assignment->cook == cook)
				busy = true;
			temp.enqueue(assignment);
		}

		while (temp.dequeue(assignment))
		{
			queue.enqueue(assignment);
		}

		return busy;
	}

	// Remove assignment (e.g., for preemption)
	bool removeAssignment(Order* order, CookAssignment*& removedAssignment)
	{
		LinkedQueue<CookAssignment*> temp;
		CookAssignment* assignment;
		bool found = false;

		while (activeAssignments.dequeue(assignment))
		{
			if (!found && assignment->order == order)
			{
				removedAssignment = assignment;
				found = true;
				// Don't add to temp - effectively removing it
			}
			else
			{
				temp.enqueue(assignment);
			}
		}

		// Restore remaining assignments
		while (temp.dequeue(assignment))
		{
			activeAssignments.enqueue(assignment);
		}

		return found;
	}

	// Get all active assignments for a specific cook
	LinkedQueue<Order*> getOrdersForCook(Cook* cook) const
	{
		LinkedQueue<Order*> cookOrders;
		CookAssignment* assignment;
		LinkedQueue<CookAssignment*> temp;

		LinkedQueue<CookAssignment*>& queue =
			const_cast<LinkedQueue<CookAssignment*>&>(activeAssignments);

		while (queue.dequeue(assignment))
		{
			if (assignment->cook == cook)
			{
				cookOrders.enqueue(assignment->order);
			}
			temp.enqueue(assignment);
		}

		while (temp.dequeue(assignment))
		{
			queue.enqueue(assignment);
		}

		return cookOrders;
	}

	// Check if specific order is being prepared
	bool isOrderActive(Order* order) const
	{
		bool active = false;
		CookAssignment* assignment;
		LinkedQueue<CookAssignment*> temp;

		LinkedQueue<CookAssignment*>& queue =
			const_cast<LinkedQueue<CookAssignment*>&>(activeAssignments);

		while (queue.dequeue(assignment))
		{
			if (assignment->order == order)
				active = true;
			temp.enqueue(assignment);
		}

		while (temp.dequeue(assignment))
		{
			queue.enqueue(assignment);
		}

		return active;
	}
};

#endif // COOK_ASSIGNMENT_H