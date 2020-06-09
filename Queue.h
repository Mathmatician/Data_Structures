// Author: Jerome Richards
// Queue

/*---------------------------------------------------------------
| The class is a replication of the queue class in C++ and is a |
| demonstration of employing my logic to recreate it.           |
---------------------------------------------------------------*/

#include <iostream>

template <class type>
class Queue {
private:
	Queue* head;
	Queue* next;
	Queue* end;

	type* content; // The actual content of the element
	int length;

public:
	Queue();
	void Push(type&); // Push element if paramter is lvalue
	void Push(type&&); // Push element if paramter is rvalue
	void Pop(); // Pops element from front of queue
	void Traverse(); // Lists all elements in the stack
	type& getElementAt(int); // Returns element at index
	int getLength(); // Returns the number of elements in queue
};







/*-----------------------------------------------------
| The constructor initializes all pointers to nullptr |
-----------------------------------------------------*/
template <class type>
Queue<type>::Queue()
{
	head = nullptr;
	next = nullptr;
	end = nullptr;
	content = nullptr;
	length = 0;
}







/*------------------------------------------------------------------------
| Receives an lvalue parameter and adds element to the back of the queue |
------------------------------------------------------------------------*/
template <class type>
void Queue<type>::Push(type& q)
{
	if (head == nullptr)
	{
		head = new Queue();
		head->content = &q;
		end = head;
	}
	else
	{
		end->next = new Queue();
		end = end->next;
		end->content = &q;
	}

	length++;
}

/*------------------------------------------------------------------------
| Receives an rvalue parameter and adds element to the back of the queue |
------------------------------------------------------------------------*/
template <class type>
void Queue<type>::Push(type&& q)
{
	if (head == nullptr)
	{
		head = new Queue();
		head->content = new type;
		*head->content = q;
		end = head;
	}
	else
	{
		end->next = new Queue();
		end = end->next;
		end->content = new type;
		*end->content = q;
	}

	length++;
}







/*-------------------------------------------
| Removes the element in front of the queue |
-------------------------------------------*/
template <class type>
void Queue<type>::Pop()
{
	if (head != nullptr)
	{
		Queue* temp = head;
		head = head->next;
		delete temp;
		length--;
	}
	else
	{
		std::cout << "The Queue is already empty" << std::endl;
	}
}







/*-------------------------------------------------------------------------------
| Lists all elements in the queue starting from the front and going to the back |
-------------------------------------------------------------------------------*/

/*--- IMPORTANT ---*/
//
// This particular transverse function assumes the content is a primitive data type - int, float, double, string, etc.,
// and can print the content without issue. However, if the stack contains class objects or structs then the function
// will need to be modified in order to print out the desired attributes of the content.
//
template<class type>
void Queue<type>::Traverse()
{
	if (head != nullptr)
	{
		Queue* temp = head;
		while (temp != end)
		{
			std::cout << *temp->content << std::endl;
			temp = temp->next;
		}
		std::cout << *temp->content << std::endl;
	}
	else
	{
		std::cout << "The Queue is empty" << std::endl;
	}
}







/*--------------------------------------------------------------------------------
| Returns element at the specified index where the front of the queue is index 0 |
--------------------------------------------------------------------------------*/
template <class type>
type& Queue<type>::getElementAt(int n)
{
	Queue* temp = head;
	for (int i = 0; i < n; i++)
	{
		temp = temp->next;
	}
	return *temp->content;
}







/*---------------------------------------------
| Returns the number of elements in the queue |
---------------------------------------------*/
template <class type>
int Queue<type>::getLength()
{
	return length;
}
