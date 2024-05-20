#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;
struct node
{
	int value = 0;
	char color = 'r';
	node* left = nullptr;
	node* right = nullptr;
	node* parent = nullptr;
};
node* grand_parent(node*& tree);
node* uncle(node*& tree);
void case1(node*& tree);
void case2(node*& tree);
void case3(node*& tree);
void case4(node*& tree);
void case5(node*& tree);
void rotate_left(node*& tree);
void rotate_right(node*& tree);
void insert(int value, node*& tree, node* parent);
int main()
{
	int input;
	node* tree = nullptr;
	while (cin >> input)
	{
		insert(input, tree, nullptr);
	}
}
node* grand_parent(node*& tree)
{
	if ((tree != nullptr) && (tree->parent != nullptr))
	{
		return tree->parent->parent;
	}
	else
	{
		return nullptr;
	}
}

node* uncle(node*& tree)
{
	node* greandParent;
	greandParent = grand_parent(tree);
	if (greandParent == nullptr)
	{
		return nullptr;
	}
	if (tree->parent == greandParent->left)
	{
		return greandParent->right;
	}
	else
	{
		return greandParent->left;
	}
}

void case1(node*& tree)
{
	if (tree->parent == nullptr)
	{
		tree->color = 'b';
	}
	else
	{
		case2(tree);
	}
}

void case2(node*& tree)
{
	if (tree->parent->color != 'b')
	{
		case3(tree);
	}
}

void case3(node*& tree)
{
	node* u = uncle(tree);
	node* g = grand_parent(tree);
	if (u != nullptr && u->color == 'r')
	{
		tree->parent->color = 'b';
		u->color = 'b';
		g->color = 'r';
		case1(g);
	}
	else
	{
		case4(tree);
	}

}

void case4(node*& tree)
{
	node* g = grand_parent(tree);
	if (tree == tree->parent->right && tree->parent == g->left)
	{
		rotate_left(tree);
		tree = tree->left;
	}
	else if (tree == tree->parent->left && tree->parent == g->right)
	{
		rotate_right(tree);
		tree = tree->right;
	}
	case5(tree);
}

void case5(node*& tree)
{
	node* g = grand_parent(tree);
	tree->parent->color = 'b';
	g->color = 'r';
	if (tree == tree->parent->left && tree->parent == g->left)
	{
		rotate_right(tree->parent);
	}
	else if (tree == tree->parent->right && tree->parent == g->right)
	{
		rotate_left(tree->parent);
	}
}

void rotate_left(node*& tree)
{
	node* g = grand_parent(tree);
	bool sideRight = false;
	if (tree->parent == g->right)
	{
		sideRight = true;
	}
	tree->parent->right = tree->left;
	tree->left = tree->parent;
	if (sideRight)
	{
		g->right = tree;
	}
	else
	{
		g->left = tree;
	}
	tree->parent->parent = tree;
	tree->parent = g;
}

void rotate_right(node*& tree)
{
	node* g = grand_parent(tree);
	bool sideRight = false;
	if (tree->parent == g->right)
	{
		sideRight = true;
	}
	tree->parent->left = tree->right;
	tree->right = tree->parent;
	if (sideRight)
	{
		g->right = tree;
	}
	else
	{
		g->left = tree;
	}
	tree->parent->parent = tree;
	tree->parent = g;
}

void insert(int value, node*& tree, node* parent)
{
	if (tree == nullptr)
	{
		node* tmp = new node;
		tmp->value = value;
		tmp->parent = parent;
		tree = tmp;
		case1(tree);
	}
	else
	{
		if (value < tree->value)
		{
			insert(value, tree->left, tree);
		}
		else
		{
			insert(value, tree->right, tree);
		}
	}
}
