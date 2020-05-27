#include <iostream>

template <class type>
class Stack {

private:
	Stack* head;
	Stack* next;
	Stack* end;

	type* content; // The actual content of the element
	int length; // number of elements in the stack

public:
	Stack();
	void Push(type&); // Push element if paramter is lvalue
	void Push(type&&); // Push element if paramter is rvalue
	void Pop(); // Pops element from top of the stack
	void Traverse(); // Lists all elements in the stack
	type& getElementAt(int); // Returns element at index
	int getLength(); // Returns the number of elements in the stack
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
	length = 0;
}







/*-----------------------------------------------------------------------
| Receives an lvalue parameter and adds element to the top of the stack |
-----------------------------------------------------------------------*/
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

	length++;
}



/*-----------------------------------------------------------------------
| Receives an rvalue parameter and adds element to the top of the stack |
-----------------------------------------------------------------------*/
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

	length++;
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
		length--;
	}
	else
	{
		std::cout << "There stack is already empty" << std::endl;
	}
}







/*-------------------------------------------------------------------------------
| Lists all elements in the stack starting from the top and going to the bottom |
-------------------------------------------------------------------------------*/

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
		std::cout << *temp->content << std::endl;
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
	Stack* temp = head;
	for (int i = 0; i < n; i++)
	{
		temp = temp->next;
	}
	return *temp->content;
}







/*---------------------------------------------
| Returns the number of elements in the stack |
---------------------------------------------*/
template <class type>
int Stack<type>::getLength()
{
	return length;
}
