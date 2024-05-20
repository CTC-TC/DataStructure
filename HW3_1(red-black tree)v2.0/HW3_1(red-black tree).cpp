#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;

struct cell
{
	int value = 0;
	string color = "red";
	cell* parent = nullptr;
	cell* left = nullptr;
	cell* right = nullptr;
};
cell* checkRoot(cell*& tree);
void insert(cell*& tree, cell* parent, int value);
cell* doubleRed(cell* tree);
void recursiveRotation(cell* tree);
void RR_rotation(cell*& tree, cell*& vertex);
void RL_rotation(cell*& tree, cell*& vertex);
void LL_rotation(cell*& tree, cell*& vertex);
void LR_rotation(cell*& tree, cell*& vertex);
void printFrontOrder(cell*& tree, string mode, int& rc, int& bc);
cell* integration = nullptr;
void tailSort(vector<int>& a)
{
	if (a.size() > 3)
	{
		int tmp;
		if (a[a.size()-1]< a[a.size() - 3])
		{
			tmp = a[a.size() - 1];
			a[a.size() - 1] = a[a.size() - 3];
			a[a.size() - 3] = tmp;
		}
		if (a[a.size() - 1] < a[a.size() - 2])
		{
			tmp = a[a.size() - 1];
			a[a.size() - 1] = a[a.size() - 2];
			a[a.size() - 2] = tmp;
		}
		if (a[a.size() - 2] < a[a.size() - 3])
		{
			tmp = a[a.size() - 2];
			a[a.size() - 2] = a[a.size() - 3];
			a[a.size() - 3] = tmp;
		}
	}
}
int main()
{

	int input;
	while (cin >> input)
	{
		insert(integration, nullptr, input);
	}
	vector<cell*> player;
	vector<int>redTeam, blackTeam, tmp;
	player.push_back(integration);
	while (!player.empty())
	{
		cell* current = player.front();
		player.erase(player.begin());
		if (current==nullptr)
		{
			break;
		}
		if (current->color == "red")
		{
			redTeam.push_back(current->value);
		}
		else
		{
			blackTeam.push_back(current->value);
		}
		if (current->left != nullptr)
		{
			player.push_back(current->left);
		}
		if (current->right != nullptr)
		{
			player.push_back(current->right);
		}
	}
	if (redTeam.size()>3&& blackTeam.size() > 3)
	{
	cout << "Red team: ";
	int rc = 0, bc = 0;
	printFrontOrder(integration, "red", rc, bc);
	tailSort(redTeam);
	cout << endl << "outfield: "<<redTeam[redTeam.size()-3]<<"," << redTeam[redTeam.size() - 2] << "," << redTeam[redTeam.size() - 1];
	cout << endl << "jump ball: " << redTeam.front();
	rc = 0;
	bc = 0;
	cout << endl<<"Black team: ";
	printFrontOrder(integration, "black", rc, bc);
	tailSort(blackTeam);
	cout << endl << "outfield: " << blackTeam[blackTeam.size() - 3] << "," << blackTeam[blackTeam.size() - 2] << "," << blackTeam[blackTeam.size() - 1];
	cout << endl << "jump ball: " << blackTeam.front();
	}
	else
	{
		cout << "No game";
	}
}

cell* checkRoot(cell*& tree)
{
	if (tree->parent != nullptr)
	{
		checkRoot(tree->parent);
	}
	else
	{
		tree->color = "black";
		return tree;
	}
}

void insert(cell*& tree, cell* parent, int value)
{
	if (tree == nullptr)
	{
		cell* tmp = new cell;
		tmp->value = value;
		tmp->parent = parent;
		tree = tmp;
		recursiveRotation(tmp);
		integration->color = "black";
	}
	else
	{
		if (tree->left != nullptr && tree->right != nullptr && tree->left->color == "red" && tree->right->color == "red")
		{
			tree->color = "red";
			tree->left->color = "black";
			tree->right->color = "black";
		}
		recursiveRotation(tree);
		integration->color = "black";
		if (value > tree->value)
		{
			insert(tree->right, tree, value);
		}
		else
		{
			insert(tree->left, tree, value);
		}
	}
}

cell* doubleRed(cell* tree)
{
	if (tree == nullptr)
	{
		return nullptr;
	}
	else
	{
		cell* tmp = new cell;
		tmp = doubleRed(tree->left);
		if (tmp != nullptr)
		{
			return tmp;
		}
		tmp = doubleRed(tree->right);
		if (tmp != nullptr)
		{
			return tmp;
		}
		if (tree->color == "red" && (tree->left != nullptr && tree->left->color == "red" || tree->right != nullptr && tree->right->color == "red"))
		{
			return tree->parent;
		}
		else
		{
			return nullptr;
		}
	}
}

void recursiveRotation(cell* tree)
{
	while (true)
	{
		cell* doubleRedPoint = new cell;
		doubleRedPoint = doubleRed(integration);
		if (doubleRedPoint != nullptr)
		{
			if (doubleRedPoint->right != nullptr && doubleRedPoint->right->color == "red")
			{
				if (doubleRedPoint->right->right != nullptr && doubleRedPoint->right->right->color == "red")
				{
					RR_rotation(integration, doubleRedPoint);
				}
				else
				{
					RL_rotation(integration, doubleRedPoint);
				}
			}
			else
			{
				if (doubleRedPoint->left->left != nullptr && doubleRedPoint->left->left->color == "red")
				{
					LL_rotation(integration, doubleRedPoint);
				}
				else
				{
					LR_rotation(integration, doubleRedPoint);
				}
			}
		}
		else
		{
			break;
		}
		doubleRedPoint = nullptr;
		delete doubleRedPoint;
	}
}

void RR_rotation(cell*& tree, cell*& vertex)
{
	if (tree != nullptr)
	{
		if (tree == vertex)
		{
			cell* tmp = new cell;
			tmp = tree->right;
			tree->right = tmp->left;
			tmp->left = tree;
			tmp->parent = tree->parent;
			tree->parent = tmp;
			tree = tmp;
			tree->color = "black";
			tree->left->color = "red";
			tree->right->color = "red";
		}
		else
		{
			RR_rotation(tree->left, vertex);
			RR_rotation(tree->right, vertex);
		}
	}
}

void RL_rotation(cell*& tree, cell*& vertex)
{
	if (tree != nullptr)
	{
		if (tree == vertex)
		{
			cell* tmp = new cell;
			tmp = tree->right->left;
			tree->right->left = tmp->right;
			tmp->right = tree->right;
			tree->right = tmp->left;
			tmp->left = tree;
			tmp->parent = tree->parent;
			tree->parent = tmp;
			tmp->right->parent = tmp;
			tree = tmp;
			tree->color = "black";
			tree->left->color = "red";
			tree->right->color = "red";
		}
		else
		{
			RL_rotation(tree->left, vertex);
			RL_rotation(tree->right, vertex);
		}
	}
}

void LL_rotation(cell*& tree, cell*& vertex)
{
	if (tree != nullptr)
	{
		if (tree == vertex)
		{
			cell* tmp = new cell;
			tmp = tree->left;
			tree->left = tmp->right;
			tmp->right = tree;
			tmp->parent = tree->parent;
			tree->parent = tmp;
			tree = tmp;
			tree->color = "black";
			tree->left->color = "red";
			tree->right->color = "red";
		}
		else
		{
			LL_rotation(tree->left, vertex);
			LL_rotation(tree->right, vertex);
		}
	}
}

void LR_rotation(cell*& tree, cell*& vertex)
{
	if (tree != nullptr)
	{
		if (tree == vertex)
		{
			cell* tmp = new cell;
			tmp = tree->left->right;
			tree->left->right = tree->left->right->left;
			tmp->left = tree->left;
			tree->left = tmp->right;
			tmp->right = tree;
			tmp->parent = tree->parent;
			tmp->left->parent = tmp;
			tree->parent = tmp;
			tree = tmp;
			tree->color = "black";
			tree->left->color = "red";
			tree->right->color = "red";
		}
		else
		{
			LR_rotation(tree->left, vertex);
			LR_rotation(tree->right, vertex);
		}
	}
}

void printFrontOrder(cell*& tree, string mode, int& rc, int& bc)
{
	if (tree != nullptr)
	{
		printFrontOrder(tree->left, mode, rc, bc);
		if (mode == "red")
		{
			if (tree->color == "red")
			{
				if (rc != 0)
				{
					cout << ',';
				}
				cout << tree->value;
				rc++;
			}
		}
		else
		{
			if (tree->color == "black")
			{
				if (bc != 0)
				{
					cout << ',';
				}
				cout << tree->value;
				bc++;
			}
		}
		printFrontOrder(tree->right, mode, rc, bc);
	}
}