#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include <iostream>
using namespace std;

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )

	char type;		//order type: Normal, vegan, VIP

	ORD_STATUS status;	//waiting, in-service, done

	int Distance;	//The distance (in meters) between the order location and the resturant 

	int ordersize; //number of dishes in the order                

	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times

public:
	Order(int ID, char r_Type, int distance, double money, int size, int time); // constructor
	virtual ~Order(); // destroctor (virtual as class is inherited)

	int GetID(); // ID getter

	char GetType() const; // type getter

	void SetDistance(int d); // distance setter
	
	int GetDistance() const; // distance getter

	void setStatus(ORD_STATUS s); // status setting

	ORD_STATUS getStatus() const; // getting status

	void setOrderSize(int s); // set size

	int getOrderSize() const; // get size

	void setMoney(double m); //set money

	double getMoney() const; // get money

	void setArrTime(int at); // set arrival time

	int getArrTime() const; // get arrival time




};

#endif