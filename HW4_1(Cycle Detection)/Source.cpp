#include<iostream>
#include<stdlib.h>
#include<vector>
using namespace std;
int findvertix(vector<vector<int>>table, int value, int seat)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i][0] == value && i != seat)
		{
			return i;
		}
	}
	return -1;
}
bool findIndeg(vector<vector<int>>table, int value)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i][1] == value)
		{
			return i;
		}
	}
	return false;
}
int main()
{
	int count, vertix, target;
	cin >> count;
	vector<vector<int>>table;
	vector<int> list;
	for (int i = 0; i < count; i++)
	{
		cin >> vertix >> target;
		list.push_back(vertix);
		list.push_back(target);
		table.push_back(list);
		list.clear();
	}
	int internalVertix;
	for (int i = 0; i < table.size(); i++)
	{
		internalVertix = table[i][1];
		while (true)
		{
			if (findIndeg(table, internalVertix))
			{
				if (findvertix(table, internalVertix, i) != -1)
				{
					internalVertix = table[findvertix(table, internalVertix, i)][1];
					if (table[i][0] == internalVertix)
					{
						cout << "Cycle";
						return 0;
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	cout << "No Cycle";
}