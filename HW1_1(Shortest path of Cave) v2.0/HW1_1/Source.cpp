#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct coordinate
{
	int x = 0;
	int y = 0;
};
int main(void)
{
	int caveSize;
	cin >> caveSize;
	char buffer;
	vector<vector<char>> Caves(caveSize, vector<char>(caveSize, '0'));
	for (int row = 0; row < caveSize; row++)
	{
		for (int col = 0; col < caveSize; col++)
		{
			cin >> buffer;
			Caves[row][col] = buffer;
		}
	}
	int dirction = 2, dirctionEd = 2;
	coordinate target, position;
	vector<coordinate> shippingWay, route;
	//dirction: 1:朝左 2:朝下 3:朝右 4:朝上
	while (!(position.x == caveSize - 1 && position.y == caveSize - 1))
	{
		dirctionEd = dirction;
		for (int i = -1; i < 3; i++)
		{
			switch ((dirction + i) % 4)
			{
			case 0:
				if (position.y > 0 && Caves[position.y - 1][position.x] != '0')
				{
					target.x = position.x;
					target.y = position.y - 1;
					shippingWay.push_back(target);

				}
				break;
			case 1:
				if (position.x > 0 && Caves[position.y][position.x - 1] != '0')
				{
					target.x = position.x - 1;
					target.y = position.y;
					shippingWay.push_back(target);
				}
				break;
			case 2:
				if (position.y + 1 < caveSize && Caves[position.y + 1][position.x] != '0')
				{
					target.x = position.x;
					target.y = position.y + 1;
					shippingWay.push_back(target);
				}
				break;
			case 3:
				if (position.x + 1 < caveSize && Caves[position.y][position.x + 1] != '0')
				{
					target.x = position.x + 1;
					target.y = position.y;
					shippingWay.push_back(target);
				}
				break;
			default:
				break;
			}
		}
		if (position.x != shippingWay[0].x)
		{
			if (position.x > shippingWay[0].x)
			{
				dirction = 1;
			}
			else
			{
				dirction = 3;
			}
		}
		else if (position.y != shippingWay[0].y)
		{
			if (position.y > shippingWay[0].y)
			{
				dirction = 4;
			}
			else
			{
				dirction = 2;
			}
		}

		if (abs(dirctionEd - dirction) == 2 && !route.empty())
		{
			Caves[position.y][position.x] = 'r';
			route.pop_back();
		}
		position.x = shippingWay[0].x;//move
		position.y = shippingWay[0].y;//move
		shippingWay.clear();
		if (!(Caves[position.y][position.x] == 'R'))
		{
			Caves[position.y][position.x] = 'R';
			route.push_back(position);
		}
		else
		{
			int cross = 0, crossED = 0;
			if (position.y - 1 >= 0 && Caves[position.y - 1][position.x] != '0')
			{
				if (Caves[position.y - 1][position.x] == 'r')
				{
					crossED++;
				}
				cross++;
			}
			if (position.y + 1 < caveSize && Caves[position.y + 1][position.x] != '0')
			{
				if (Caves[position.y + 1][position.x] == 'r')
				{
					crossED++;
				}
				cross++;
			}
			if (position.x + 1 < caveSize && Caves[position.y][position.x + 1] != '0')
			{
				if (Caves[position.y][position.x + 1] == 'r')
				{
					crossED++;
				}
				cross++;
			}
			if (position.x - 1 >= 0 && Caves[position.y][position.x - 1] != '0')
			{
				if (Caves[position.y][position.x - 1] == 'r')
				{
					crossED++;
				}
				cross++;
			}
			if (!(cross > 2))//不是路口
			{
				Caves[position.y][position.x] = 'r';
				route.pop_back();
			}
			else
			{
				if (cross-crossED == 1 )//是路口
				{
					Caves[position.y][position.x] = 'r';
					route.pop_back();
				}
			}
		}

	}

	if (route.front().x + route.front().y != 0)
	{
		target.x = 0;
		target.y = 0;
		route.insert(route.begin(), target);
	}
	for (int i = 0; i < route.size() - 1; i++)
	{
		if (route[i].x != route[i + 1].x)
		{
			if (route[i].x < route[i + 1].x)
			{
				cout << 'E';
			}
			else
			{
				cout << 'W';
			}
		}
		else if (route[i].y != route[i + 1].y)
		{
			if (route[i].y < route[i + 1].y)
			{
				cout << 'S';
			}
			else
			{
				cout << 'N';
			}
		}
	}

}/*for (int i = 0; i < route.size(); i++)
	{
		Caves[route[i].y][route[i].x] = ' ';
	}
	cout << endl;
	for (int i = 0; i < caveSize; i++)
	{
		for (int c = 0; c < caveSize; c++)
		{
			cout << Caves[i][c];
		}
		cout << endl;
	}*/