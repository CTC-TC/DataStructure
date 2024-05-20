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
void insert(cell*& tree, cell* parent, int value);
cell* doubleRed(cell* tree);
void recursiveDeal();
void rotation(cell* &tree, cell* vertex);
void printFrontOrder(cell*& tree, string mode, int& rc, int& bc);
cell* integration = nullptr;
void tailSort(vector<int>& a)
{
	if (a.size() > 3)
	{
		int tmp;
		if (a[a.size() - 1] < a[a.size() - 3])
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
		if (current == nullptr)
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
	if (redTeam.size() > 3 && blackTeam.size() > 3)
	{
		cout << "Red team: ";
		int rc = 0, bc = 0;
		printFrontOrder(integration, "red", rc, bc);
		tailSort(redTeam);
		cout << endl << "outfield: " << redTeam[redTeam.size() - 3] << "," << redTeam[redTeam.size() - 2] << "," << redTeam[redTeam.size() - 1];
		cout << endl << "jump ball: " << redTeam.front();
		rc = 0;
		bc = 0;
		cout << endl << "Black team: ";
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

void insert(cell*& tree, cell* parent, int value)
{
	if (tree == nullptr)
	{
		cell* tmp = new cell;
		tmp->value = value;
		tmp->parent = parent;
		tree = tmp;
		recursiveDeal();
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
		recursiveDeal();
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

void recursiveDeal()
{
	while (true)
	{
		cell* doubleRedPoint = new cell;
		doubleRedPoint = doubleRed(integration);
		if (doubleRedPoint != nullptr)
		{
			rotation(integration, doubleRedPoint);
		}
		else
		{
			break;
		}
		doubleRedPoint = nullptr;
		delete doubleRedPoint;
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

void rotation(cell*& tree, cell* vertex)
{
	if (tree == vertex)
	{
		vector<cell*> list;
		list.push_back(vertex);
		cell* root = vertex->parent;
		for (int i = 0; i < 2; i++)
		{
			if (list[i]->left != nullptr && list[i]->left->color == "red")
			{
				list.push_back(list[i]->left);
			}
			else
			{
				list.push_back(list[i]->right);
			}
		}
		for (int k = 1; k < 3; k++)
		{
			cell* tmp = list[k];
			int j = k - 1;
			while (j >= 0 && tmp->value <= list[j]->value)
			{
				list[j + 1] = list[j];
				j--;
			}
			list[j + 1] = tmp;
		}
		if (list[1]->left != list[0])
		{
			list[0]->right = list[1]->left;
			list[0]->parent = list[1];
		}
		if (list[1]->right != list[2])
		{
			list[2]->left = list[1]->right;
			list[2]->parent = list[1];
		}
		list[0]->color = "red";
		list[1]->color = "black";
		list[2]->color = "red";
		list[1]->parent = root;
		list[1]->left = list[0];
		list[1]->right = list[2];
		tree = list[1];
	}
	else
	{
		if (vertex->value > tree->value)
		{
			rotation(tree->right, vertex);
		}
		else
		{
			rotation(tree->left, vertex);
		}
	}
}
