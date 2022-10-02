#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
string resultPath;
bool shipping(vector<vector<char>> input, string result, int X, int Y, int size, int count);

int main(void)
{
	int caveSize;
	cin >> caveSize;
	char buffer;
	string path;
	vector<vector<char>> Caves(caveSize, vector<char>(caveSize, '0'));
	for (int row = 0; row < caveSize; row++)
	{
		for (int col = 0; col < caveSize; col++)
		{
			cin >> buffer;
			Caves[row][col] = buffer;
		}
	}
	shipping(Caves, path, 0, 0, caveSize, 0);
	cout << resultPath;
	return 0;
}

bool shipping(vector<vector<char>> input, string result, int X, int Y, int size, int count)
{
	string path = result;
	if (X == size - 1 && Y == size - 1)
	{
		resultPath = path;
		return true;
	}
	else
	{
		if (X < size && Y < size && input[Y][X] == '1')
		{
			if (!shipping(input, path + 'E', X + 1, Y, size, count + 1))
			{
				if (!shipping(input, path + 'S', X, Y + 1, size, count + 1))
				{
					if (!shipping(input, path + 'W', X - 1, Y, size, count + 1))
					{
						if (!shipping(input, path + 'N', X, Y - 1, size, count + 1))
						{
							return false;
						}
					}
					return false;
				}

			}

			/*if (path.empty() || path[path.length() - 1] != 'W')
			{
				shipping(input, path + 'E', X + 1, Y, size, count + 1);
			}
			else if (Y <= size - 1 && (path.length() == 0 || path[path.length() - 1] != 'N'))
			{
				shipping(input, path + 'S', X, Y + 1, size, count + 1);
			}
			else if (X >= 1 && (path.length() == 0 || path[path.length() - 1] != 'E'))
			{
				shipping(input, path + 'W', X - 1, Y, size, count + 1);
			}
			else if (Y >= 1 && (path.length() == 0 || path[path.length() - 1] != 'S'))
			{
				(shipping(input, path + 'N', X, Y - 1, size, count + 1));
			}*/

		}
		else
		{
			return false;
		}
	}
}
