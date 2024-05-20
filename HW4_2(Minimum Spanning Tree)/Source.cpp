#include<iostream>
#include<vector>
#include<string>
using namespace std;
int findObject(vector<vector<string>> table, string input)
{
	for (int i = 0; i < table.size(); i++)
	{
		for (int insidePoint = 0; insidePoint < table[i].size(); insidePoint++)
		{
			if (table[i][insidePoint] == input)
			{
				return i;
			}
		}
	}
	return -1;
}

int main()
{
	vector<int>list_weight;
	vector<vector<string>>table_vertix, F;
	int num_vertix, num_edge, weight;
	string vertixA, vertixB;
	cin >> num_vertix >> num_edge;
	for (int i = 0; i < num_edge; i++)
	{
		cin >> vertixA >> vertixB >> weight;
		table_vertix.push_back({ vertixA ,vertixB });
		list_weight.push_back(weight);
		if (vertixA > vertixB)
		{
			swap(vertixA, vertixB);
		}
		if (findObject(F, vertixA) == -1)
		{
			F.push_back({ vertixA });
		}
		if (findObject(F, vertixB) == -1)
		{
			F.push_back({ vertixB });
		}
	}
	for (int core = 0; core < list_weight.size() - 1; core++)
	{
		for (int point = 0; point < list_weight.size() - 1 - core; point++)
		{
			if (list_weight[point] > list_weight[point + 1])
			{
				swap(list_weight[point], list_weight[point + 1]);
				swap(table_vertix[point], table_vertix[point + 1]);
			}
			if (list_weight[point] == list_weight[point + 1] && table_vertix[point] > table_vertix[point + 1])
			{
				swap(table_vertix[point], table_vertix[point + 1]);
			}
		}
	}
	int total = 0;
	vector<string>print;
	while (F.size() != 1)
	{
		int seat1 = findObject(F, table_vertix[0][0]);
		int seat2 = findObject(F, table_vertix[0][1]);
		if (seat1 != seat2)
		{
			total += list_weight[0];
			print.push_back(table_vertix[0][0] + " " + table_vertix[0][1] + " " + to_string(list_weight[0]));
			for (int count = 0; count < F[seat2].size(); count++)
			{
				F[seat1].push_back(F[seat2][count]);
			}
			F.erase(F.begin() + seat2);
		}
		table_vertix.erase(table_vertix.begin());
		list_weight.erase(list_weight.begin());
	}
	cout << total << endl;
	for (int i = 0; i < print.size(); i++)
	{
		cout << print[i];
		if (i != print.size() - 1)
		{
			cout << endl;
		}
	}
}