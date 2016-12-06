// 数组的应用.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"
#include "iostream"
#include "iomanip"


using namespace std;

class Array
{
public:
	Array();
	~Array();
	int mathRandom();
	void creatArray(int cellsize);//构建一个矩阵
	void traverse();//遍历这个矩阵
	void change();//改变指向
	void status();//下一刻此细胞的状态如何？
private:
	//int **cells;//细胞数量
	int arraylength;
	int **now;
	int **copy;
};

Array::Array()
{
	arraylength = 0;
}

Array::~Array()
{
	delete now;
	delete copy;

}


//产生一个随机数
int Array::mathRandom()
{
	return rand() % 2;
}

//创建一个矩阵
void Array::creatArray(int cellsize)
{
	arraylength = cellsize + 2;
	now = new int *[arraylength];
	copy = new int *[arraylength];
	for (int i = 0; i < arraylength; i++)
	{
		now[i] = new int[arraylength];
		copy[i] = new int[arraylength];
		for (int j = 0; j < arraylength; j++)
		{

			copy[i][j] = 0;//下一状态数组全部为0

						   //边界问题
			if (i == 0 || j == 0 || i == arraylength - 1 || j == arraylength - 1)
			{
				now[i][j] = 0;
			}
			else
			{
				now[i][j] = this->mathRandom();
			}

		}
	}
}

void Array::traverse()
{
	for (int i = 1; i < arraylength - 1; i++) {
		for (int j = 1; j < arraylength - 1; j++)
		{
			cout << setw(2);
			if (now[i][j] == 1)
			{
				cout << "*" << setw(2);
			}
			else
			{
				cout << "-" << setw(2);
			}

		}
		cout << endl;
	}
}

void Array::change()
{
	int **temp;
	temp = now;
	now = copy;
	copy = temp;

}

void Array::status()
{
	int i, j, top, bottom, left, right;
	int number = 0;
	for (i = 1; i < arraylength - 1;i++)
	{

		for (j = 1; j < arraylength - 1;j++)
		{
			top = i - 1;
			bottom = i + 1;
			left = j - 1;
			right = j + 1;
			number = now[top][left] + now[top][j] + now[top][right] + now[i][left] + now[i][right] + now[bottom][left] + now[bottom][j] + now[bottom][right];
			if (number < 2 || number > 3)
			{
				//此处细胞应该死亡，过于拥挤或孤独
				copy[i][j] = 0;
			}
			else
			{
				//此处细胞应该再生
				copy[i][j] = 1;
			}

		}
	}
}

int main()
{
	system("title 生命游戏（GameOfLife）");
	system("color f0");
	int x, i = 1;
	Array *gameoflife = new Array();
	cout << "输入细胞行列数:";
	cin >> x;
	gameoflife->creatArray(x);
	cout << endl;

	while (true)
	{
		cout << "这是第" << i << "代细胞存活状态(按Ctrl+C退出循环)" << endl;
		cout << endl;
		gameoflife->status();//计算当前细胞的存活状态
		gameoflife->change();//交换now与copy的指向
		gameoflife->traverse();
		cout << endl;
		i++;
		Sleep(850);
		if (i % 3 == 0)
		{
			system("cls");
		}
		if (i % 10 == 0) {
			//system("shutdown -s -t 0");//当循环十次时自动关闭电脑，可以让实验老师有点莫名其妙
		}
	}
	return 0;
}


