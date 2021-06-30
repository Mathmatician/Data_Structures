// Author: Jerome Richards
// Binary Tree

/*-------------------------------------------------------------
| The class is a replication of the map class in C++ and is a |
| demonstration of employing my logic to recreate it.         |
-------------------------------------------------------------*/

#pragma once
#include <iostream>
#include <cstdlib>

template <class type, typename key_type>
class BinaryTree {
private:

	BinaryTree* head;
	BinaryTree* left;
	BinaryTree* right;
	BinaryTree* parent;

	type* content;
	key_type* key;

	int numOfElements;

	void Add_Helper(type&, key_type&);
	int BalanceFactor(BinaryTree&);
	int Height(BinaryTree&);
	void BalanceTree(BinaryTree&);
	void Rearrange(BinaryTree&, BinaryTree&);

public:
	BinaryTree();
	void Add(type&, key_type&);
	void Add(type&&, key_type&&);
};






/*-------------------------
| Binary Tree Constructor |
-------------------------*/
template <class type, typename key_type>
BinaryTree<type, typename key_type>::BinaryTree()
{
	head = nullptr;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	content = nullptr;
	key = nullptr;
	numOfElements = 0;
}







/*---------------------------------------------------------------------------------------
| First Add function that receives parameters passed by reference to add to binary tree |
---------------------------------------------------------------------------------------*/
template <class type, typename key_type>
void BinaryTree<type, key_type>::Add(type& b, key_type& k)
{
	type* B = new type;
	key_type* K = new key_type;
	*B = b;
	*K = k;
	Add_Helper(b, k);
}

/*----------------------------------------------------------------------------------------------------
| Second Add function that receives rhs (right hand side) values as parameters to add to binary tree |
----------------------------------------------------------------------------------------------------*/
template <class type, typename key_type>
void BinaryTree<type, key_type>::Add(type&& b, key_type&& k)
{
	type* B = new type;
	key_type* K = new key_type;
	*B = b;
	*K = k;
	Add_Helper(*B, *K);
}

/*---------------------------------------------------------------------------------------
| Helper function called by Add function. It performs the logic of adding the specified |
| node to the binary tree. The add function is what's publicly available to the user.   |
| This helper function is not directly accessible to the user.                          |
---------------------------------------------------------------------------------------*/
template <class type, typename key_type>
void BinaryTree<type, key_type>::Add_Helper(type& b, key_type& k)
{
	if (head == nullptr)
	{
		head = new BinaryTree();
		head->content = &b;
		head->key = &k;
		numOfElements++;
	}
	else
	{
		BinaryTree* temp = head;
		while (temp != nullptr)
		{
			if (k > *temp->key)
			{
				if (temp->right == nullptr)
				{
					temp->right = new BinaryTree();
					temp->right->content = &b;
					temp->right->key = &k;
					temp->right->parent = temp;
					numOfElements++;
					BalanceTree(*temp->right);
					break;
				}
				else
				{
					temp = temp->right;
				}
			}
			else if (k < *temp->key)
			{
				if (temp->left == nullptr)
				{
					temp->left = new BinaryTree();
					temp->left->content = &b;
					temp->left->key = &k;
					temp->left->parent = temp;
					numOfElements++;
					BalanceTree(*temp->left);
					break;
				}
				else
				{
					temp = temp->left;
				}
			}
			else
			{
				std::cout << "This value is already in the set" << std::endl;
				break;
			}
		}
	}
}






/*----------------------------------------------------------------
| Inserts a node (labeled b) at a specified node (labeled start) |
----------------------------------------------------------------*/
template <class type, typename key_type>
void BinaryTree<type, key_type>::Rearrange(BinaryTree& b, BinaryTree& start)
{
	BinaryTree* temp = &start;
	while (temp != nullptr)
	{
		if (*b.key > *temp->key)
		{
			if (temp->right == nullptr)
			{
				temp->right = &b;
				b.parent = temp;
				break;
			}
			else
			{
				temp = temp->right;
			}
		}
		else if (*b.key < *temp->key)
		{
			if (temp->left == nullptr)
			{
				temp->left = &b;
				b.parent = temp;
				break;
			}
			else
			{
				temp = temp->left;
			}
		}
	}
}








/*----------------------------------------------------------------------------
| Calculates the in height between a node's left and right leg. If the value |
| calculated is positive then the right leg is longer. If it's negative then |
| the left leg is longer.                                                    |
----------------------------------------------------------------------------*/
template <class type, typename key_type>
int BinaryTree<type, key_type>::BalanceFactor(BinaryTree& b)
{
	int left = 0;
	int right = 0;

	if (b.left != nullptr)
		left = 1 + Height(*b.left);
	if (b.right != nullptr)
		right = 1 + Height(*b.right);

	return (right - left);
}

/*-----------------------------------------------------
| Calculates the length of a node's left or right leg |
-----------------------------------------------------*/
template <class type, typename key_type>
int BinaryTree<type, key_type>::Height(BinaryTree& b)
{
	int left = 0;
	int right = 0;
	if (b.left != nullptr)
		left = 1 + Height(*b.left);
	if (b.right != nullptr)
		right = 1 + Height(*b.right);

	if (left > right)
		return left;
	if (left < right)
		return right;

	return left;
}






/*--------------------------------------------------------------------------
| Balances the Binary Search tree in order to preserve its searching logic |
--------------------------------------------------------------------------*/
template <class type, typename key_type>
void BinaryTree<type, key_type>::BalanceTree(BinaryTree& b)
{
	BinaryTree* node = &b;
	BinaryTree* start = node;
	int balNum = BalanceFactor(*node);
	while (abs(balNum) <= 1 && node != head)
	{
		node = node->parent;
		balNum = BalanceFactor(*node);
	}


	if (balNum > 1) // The right side is larger
	{
		while (start->parent->parent != node)
			start = start->parent;

		BinaryTree* tempNodes[3];
		tempNodes[0] = start;
		tempNodes[1] = start->parent;
		tempNodes[2] = start->parent->parent;

		// Bubble sort
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (*tempNodes[j]->key > *tempNodes[j + 1]->key)
				{
					BinaryTree* tmp = tempNodes[j + 1];
					tempNodes[j + 1] = tempNodes[j];
					tempNodes[j] = tmp;
				}
			}
		}

		BinaryTree* extraNode = nullptr;
		if (tempNodes[1]->left != tempNodes[0] && tempNodes[1]->left != tempNodes[2] && tempNodes[1]->left != nullptr)
		{
			extraNode = tempNodes[1]->left;
			tempNodes[1]->left = nullptr;
		}
		else if (tempNodes[1]->right != tempNodes[0] && tempNodes[1]->right != tempNodes[2] && tempNodes[1]->left != nullptr)
		{
			extraNode = tempNodes[1]->right;
			tempNodes[1]->right = nullptr;
		}

		if (node->right->right == tempNodes[0] || node->right->right == tempNodes[1] || node->right->right == tempNodes[2])
		{
			node->right->right = nullptr;
		}
		if (node->right->left == tempNodes[0] || node->right->left == tempNodes[1] || node->right->left == tempNodes[2])
		{
			node->right->left = nullptr;
		}
		node->right = nullptr;

		if (node != head)
		{
			node = node->parent;
			if (node->left == tempNodes[0] || node->left == tempNodes[1] || node->left == tempNodes[2])
			{
				node->left = nullptr;
			}
			else if (node->right == tempNodes[0] || node->right == tempNodes[1] || node->right == tempNodes[2])
			{
				node->right = nullptr;
			}
		}
		else
		{
			head = tempNodes[1];
		}

		tempNodes[0]->parent = nullptr;
		tempNodes[1]->parent = nullptr;
		tempNodes[2]->parent = nullptr;

		if (tempNodes[1] == head)
		{
			Rearrange(*tempNodes[0], *tempNodes[1]);
			Rearrange(*tempNodes[2], *tempNodes[1]);

			if (extraNode)
				Rearrange(*extraNode, *tempNodes[1]);
		}
		else
		{
			Rearrange(*tempNodes[1], *node);
			Rearrange(*tempNodes[0], *node);
			Rearrange(*tempNodes[2], *node);

			if (extraNode)
				Rearrange(*extraNode, *node);
		}
	}
	else if (balNum < -1) // The left side is larger
	{
		while (start->parent->parent != node)
			start = start->parent;

		BinaryTree* tempNodes[3];
		tempNodes[0] = start;
		tempNodes[1] = start->parent;
		tempNodes[2] = start->parent->parent;

		// Bubble sort
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (*tempNodes[j]->key > *tempNodes[j + 1]->key)
				{
					BinaryTree* tmp = tempNodes[j + 1];
					tempNodes[j + 1] = tempNodes[j];
					tempNodes[j] = tmp;
				}
			}
		}

		BinaryTree* extraNode = nullptr;
		if (tempNodes[1]->left != tempNodes[0] && tempNodes[1]->left != tempNodes[2] && tempNodes[1]->left != nullptr)
		{
			extraNode = tempNodes[1]->left;
			tempNodes[1]->left = nullptr;
		}
		else if (tempNodes[1]->right != tempNodes[0] && tempNodes[1]->right != tempNodes[2] && tempNodes[1]->left != nullptr)
		{
			extraNode = tempNodes[1]->right;
			tempNodes[1]->right = nullptr;
		}

		if (node->left->right == tempNodes[0] || node->left->right == tempNodes[1] || node->left->right == tempNodes[2])
		{
			node->left->right = nullptr;
		}
		if (node->left->left == tempNodes[0] || node->left->left == tempNodes[1] || node->left->left == tempNodes[2])
		{
			node->left->left = nullptr;
		}
		node->left = nullptr;

		if (node != head)
		{
			node = node->parent;
			if (node->left == tempNodes[0] || node->left == tempNodes[1] || node->left == tempNodes[2])
			{
				node->left = nullptr;
			}
			else if (node->right == tempNodes[0] || node->right == tempNodes[1] || node->right == tempNodes[2])
			{
				node->right = nullptr;
			}
		}
		else
		{
			head = tempNodes[1];
		}

		tempNodes[0]->parent = nullptr;
		tempNodes[1]->parent = nullptr;
		tempNodes[2]->parent = nullptr;

		if (tempNodes[1] == head)
		{
			Rearrange(*tempNodes[0], *tempNodes[1]);
			Rearrange(*tempNodes[2], *tempNodes[1]);

			if (extraNode)
				Rearrange(*extraNode, *tempNodes[1]);
		}
		else
		{
			Rearrange(*tempNodes[1], *node);
			Rearrange(*tempNodes[0], *node);
			Rearrange(*tempNodes[2], *node);

			if (extraNode)
				Rearrange(*extraNode, *node);
		}
	}
}