#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
struct node
{
	int value;
	node* left = nullptr;
	node* right = nullptr;
};
void insert(node*& tree, int value);
void inOrder(node* tree);
void preOrder(node* tree);
void postOrder(node* tree);
int output = 0;
int main()
{
	int input;
	node* tree = nullptr;
	while (cin >> input)
	{
		insert(tree, input);
	}
	inOrder(tree);
	output = 0;
	cout << endl;
	preOrder(tree);
	output = 0;
	cout << endl;
	postOrder(tree);
}
void insert(node*& tree, int value)
{
	if (tree == nullptr)
	{
		node* tmp = new node;
		tmp->value = value;
		tmp->left = nullptr;
		tmp->right = nullptr;
		tree = tmp;
	}
	else if (tree->value < value)
	{
		insert(tree->right, value);
	}
	else
	{
		insert(tree->left, value);
	}
}

void inOrder(node* tree)
{
	if (tree != nullptr)
	{
		inOrder(tree->left);
		if (output != 0)
		{
			cout << ' ';
		}
		output++;
		cout << tree->value;
		inOrder(tree->right);
	}
}

void preOrder(node* tree)
{
	if (tree != nullptr)
	{
		if (output != 0)
		{
			cout << ' ';
		}
		output++;
		cout << tree->value;
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

void postOrder(node* tree)
{
	if (tree != nullptr)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		if (output != 0)
		{
			cout << ' ';
		}
		output++;
		cout << tree->value;
	}
}