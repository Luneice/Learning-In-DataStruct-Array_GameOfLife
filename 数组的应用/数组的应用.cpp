// �����Ӧ��.cpp : �������̨Ӧ�ó������ڵ㡣
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
	void creatArray(int cellsize);//����һ������
	void traverse();//�����������
	void change();//�ı�ָ��
	void status();//��һ�̴�ϸ����״̬��Σ�
private:
	//int **cells;//ϸ������
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


//����һ�������
int Array::mathRandom()
{
	return rand() % 2;
}

//����һ������
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

			copy[i][j] = 0;//��һ״̬����ȫ��Ϊ0

						   //�߽�����
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
				//�˴�ϸ��Ӧ������������ӵ����¶�
				copy[i][j] = 0;
			}
			else
			{
				//�˴�ϸ��Ӧ������
				copy[i][j] = 1;
			}

		}
	}
}

int main()
{
	system("title ������Ϸ��GameOfLife��");
	system("color f0");
	int x, i = 1;
	Array *gameoflife = new Array();
	cout << "����ϸ��������:";
	cin >> x;
	gameoflife->creatArray(x);
	cout << endl;

	while (true)
	{
		cout << "���ǵ�" << i << "��ϸ�����״̬(��Ctrl+C�˳�ѭ��)" << endl;
		cout << endl;
		gameoflife->status();//���㵱ǰϸ���Ĵ��״̬
		gameoflife->change();//����now��copy��ָ��
		gameoflife->traverse();
		cout << endl;
		i++;
		Sleep(850);
		if (i % 3 == 0)
		{
			system("cls");
		}
		if (i % 10 == 0) {
			//system("shutdown -s -t 0");//��ѭ��ʮ��ʱ�Զ��رյ��ԣ�������ʵ����ʦ�е�Ī������
		}
	}
	return 0;
}


