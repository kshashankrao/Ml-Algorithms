#pragma once
#include <stack>
#include <string>
#include <iostream>

template<typename T>
class LinkedList
{

public:
	struct Node
	{
		Node* next = NULL;
		T data;
	};

	void insert(T val);
	void del(T val);
	void print();

private:
	Node* head = new Node;



	
	
};
