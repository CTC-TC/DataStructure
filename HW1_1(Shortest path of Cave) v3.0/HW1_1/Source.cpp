#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<vector>
#include<iostream>
using namespace std;
char rightHand, ahead, leftHand;
vector<vector<char>> mape;
int IfPrint = 0, mapeSize = 0;
int coordinate[4][2] = { 0 };//�{�b�y��([0][0],[0][1])(x,y)�B�W���y��([1][0],[1][1])[1][1](x,y)
//�J�f�y��([2][0],[2][1])(x,y)�B�X�f�y��([3][0],[3][1])(x,y)
int precoordinate[3][2] = { 0 };//�U���y��(�e�B�k�B��)
int direction;//(1-north,3-south,0-east,2-west)
void printmape()//�N��Ӧa�ϥثe���p���L�X��
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
		precoordinate[0][0] = X_axis + 1;//�U���y��(�eX)
		precoordinate[0][1] = Y_axis;//�U���y��(�eY)
		precoordinate[1][0] = X_axis;//�U���y��(�kX)
		precoordinate[1][1] = Y_axis - 1;//�U���y��(�kY)
		precoordinate[2][0] = X_axis;//�U���y��(��X)
		precoordinate[2][1] = Y_axis + 1;//�U���y��(��Y)
		break;
	case 1:
		ahead = mape[Y_axis + 1][X_axis];
		rightHand = mape[Y_axis][X_axis + 1];
		leftHand = mape[Y_axis][X_axis - 1];
		precoordinate[0][0] = X_axis;//�U���y��(�eX)
		precoordinate[0][1] = Y_axis + 1;//�U���y��(�eY)
		precoordinate[1][0] = X_axis + 1;//�U���y��(�kX)
		precoordinate[1][1] = Y_axis;//�U���y��(�kY)
		precoordinate[2][0] = X_axis - 1;//�U���y��(��X)
		precoordinate[2][1] = Y_axis;//�U���y��(��Y)
		break;
	case 2:
		ahead = mape[Y_axis][X_axis - 1];
		rightHand = mape[Y_axis + 1][X_axis];
		leftHand = mape[Y_axis - 1][X_axis];
		precoordinate[0][0] = X_axis - 1;//�U���y��(�eX)
		precoordinate[0][1] = Y_axis;//�U���y��(�eY)
		precoordinate[1][0] = X_axis;//�U���y��(�kX)
		precoordinate[1][1] = Y_axis + 1;//�U���y��(�kY)
		precoordinate[2][0] = X_axis;//�U���y��(��X)
		precoordinate[2][1] = Y_axis - 1;//�U���y��(��Y)
		break;
	case 3:
		ahead = mape[Y_axis - 1][X_axis];
		rightHand = mape[Y_axis][X_axis - 1];
		leftHand = mape[Y_axis][X_axis + 1];
		precoordinate[0][0] = X_axis;//�U���y��(�eX)
		precoordinate[0][1] = Y_axis - 1;//�U���y��(�eY)
		precoordinate[1][0] = X_axis - 1;//�U���y��(�kX)
		precoordinate[1][1] = Y_axis;//�U���y��(�kY)
		precoordinate[2][0] = X_axis + 1;//�U���y��(��X)
		precoordinate[2][1] = Y_axis;//�U���y��(��Y)
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
	//�a��Ū��
	coordinate[2][0] = 0;
	coordinate[2][1] = mapeSize - 1;
	//��J�f
	coordinate[3][0] = mapeSize - 1;
	coordinate[3][1] = 0;
	//��X�f
	coordinate[0][0] = coordinate[2][0];
	coordinate[0][1] = coordinate[2][1];
	direction = 0;
	//�y�Ъ�l��
	move();
}