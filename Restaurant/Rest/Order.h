#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include <iostream>
using namespace std;
enum ORD_TYPE	//types of orders
{
	NRMo,	
	Vegano,	
	VIPo,	
	
};
class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	int ordersize; //number of dishes in the order                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times

public:
	Order(int ID, ORD_TYPE r_Type, int distance, int money, int size, int time);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	void setOrderSize(int s);
	int getOrderSize() const;
	void setMoney(double m);
	double getMoney() const;
	void setArrTime(int at);
	int getArrTime() const;




};

#endif