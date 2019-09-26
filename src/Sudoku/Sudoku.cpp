#include "pch.h"
#include<iostream> 
#include <fstream>
#include <stdlib.h>
#include<string>
using namespace std;
bool sign = false;//构造完成标志
// 创建数独矩阵 
int num[10][10], num2[100][100][100];
bool Check(int n, int key);
int DFS(int n);
int jie_num;    //jie为宫格阶数 
int pan_num;   //盘面数目 

int main(int argc, char* argv[])
{
	int k, i, j;
	char* in;  //输入文件 
	char* out;

	jie_num = atoi(argv[2]);
	pan_num = atoi(argv[4]);
	in = argv[6];
	ifstream infile(in);
	out = argv[8];
	ofstream outfile(out);
	for (k = 0; k < pan_num; k++) {
		char temp[10][10] = { 0 };
		int flag = 0;
		for (i = 0; i < jie_num; i++)
		{
			for (j = 0; j < jie_num; j++)
			{
				infile >> temp[i][j];
				num[i][j] = temp[i][j] - '0';
			}
			flag++;
		}
		cout << endl;
		sign = false;
		DFS(0);
		for (i = 0; i < jie_num; i++)
		{
			for (j = 0; j < jie_num; j++)
			{
				num2[k][i][j] = num[i][j];
			}
		}

		for (i = 0; i < jie_num; i++)
		{
			for (j = 0; j < jie_num; j++)
			{
				cout << num2[k][i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		ofstream outfile;
		outfile.open("output.txt", ios::app);   //以后继方式打开文件以便继续写
		for (int i = 0; i < jie_num; i++) {
			for (int j = 0; j < jie_num; j++) {
				outfile << num2[k][i][j] << " ";
			}
			outfile << endl;
		}
		outfile << "\n";
		outfile.close();
	}
	return 0;
}
bool Check(int n, int key)//判断填入的数是否合法 
{
	for (int i = 0; i < jie_num; i++)//判断n所在横列是否合法 
	{
		int j = n / jie_num;    // j为n竖坐标
		if (num[j][i] == key)
			return false;
	}
	for (int i = 0; i < jie_num; i++)//判断n所在竖列是否合法 
	{
		int j = n % jie_num;    //j为n横坐标 
		if (num[i][j] == key)
			return false;
	}
	if (jie_num == 4 || jie_num == 6 || jie_num == 8 || jie_num == 9)//4689 规律相似 
	{
		int a, b;   //a为每个小宫格中横向的格子数，b为纵向格子数 
		switch (jie_num)
		{
		case 4:
			a = 2, b = 2;
			break;
		case 6:
			a = 3, b = 2;
			break;
		case 8:
			a = 2, b = 4;
			break;
		case 9:
			a = 3, b = 3;
			break;
		}
		int x = n / jie_num / b * b;     //x为n所在的小宫格左顶点竖坐标
		int y = n % jie_num / a * a;     //y为n所在的小宫格左顶点横坐标
		for (int i = x; i < x + b; i++)//判断n所在的小宫格是否合法 
		{
			for (int j = y; j < y + a; j++)
			{
				if (num[i][j] == jie_num) return false;
			}
		}
	}
	return true;    //都合法，返回正确

}
int DFS(int n)//深搜+回溯 
{
	int total;//每个数独中的总数—1 
	total = jie_num * jie_num - 1;
	if (n > total)
	{
		sign = true;
		return 0;
	}
	if (num[n / jie_num][n % jie_num] != 0)//当前位不为空时跳过
	{
		DFS(n + 1);
	}
	else
	{
		for (int i = 1; i <= jie_num; i++)//否则对当前位进行枚举测试
		{
			//满足条件时填入数字 
			if (Check(n, i) == true)
			{
				num[n / jie_num][n % jie_num] = i;
				DFS(n + 1);    // 继续搜索 
				if (sign == true)  //返回时如果构造成功，则直接退出 
				{
					return 0;
				}
				num[n / jie_num][n % jie_num] = 0;//如果构造不成功，还原当前位 
			}
		}
	}
	return 0;
}