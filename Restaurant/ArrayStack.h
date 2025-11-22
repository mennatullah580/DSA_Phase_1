/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_
#include "StackADT.h"
#include "Generic_DS/Node.h"

template<typename T>
class ArrayStack : public StackADT<T>
{
private:
	T* items;		// Array of stack items
	int top;                   // Index to top of stack
	const int STACK_SIZE;

public:

	ArrayStack(int MaxSize) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;	// law el top = -1 yb2a el stack m3ndosh elements , else msh fady
	}  // end isEmpty 

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;	//Stack is FULL

		top++; // move top up
		items[top] = newEntry; // store value   
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false; // maynfa3sh n3ml pop lw el stack fady

		TopEntry = items[top];		 // copy top value
		top--; 			 // move top down
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];		 //bn3ml copy lel top elements lel top entry mn 8er ma neghayar 7aga
		return true;
	}  // end peek

}; // end ArrayStack

#endif

