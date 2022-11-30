#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>

using namespace std;

int main()
{
	vector< vector<vector<string>>*> centerSystem;
	vector< vector<string> >customer;
	vector<string>inputBuffer;
	string name, arrivalTime, handleTime;
	int deskSize = 0;
	cin >> deskSize;
	for (int i = 0; i < deskSize; i++)
	{
		vector<vector<string>>* desk = new vector< vector<string>>;
		centerSystem.push_back(desk);
	}
	while (cin >> name >> arrivalTime >> handleTime)
	{
		inputBuffer.push_back(name);
		inputBuffer.push_back(arrivalTime);
		inputBuffer.push_back(handleTime);
		customer.push_back(inputBuffer);
		inputBuffer.clear();
	}
	int count = 0;
	while (true)
	{
		if (!customer.empty() && count == stoi(customer[0][1]))
		{
			int miniSize = customer.size();
			for (int t = 0; t < deskSize; t++)
			{
				if (centerSystem[t]->size() < miniSize)
				{
					miniSize = centerSystem[t]->size();
				}
			}
			for (int t = 0; t < deskSize; t++)
			{
				if (centerSystem[t]->size() == miniSize)
				{
					centerSystem[t]->push_back(customer[0]);
					customer.erase(customer.begin());
					break;
				}
			}
		}
		for (int t = 0; t < deskSize; t++)
		{
			if (!centerSystem[t]->empty() )
			{
				if (stoi(centerSystem[t][0][0][2]) + stoi(centerSystem[t][0][0][1]) == count + 1)
				{
					cout << centerSystem[t][0][0][0] << ' ' << count + 1 << ' ' << t << endl;
					centerSystem[t]->erase(centerSystem[t]->begin());
					if (!centerSystem[t]->empty())
					{
						centerSystem[t][0][0][1] = to_string (count + 1);
					}
				}
			}
		}
		count++;
		bool clearFlag = true;
		for (int  i = 0; i < centerSystem.size(); i++)
		{
			if (centerSystem[i]->size()!=0)
			{
				clearFlag = false;
				break;
			}
		}
		if (customer.empty()&& clearFlag)
		{
			break;
		}
	}
}