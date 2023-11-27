#ifndef _linkedList
#define _linkedList

#include "Node.h"

#include <stdexcept>
//This header defines a set of standard exceptions 
//that both the library and programs can use to report common errors.

using namespace std;

template <typename T> class linkedListADT
{
	Node<T>* head, * tail;
	int size;

public:

	linkedListADT() //constructor for linked list
	{
		size = 0,
		head = NULL,
		tail = NULL;
	}

	int getSize()
	{
		return this -> size; // https://www.youtube.com/watch?v=8MslX21jf1Y -- this ptr concept
	}

	bool isEmpty() //checks if the list is empty
	{
		if (getSize() == 0)
			return true;
		else
			return false;
	}

	T getItem(int index) //gets item through its index
	{
		if (index < 0 || index >= size) //checks if the index exceeds bounds
			throw out_of_range("Index out of bounds");
		Node<T>* node = head;
		for (int m = 0; m < index; m++)
			node = node -> next;
		return node -> item;
	}

	void addNode(T item) //creates a new node
	{
		Node<T>* node = new Node<T>(item);
		size++; //increments size

		if (head != nullptr) //checks if the list is empty
		{
			node -> previous = tail;
			tail -> next = node;
			tail = node;
			return;
		}
		else
		{
			//List's empty
			tail = node;
			head = node;
		}
	}

	void removeNode(T item)
	{
		Node<T>* node = head; //checks if the list is empty
		while (node != nullptr) //iterates through the list
		{
			if (node -> item == item) //checks if the item is found
			{
				if (node == head) //item found
				{
					head = node -> next; // item is the head
					if (head != NULL) // checks if the list is empty
						head -> previous = NULL;
					else
						tail = nullptr;
				}
				else if (node == tail)
				{
					tail = node -> previous; //item is the tail
					if (tail != nullptr)
						tail -> next = NULL;
					else
						head = NULL;
				}
				else
				{
					node -> previous -> next = node -> next;
					node -> next -> previous = node -> previous;
				}
				delete node;
				size--;
				break;
			}
			node = node -> next;
		}
	}

	~linkedListADT() //destructor for linked list
	{
		Node<T>* node = head; size = 0;
		while (node != nullptr) //iterates through the list and deletes all nodes
		{
			Node<T>* next = node -> next;
			delete node;
			node = next;
		}
		head = nullptr;
		tail = NULL;
	}

};
#endif

