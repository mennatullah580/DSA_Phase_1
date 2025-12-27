# pragma once
#include "Order.h"
#include <iostream>
using namespace std;
Order::Order(int id, char r_Type, int distance, double money, int size, int time)  // hena el constructor bta3 el order
{

	ID = (id > 0 && id < 1000) ? id : 0; // ID must be between 1 and 999 if not valid set to 0

	type = r_Type; // save order (N , V, G)

	status = WAIT; // lma el order yegi el status byeb2a waiting by default


	Distance = (distance > 0 ? distance : 0); // distance must be positive if not valid set to 0

	ordersize = (size > 0 ? size : 0); // ordersize must be positive if not valid set to 0

	totalMoney = (money > 0 ? money : 0); // money must be positive if not valid set to 0

	ArrTime = time; // save the arrival time
}

Order::~Order() // destructor
{
}

int Order::GetID() // ID getter
{
	return ID;
}


char Order::GetType() const
{
	return type; // type getter
}


void Order::SetDistance(int d) //distance setter
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const // distance getter
{
	return Distance;
}

void Order::setStatus(ORD_STATUS s) // status setter
{
	status = s; // set order status
}

ORD_STATUS Order::getStatus() const // status getter
{
	return status; // retrieve order status
}

void Order:: setMoney(double m) // money setter
{
	totalMoney = (m > 0 ? m : 0);
}

double Order::getMoney() const // money getter
{
	return totalMoney; // money getter
}

void Order::setOrderSize(int s) // size setter
{
	ordersize = (s > 0 ? s : 0);
}	

int Order::getOrderSize() const // size getter
{
	return ordersize; // retrieve order size
}

void Order::setArrTime(int at) // arrival time setter
{
	ArrTime = at; // set arrival time

}


int Order:: getArrTime() const // arrival time getter
{
	return ArrTime;
}


