#include <iostream>

template <class type> class Stack {

private:
	Stack* head;
	Stack* next;
	Stack* end;

	type* content; // The actual content of the element

public:
	Stack();
	void Push(type&); // Push element if paramter is lvalue
	void Push(type&&); // Push element if paramter is rvalue
	void Pop(); // Pops element from top of the stack
	void Traverse(); // Lists all elements in the stack
	type& getElementAt(int); // Returns element at index
};







/*-----------------------------------------------------
| The constructor initializes all pointers to nullptr |
-----------------------------------------------------*/
template <class type>
Stack<type>::Stack()
{
	head = nullptr;
	next = nullptr;
	end = nullptr;
	content = nullptr;
}







/*-----------------------------------------------------------------
| Receives an lvalue parameter and calls the Push_Helper function |
-----------------------------------------------------------------*/
template <class type>
void Stack<type>::Push(type& s)
{
	if (head == nullptr)
	{
		head = new Stack();
		head->content = &s;
		end = head;
	}
	else
	{
		Stack* temp = head;
		head = new Stack();
		head->next = temp;
		head->content = &s;
	}
}



/*-----------------------------------------------------------------
| Receives an rvalue parameter and calls the Push_Helper function |
-----------------------------------------------------------------*/
template <class type>
void Stack<type>::Push(type&& s)
{
	if (head == nullptr)
	{
		head = new Stack();
		head->content = new type;
		*head->content = s;
		end = head;
	}
	else
	{
		Stack* temp = head;
		head = new Stack();
		head->next = temp;
		head->content = new type;
		*head->content = s;
	}
}







/*----------------------------------------
| Removes the top element from the stack |
----------------------------------------*/
template <class type>
void Stack<type>::Pop()
{
	if (head != nullptr)
	{
		Stack* temp = head;
		head = head->next;
		delete temp;
	}
	else
	{
		std::cout << "There is nothing to pop" << std::endl;
	}
}







/*------------------------------------------------------------------------
| Lists all elements in starting from the top of the stack to the bottom |
------------------------------------------------------------------------*/

/*--- IMPORTANT ---*/
//
// This particular transverse function assumes the content is a primitive data type - int, float, double, string, etc.,
// and can print the content without issue. However, if the stack contains class objects or structs then the function
// will need to be modified in order to print out the desired attributes of the content.
//
template <class type>
void Stack<type>::Traverse()
{
	if (head != nullptr)
	{
		Stack* temp = head;
		while (temp != end)
		{
			std::cout << *temp->content << std::endl;
			temp = temp->next;
		}
		std::cout << *end->content << std::endl;
	}
	else
	{
		std::cout << "The stack is empty" << std::endl;
	}
}







/*------------------------------------------------------------------------------
| Returns element at the specified index where the top of the stack is index 0 |
------------------------------------------------------------------------------*/
template <class type>
type& Stack<type>::getElementAt(int n)
{
	try {
		if (head != nullptr)
		{
			Stack* temp = head;
			for (int i = 0; i < n; i++)
			{
				temp = temp->next;
			}
			return *temp->content;
		}
		else
		{
			std::string s = "The stack is empty";
			throw s;
		}
	}
	catch (std::string s)
	{
		std::cout << s << std::endl;
	}
	
}
