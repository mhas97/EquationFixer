#pragma once
#include "Node.h"
#include <cstddef>

//Linked List class template to handle different types.
template <typename T>
class LinkedList
{
private:
	Node<T>* top = nullptr;
	int capacity;
	int numNodes = 0;

public:
	//If the list is constructed without arguments, the capacity is not limited, -1 flag indicates this.
	LinkedList() { capacity = -1; }

	LinkedList(int c)
	{
		capacity = c;
		if (c < 0) { capacity = -capacity; }
	}

	//If the stack is not full, creates a node
	//and adds it to the top of the stack.
	void push(T d)
	{
		if (!isFull())
		{
			Node<T>* temp = new Node<T>(d);
			temp->setNext(top);
			top = temp;
			++numNodes;
		}
	}

	//Returns the data from the node at the 
	//top of the stack before deleting the node.
	//If the stack is empty instead returns null. 
	T pop()
	{
		if (!isEmpty())
		{
			T data = top->getData();
			Node<T>* temp = top;
			top = top->getNext();
			delete temp;
			--numNodes;
			return data;
		}
		return NULL;
	}

	//Returns the data from the node at the
	//top of the stack. If the stack is empty
	//instead returns null.
	T peek()
	{
		if (!isEmpty())
		{
			return top->getData();
		}
		return NULL;
	}

	bool isFull()
	{
		if (capacity == -1)
		{
			return false;
		}
		return (numNodes == capacity);
	}

	bool isEmpty()
	{
		return (numNodes == 0);
	}
};