# pragma once
#include "Order.h"
#include <iostream>
using namespace std;
Order::Order(int id, ORD_TYPE r_Type ,int distance, int money, int size, int time)
{
	ID = (id>0&&id<1000)?id:0;	//1<	ID<999
	type = r_Type;
	status = WAIT;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}
void Order:: setMoney(double m)
{
	totalMoney > 0;
}
double Order:: getMoney() const
{
	return totalMoney;
}
void Order:: setOrderSize(int s)
{
	odrdersize > 0;
}	
int Order:: getOrderSize() const
{
	return odrdersize;
}
void Order:: setTime(int at, int st, int ft)
{
	ArrTime = at;
	ServTime = st;
	FinishTime = ft;
}
int Order:: getTime(int& at, int& st, int& ft) const
{
	at = ArrTime;
	st = ServTime;
	ft = FinishTime;
}


