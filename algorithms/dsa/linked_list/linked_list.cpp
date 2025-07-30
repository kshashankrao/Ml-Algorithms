#include "linked_list.h"

template class LinkedList<int>;

template <typename T>
void LinkedList<T>::insert(T val)
{
	Node* new_node = new Node;
	new_node->data = val;
	if (head->next == NULL)
	{
		head->next = new_node;
	}
	else
	{
		Node* tmp = head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_node;
		
	}
}
template<typename T>
void LinkedList<T>::del(T val)
{
	if (head->data == val)
	{
		head = head->next;
	}
	else
	{
		Node* tmp = head;
		Node* prev = NULL;
		while (tmp->data != val)
		{
			prev = tmp;
			tmp = tmp->next;
			
		}
		prev->next = tmp;
	}
}

template<typename T>
void LinkedList<T>::print()
{
	Node* tmp = head->next; // Start from the first actual node
	while (tmp != NULL)
	{
		std::cout << tmp->data << " ";
		tmp = tmp->next;
	}
	std::cout << std::endl;
}