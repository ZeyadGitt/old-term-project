#ifndef _Node
#define _Node

template <typename T> class Node
{
public:

	T item;
	Node<T>* next, * previous;

	Node() //constructor of node
	{
		this -> item = NULL; // https://www.youtube.com/watch?v=8MslX21jf1Y -- this ptr concept
		this -> next = NULL;
		this -> previous = nullptr;
	}

	Node(T item)
	{
		this -> item = item;
		this -> next = nullptr;
		this -> previous = NULL;
		//The ‘this’ pointer is passed as a hidden argument 
		//to all nonstatic member function calls and is available 
		//as a local variable within the body of all nonstatic functions.
	}

	~Node() //destructor of node
	{
	}
};
#endif