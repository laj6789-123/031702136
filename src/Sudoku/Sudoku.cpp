#include "pch.h"
#include<iostream> 
#include <fstream>
#include <stdlib.h>
#include<string>
using namespace std;
bool sign = false;//������ɱ�־
// ������������ 
int num[10][10], num2[100][100][100];
bool Check(int n, int key);
int DFS(int n);
int jie_num;    //jieΪ������� 
int pan_num;   //������Ŀ 

int main(int argc, char* argv[])
{
	int k, i, j;
	char* in;  //�����ļ� 
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
		outfile.open("output.txt", ios::app);   //�Ժ�̷�ʽ���ļ��Ա����д
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
bool Check(int n, int key)//�ж���������Ƿ�Ϸ� 
{
	for (int i = 0; i < jie_num; i++)//�ж�n���ں����Ƿ�Ϸ� 
	{
		int j = n / jie_num;    // jΪn������
		if (num[j][i] == key)
			return false;
	}
	for (int i = 0; i < jie_num; i++)//�ж�n���������Ƿ�Ϸ� 
	{
		int j = n % jie_num;    //jΪn������ 
		if (num[i][j] == key)
			return false;
	}
	if (jie_num == 4 || jie_num == 6 || jie_num == 8 || jie_num == 9)//4689 �������� 
	{
		int a, b;   //aΪÿ��С�����к���ĸ�������bΪ��������� 
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
		int x = n / jie_num / b * b;     //xΪn���ڵ�С�����󶥵�������
		int y = n % jie_num / a * a;     //yΪn���ڵ�С�����󶥵������
		for (int i = x; i < x + b; i++)//�ж�n���ڵ�С�����Ƿ�Ϸ� 
		{
			for (int j = y; j < y + a; j++)
			{
				if (num[i][j] == jie_num) return false;
			}
		}
	}
	return true;    //���Ϸ���������ȷ

}
int DFS(int n)//����+���� 
{
	int total;//ÿ�������е�������1 
	total = jie_num * jie_num - 1;
	if (n > total)
	{
		sign = true;
		return 0;
	}
	if (num[n / jie_num][n % jie_num] != 0)//��ǰλ��Ϊ��ʱ����
	{
		DFS(n + 1);
	}
	else
	{
		for (int i = 1; i <= jie_num; i++)//����Ե�ǰλ����ö�ٲ���
		{
			//��������ʱ�������� 
			if (Check(n, i) == true)
			{
				num[n / jie_num][n % jie_num] = i;
				DFS(n + 1);    // �������� 
				if (sign == true)  //����ʱ�������ɹ�����ֱ���˳� 
				{
					return 0;
				}
				num[n / jie_num][n % jie_num] = 0;//������첻�ɹ�����ԭ��ǰλ 
			}
		}
	}
	return 0;
}