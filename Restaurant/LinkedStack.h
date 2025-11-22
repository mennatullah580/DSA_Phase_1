
/** ADT stack: Linked list-based implementation.
 @file LinkedStack.h */

#ifndef LINKED_STACK_
#define LINKED_STACK_
#include "Generic_DS/Node.h"
#include "StackADT.h"
#include <memory> // For std::unique_ptr (optional, for modern C++ memory management)

template<typename T>
class LinkedStack : public StackADT<T>
{
private:
    /** A node structure for the linked list. */
    struct Node
    {
        T item; // Data portion
        Node* next; // Pointer to the next node

        // Constructor for convenience
        Node(const T& anItem, Node* nextNodePtr = nullptr) :
            item(anItem), next(nextNodePtr)
        {
        }
    }; // end Node

    Node* topPtr; // Pointer to the top node in the stack (the head of the list)

public:
    /** Default Constructor: Initializes an empty stack. */
    LinkedStack() : topPtr(nullptr) {}

    /** Copy Constructor (optional, but good practice): */
    // LinkedStack(const LinkedStack<T>& otherStack);

    /** Destructor: Frees all memory allocated for the nodes. */
    virtual ~LinkedStack()
    {
        // Call the pop operation repeatedly until the stack is empty.
        T temp;
        while (!isEmpty()) {
            pop(temp);
        }
    }

    // --- StackADT Methods (Public Interface) ---

    /** @see StackADT::isEmpty */
    virtual bool isEmpty() const override
    {
        return topPtr == nullptr;
    }

    /** @see StackADT::push
     * Pushes by adding a new node to the front of the linked list.
     */
    virtual bool push(const T& newEntry) override
    {
        // Create a new node, making it point to the current top node.
        Node* newNodePtr = new Node(newEntry, topPtr);

        // Make the new node the new top of the stack.
        topPtr = newNodePtr;

        return true; // Push operation on a linked stack typically always succeeds (unless out of memory)
    }

    /** @see StackADT::pop
     * Pops by removing the top node and moving the top pointer.
     */
    virtual bool pop(T& TopEntry) override
    {
        if (isEmpty())
            return false; // Cannot pop an empty stack

        // 1. Copy the data from the top node.
        TopEntry = topPtr->item;

        // 2. Save pointer to the node to be deleted.
        Node* nodeToDeletePtr = topPtr;

        // 3. Move the top pointer to the next node.
        topPtr = topPtr->next;

        // 4. Delete the old top node.
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr; // Good practice

        return true;
    }

    /** @see StackADT::peek */
    virtual bool peek(T& TopEntry) const override
    {
        if (isEmpty())
            return false;

        TopEntry = topPtr->item;
        return true;
    }
}; // end LinkedStack

#endif
