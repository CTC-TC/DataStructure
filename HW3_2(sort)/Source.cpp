#include<iostream>
#include<stdlib.h>
#include<vector>
using namespace std;
template<class T>
void change(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
int findSmall(vector<int> array, int startPos)
{
	int seat = startPos;
	int smallest = array[startPos];
	for (int i = startPos + 1; i < array.size(); i++)
	{
		if (array[i] < smallest)
		{
			smallest = array[i];
			seat = i;
		}
	}
	return seat;
}
int main()
{
	vector<int> input, bubble, insert, selection;
	int buffer = 0, swapTime = 0;
	while (cin >> buffer)
	{
		input.push_back(buffer);
	}
	bubble = input;
	for (int core = 0; core < bubble.size(); core++)
	{
		for (int point = 0; point < bubble.size() - core - 1; point++)
		{
			if (bubble[point] > bubble[point + 1])
			{
				swapTime++;
				change(bubble[point], bubble[point + 1]);
				if (swapTime == 5)
				{
					cout << "Bubble: " << bubble[point] << ", " << bubble[point + 1] << ';';
					for (int i = 0; i < bubble.size(); i++)
					{
						cout << ' ' << bubble[i];
					}
					cout << endl;
				}
			}
		}
	}
	insert = input;
	for (int k = 1; k < insert.size(); k++)
	{
		int tmp = insert[k];
		int j = k - 1;
		while (j >= 0 && tmp <= insert[j])
		{
			insert[j + 1] = insert[j];
			j--;
		}
		insert[j + 1] = tmp;
		if (k == 4)
		{
			cout << "Insertion:";
			for (int i = 0; i < insert.size(); i++)
			{
				cout << ' ' << insert[i];
			}
			cout << endl;
		}
	}
	selection = input;
	for (int i = 0; i < selection.size()-1; i++)
	{
		int seat = findSmall(selection, i);
		change(selection[seat], selection[i]);
		if (i == 4)
		{
			cout << "Selection: " << selection[i] << ";";
			for (int b = 0; b < selection.size(); b++)
			{
				cout << ' ' << selection[b];
			}
			cout << endl;
		}
	}
	for (int i = 0; i < bubble.size(); i++)
	{
		if (i != 0)
		{
			cout << ' ';
		}
		cout << bubble[i];
	}
}