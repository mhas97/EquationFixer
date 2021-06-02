#pragma once

//Node class template to handle different types.
template <typename T>
class Node
{
private:
	T data;
	Node* next;

public:
	Node(T d)
	{
		data = d;
		next = nullptr;
	}

	T getData() { return data; }

	Node* getNext() { return next; }

	void setNext(Node* n) { next = n; }
};