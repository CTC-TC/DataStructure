#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

struct node
{
	int value;
	int balanceFactor;
	node* left = nullptr;
	node* right = nullptr;
};
string procees;
int output = 0;
void insert(node*& tree, int value);
void balanceFactorCalculate(node*& tree);
int treeHight(node* tree);
node* criticalNodeFind(node* tree);
void numberInsert(node*& tree, int value);
void RRrotation(node*& tree, node* criticalNode);
void RLrotation(node*& tree, node* criticalNode);
void LRrotation(node*& tree, node* criticalNode);
void LLrotation(node*& tree, node* criticalNode);
void deletion(node*& tree, int value);
void numberDelete(node*& tree, int value);
node* findTheLargestNode(node*& tree);
void inOrder(node* tree);

int main()
{
	node* tree = nullptr;
	string inputLine;
	string input;
	getline(cin, inputLine);
	inputLine += ',';
	while (!inputLine.empty())
	{
		input = inputLine.substr(0, inputLine.find_first_of(','));
		inputLine.erase(0, inputLine.find_first_of(',') + 1);
		numberInsert(tree, stoi(input));
	}
	while (cin >> inputLine)
	{
		string buffer;
		cin >> buffer;
		if (inputLine[0] == 'I')
		{
			numberInsert(tree, stoi(buffer));
		}
		else if (inputLine[0] == 'D')
		{
			numberDelete(tree, stoi(buffer));
		}
	}
	inOrder(tree);
	int n = 0;
	for (int i = 0; i < procees.length(); i++)
	{
		if (procees[i] == ' ')
		{
			n++;
		}
	}
	cout << endl << n << endl;
	while (!procees.empty())
	{
		cout << procees.substr(0, procees.find_first_of(' '));
		procees.erase(0, procees.find_first_of(' ') + 1);
		if (!procees.empty())
		{
			cout << ",";
		}
	}
}

void numberInsert(node*& tree, int input)
{
	insert(tree, input);
	while (true)
	{
		balanceFactorCalculate(tree);
		node* criticalNode = criticalNodeFind(tree);
		if (criticalNode != nullptr)
		{
			if (criticalNode->balanceFactor > 0)
			{
				if (criticalNode->left->balanceFactor > 0)
				{
					procees += "LL ";
					LLrotation(tree, criticalNode);
				}
				else
				{
					procees += "LR ";
					LRrotation(tree, criticalNode);
				}
			}
			else
			{
				if (criticalNode->right->balanceFactor > 0)
				{
					procees += "RL ";
					RLrotation(tree, criticalNode);
				}
				else
				{
					procees += "RR ";
					RRrotation(tree, criticalNode);
				}
			}
		}
		else {
			break;
		}
	}
	balanceFactorCalculate(tree);
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
	else if (tree->value <= value)
	{
		insert(tree->right, value);
	}
	else
	{
		insert(tree->left, value);
	}
}

void balanceFactorCalculate(node*& tree)
{
	if (tree != nullptr)
	{
		tree->balanceFactor = treeHight(tree->left) - treeHight(tree->right);
		balanceFactorCalculate(tree->left);
		balanceFactorCalculate(tree->right);
	}
}

int treeHight(node* tree)
{
	if (tree == nullptr)
	{
		return 0;
	}
	else
	{
		int leftHight = treeHight(tree->left);
		int rightHight = treeHight(tree->right);
		return max(leftHight, rightHight) + 1;
	}
}

node* criticalNodeFind(node* tree)
{
	if (tree != nullptr)
	{
		node* tmp = new node;
		tmp = criticalNodeFind(tree->left);
		if (tmp != nullptr)
		{
			return tmp;
		}
		tmp = criticalNodeFind(tree->right);
		if (tmp != nullptr)
		{
			return tmp;
		}
		if ((tree->balanceFactor > 1 || tree->balanceFactor < -1))
		{
			return tree;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

void RRrotation(node*& tree, node* criticalNode)
{
	if (tree != nullptr)
	{
		if (tree == criticalNode)
		{
			node* tmp = new node;
			tmp = criticalNode->right;
			criticalNode->right = tmp->left;
			tmp->left = criticalNode;
			tree = tmp;
		}
		else
		{
			RRrotation(tree->left, criticalNode);
			RRrotation(tree->right, criticalNode);
		}
	}
}

void RLrotation(node*& tree, node* criticalNode)
{
	if (tree != nullptr)
	{
		if (tree == criticalNode)
		{
			node* tmp = new node;
			tmp = criticalNode->right->left;
			criticalNode->right->left = criticalNode->right->left->right;
			tmp->right = criticalNode->right;
			criticalNode->right = tmp->left;
			tmp->left = criticalNode;
			tree = tmp;
		}
		else
		{
			RLrotation(tree->left, criticalNode);
			RLrotation(tree->right, criticalNode);
		}
	}
}

void LRrotation(node*& tree, node* criticalNode)
{
	if (tree != nullptr)
	{
		if (tree == criticalNode)
		{
			node* tmp = new node;
			tmp = criticalNode->left->right;
			criticalNode->left->right = criticalNode->left->right->left;
			tmp->left = criticalNode->left;
			criticalNode->left = tmp->right;
			tmp->right = criticalNode;
			tree = tmp;
		}
		else
		{
			LRrotation(tree->left, criticalNode);
			LRrotation(tree->right, criticalNode);
		}
	}
}

void LLrotation(node*& tree, node* criticalNode)
{
	if (tree != nullptr)
	{
		if (tree == criticalNode)
		{
			node* tmp = new node;
			tmp = criticalNode->left;
			criticalNode->left = tmp->right;
			tmp->right = criticalNode;
			tree = tmp;
		}
		else
		{
			LLrotation(tree->left, criticalNode);
			LLrotation(tree->right, criticalNode);
		}
	}
}

void deletion(node*& tree, int value)
{
	if (value < tree->value)
	{
		deletion(tree->left, value);
	}
	else if (value > tree->value)
	{
		deletion(tree->right, value);
	}
	else if (tree->left != nullptr && tree->right != nullptr)
	{
		node* tmp = new node;
		tmp = findTheLargestNode(tree->left);
		tree->value = tmp->value;
		deletion(tree->left, tmp->value);
	}
	else
	{
		if (tree->left == nullptr && tree->right == nullptr)
		{
			tree = nullptr;
		}
		else if (tree->left != nullptr)
		{
			tree = tree->left;
		}
		else
		{
			tree = tree->right;
		}
	}
}

void numberDelete(node*& tree, int value)
{
	node* exit = new node;
	deletion(tree, value);
	while (true)
	{
		balanceFactorCalculate(tree);
		node* criticalNode = criticalNodeFind(tree);
		if (criticalNode != nullptr)
		{
			if (criticalNode->balanceFactor > 0)
			{
				if (criticalNode->left->balanceFactor == 0)
				{
					procees += "R0 ";
					LLrotation(tree, criticalNode);
				}
				else if (criticalNode->left->balanceFactor == 1)
				{
					procees += "R1 ";
					LLrotation(tree, criticalNode);
				}
				else if (criticalNode->left->balanceFactor == -1)
				{
					procees += "R-1 ";
					LRrotation(tree, criticalNode);
				}
			}
			else
			{
				if (criticalNode->right->balanceFactor == 0)
				{
					procees += "R0 ";
					RRrotation(tree, criticalNode);
				}
				else if (criticalNode->right->balanceFactor == 1)
				{
					procees += "R1 ";
					RLrotation(tree, criticalNode);
				}
				else if (criticalNode->right->balanceFactor == -1)
				{
					procees += "R-1 ";
					RRrotation(tree, criticalNode);
				}
			}
		}
		else
		{
			break;
		}
	}
	balanceFactorCalculate(tree);
}

node* findTheLargestNode(node*& tree)
{
	if (tree->right != nullptr)
	{
		findTheLargestNode(tree->right);
	}
	else
	{
		return tree;
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
