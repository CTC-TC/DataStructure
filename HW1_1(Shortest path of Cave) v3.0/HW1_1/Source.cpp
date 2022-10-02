#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<vector>
#include<iostream>
using namespace std;
char rightHand, ahead, leftHand;
vector<vector<char>> mape;
int IfPrint = 0, mapeSize = 0;
int coordinate[4][2] = { 0 };//現在座標([0][0],[0][1])(x,y)、上次座標([1][0],[1][1])[1][1](x,y)
//入口座標([2][0],[2][1])(x,y)、出口座標([3][0],[3][1])(x,y)
int precoordinate[3][2] = { 0 };//下次座標(前、右、左)
int direction;//(1-north,3-south,0-east,2-west)
void printmape()//將整個地圖目前狀況打印出來
{
	for (int y = mapeSize - 1; y >= 0; y--)
	{
		for (int x = 0; x < mapeSize; x++)
		{
			cout << mape[y][x];
		}
		if (y != 0) { cout << endl; }
	}
}
void search(int X_axis, int Y_axis, int direction)
{
	switch (direction)
	{
	case 0:
		ahead = mape[Y_axis][X_axis + 1];
		rightHand = mape[Y_axis - 1][X_axis];
		leftHand = mape[Y_axis + 1][X_axis];
		precoordinate[0][0] = X_axis + 1;//下次座標(前X)
		precoordinate[0][1] = Y_axis;//下次座標(前Y)
		precoordinate[1][0] = X_axis;//下次座標(右X)
		precoordinate[1][1] = Y_axis - 1;//下次座標(右Y)
		precoordinate[2][0] = X_axis;//下次座標(左X)
		precoordinate[2][1] = Y_axis + 1;//下次座標(左Y)
		break;
	case 1:
		ahead = mape[Y_axis + 1][X_axis];
		rightHand = mape[Y_axis][X_axis + 1];
		leftHand = mape[Y_axis][X_axis - 1];
		precoordinate[0][0] = X_axis;//下次座標(前X)
		precoordinate[0][1] = Y_axis + 1;//下次座標(前Y)
		precoordinate[1][0] = X_axis + 1;//下次座標(右X)
		precoordinate[1][1] = Y_axis;//下次座標(右Y)
		precoordinate[2][0] = X_axis - 1;//下次座標(左X)
		precoordinate[2][1] = Y_axis;//下次座標(左Y)
		break;
	case 2:
		ahead = mape[Y_axis][X_axis - 1];
		rightHand = mape[Y_axis + 1][X_axis];
		leftHand = mape[Y_axis - 1][X_axis];
		precoordinate[0][0] = X_axis - 1;//下次座標(前X)
		precoordinate[0][1] = Y_axis;//下次座標(前Y)
		precoordinate[1][0] = X_axis;//下次座標(右X)
		precoordinate[1][1] = Y_axis + 1;//下次座標(右Y)
		precoordinate[2][0] = X_axis;//下次座標(左X)
		precoordinate[2][1] = Y_axis - 1;//下次座標(左Y)
		break;
	case 3:
		ahead = mape[Y_axis - 1][X_axis];
		rightHand = mape[Y_axis][X_axis - 1];
		leftHand = mape[Y_axis][X_axis + 1];
		precoordinate[0][0] = X_axis;//下次座標(前X)
		precoordinate[0][1] = Y_axis - 1;//下次座標(前Y)
		precoordinate[1][0] = X_axis - 1;//下次座標(右X)
		precoordinate[1][1] = Y_axis;//下次座標(右Y)
		precoordinate[2][0] = X_axis + 1;//下次座標(左X)
		precoordinate[2][1] = Y_axis;//下次座標(左Y)
		break;
	default:
		break;
	}
}
void move()
{

	mape[coordinate[0][1]][coordinate[0][0]] = 'R';
	if (coordinate[0][0] == coordinate[3][0] && coordinate[0][1] == coordinate[3][1])
	{
		printmape();
	}
	else
	{
		search(coordinate[0][0], coordinate[0][1], direction);
		if (leftHand != '0')
		{
			coordinate[0][0] = precoordinate[2][0];
			coordinate[0][1] = precoordinate[2][1];
			direction = (direction + 1) % 4;
		}
		else if (ahead != '0')
		{
			coordinate[0][0] = precoordinate[0][0];
			coordinate[0][1] = precoordinate[0][1];
		}
		else if (rightHand != '0')
		{
			coordinate[0][0] = precoordinate[1][0];
			coordinate[0][1] = precoordinate[1][1];
			direction--;
			if (direction < 0) { direction = direction + 4; }
		}
		else
		{
			direction--;
			if (direction < 0)
			{
				direction = direction + 4;
			}
		}
		move();
	}
}
int main()
{
	cin >> mapeSize;
	mape.resize(mapeSize);
	for (int row = 0; row < mapeSize; row++)
	{
		mape[row].resize(mapeSize);
	}
	char buffer;
	for (int row = mapeSize - 1; row >= 0; row--)
	{
		for (int col = 0; col < mapeSize; col++)
		{
			cin >> buffer;
			mape[row][col] = buffer;
		}
	}
	//地圖讀取
	coordinate[2][0] = 0;
	coordinate[2][1] = mapeSize - 1;
	//找入口
	coordinate[3][0] = mapeSize - 1;
	coordinate[3][1] = 0;
	//找出口
	coordinate[0][0] = coordinate[2][0];
	coordinate[0][1] = coordinate[2][1];
	direction = 0;
	//座標初始化
	move();
}