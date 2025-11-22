#include <iostream>
#include "Generic_DS/Node.h"
using namespace std;

class Circularqueue {
    int* arr;
    int size;
    int front;
    int rear;
    int count;

public:
    Circularqueue(int s) {
        size = s;
        arr = new int[size];
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isFull() {
        return count == size;
    }

    bool isEmpty() {
        return count == 0;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "queue is full" << value << endl;
            return;
        }
        rear = (rear + 1) % size;
        arr[rear] = value;
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "queue is empty";
            return;
        }
        front = (front + 1) % size;
        count--;
    }

    void display() {
        if (isEmpty()) {
            cout << "queue is empty";
            return;
        }

        cout << "queue elements: ";
        int i = front;
        for (int j = 0; j < count; j++) {
            cout << arr[i] << " ";
            i = (i + 1) % size;
        }
        cout << endl;
    }
    ~Circularqueue() {
        delete[] arr;
    }
};
