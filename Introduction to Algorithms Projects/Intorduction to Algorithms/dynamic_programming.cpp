// 15_��̬�滮.cpp : Defines the entry point for the console application.

//������Ӵ����⣺һ���������е����������ڸ�������ɾȥ����Ԫ�غ�õ������С�������������X��Y������һ����Z����X������������Y��������ʱ����Z������X��Y�Ĺ��������С�
//������Ӵ�����������������е�һ������������С����磬X=��ABCBDAB����Y=��BCDB����X��һ�������С�

//	���������
//	������������A��B��������Z��A��B�Ĺ��������У���ָZͬ��A��B�������С�����Ҫ����֪������A��B������������С�������о�A�����������У���һһ������Ƿ�����B�������У�����ʱ��¼�����ֵ������У������������������С����ַ������ʱ̫�������ȡ��
//	���������������������ηֽ�������⣬��A=��a0��a1������am-1����B=��b0��b1������bm-1������Z=��z0��z1������zk-1��Ϊ���ǵ�����������С�����֤�����������ʣ� 
//	��1�� ���am-1=bn-1����zk-1=am-1=bn-1���ҡ�z0��z1������zk-2���ǡ�a0��a1������am-2���͡�b0��b1������bn-2����һ������������У� 
//	��2�� ���am-1!=bn-1������zk-1!=am-1���̺���z0��z1������zk-1���ǡ�a0��a1������am-2���͡�b0��b1������bn-1����һ������������У� 
//	��3�� ���am-1!=bn-1������zk-1!=bn-1���̺���z0��z1������zk-1���ǡ�a0��a1������am-1���͡�b0��b1������bn-2����һ������������С� 
//	����������A��B�Ĺ���������ʱ������am-1=bn-1�����һ�����һ�������⣬�ҡ�a0��a1������am-2���͡�b0��b1������bm-2����һ�� ����������У����am-1!=bn-1����Ҫ������������⣬�ҳ���a0��a1������am-2���͡�b0��b1������bn-1����һ������������� ���ҳ���a0��a1������am-1���͡�b0��b1������bn-2����һ������������У���ȡ�����нϳ�����ΪA��B������������С�
//	Ϊ�˽�Լ�ظ�����ͬ�������ʱ�䣬����һ�����飬���������Ƿ�����ս����ã�������������Ľ���ڸ������У�����Ƕ�̬�滮�������õĻ�������������˵�����¡� 
//	����c[i][j]Ϊ���С�a0��a1������ai-2���͡�b0��b1������bj-1��������������еĳ��ȣ�����c[i][j]�ɵݹ�ر������£� 
//	��1��c[i][j] = 0                         ���i=0��j=0�� 
//	��2��c[i][j] = c[i-1][j-1]+1             ���i,j>0����a[i-1] == b[j-1]�� 
//	��3��c[i][j] = max{c[i][j-1], c[i-1][j]} ���i,j>0����a[i-1] != b[j-1]�� 
//	������ʽ��д�������������е�����������еĳ��Ⱥ���������c[i][j]�Ĳ�����������c[i-1][j-1]��c[i-1][j]��c[i][j-1]���ʿ��Դ�c[m][n]��ʼ������c[i][j]�Ĳ������̣������������������С�ϸ�ڼ����� 

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

namespace chapter15
{

string LeftHandSide = "abcbdabbadbcddbacbdad";
string RightHandSide = "bdcaadcbdbddababba";

//lcs[i][j]��ζ��:
//ȡLeftHandSide��ǰi���ַ��õ������ַ�����ȡRightHandSide��ǰj���ַ��õ������ַ��� ������������еĳ���
vector< vector<int> > lcs;


//��ͨ�ĵݹ�,ʱ�临�Ӷ�Ϊn��ָ����
int Calc1(int i, int j)
{
	if (i == 0 || j == 0)
	{
		return 0;
	}
	else
	{
		if (LeftHandSide[i - 1] == RightHandSide[j - 1])
		{
			return Calc1(i - 1, j - 1) + 1;
		}
		else
		{
			return max(Calc1(i, j - 1), Calc1(i - 1, j));
		}
	}
}

//�����˱���¼���ܵĵݹ�
//���뱸��¼֮��������ٶȳ�������ȵ�����,�ڵݹ����кܶ��ظ���������ļ���������,����һ��СС�ĸĶ�,����������Ч��
//����Ķ��Ϳ������ӱ���¼�Ĺ���
//1:����ǰ���һ���ж�,�Ƿ��Ѿ��������,����Ѿ�������˾�ֱ��ȡ�������.
//2:ÿ��Ҫ����֮ǰ�Ȱѽ������һ��.
int Calc2(int i, int j)
{
	if (lcs[i][j] != -1)
	{
		return lcs[i][j];
	}

	if (i == 0 || j == 0)
	{
		lcs[i][j] = 0;
		return 0;
	}
	else
	{
		if (LeftHandSide[i - 1] == RightHandSide[j - 1])
		{
			int temp = Calc2(i - 1, j - 1) + 1;
			lcs[i][j] = temp;
			return temp;
		}
		else
		{
			int temp = max(Calc2(i, j - 1), Calc2(i - 1, j));
			lcs[i][j] = temp;
			return temp;
		}
	}
}

//��ͳ�Ķ�̬�滮
//��ͳ�Ķ�̬�滮�������¼���ܵĵݹ�����������:һ�����Ե����ϵ�,һ���ǴӶ�����
//��ͳ�Ķ�̬�滮�������¼���ܵĵݹ���Ȼ������ͬ�Ľ������Ӷ�,������ͳ�Ķ�̬�滮�������Ÿ��õĳ�������,���Ч�ʸ���
void Calc3()
{
	for (int i = 0; i <= LeftHandSide.size(); ++i)
	{
		lcs[i][0] = 0;
	}
	for (int i = 0; i <= RightHandSide.size(); ++i)
	{
		lcs[0][i] = 0;
	}

	for (int i = 1; i <= LeftHandSide.size(); ++i)
	{
		for (int j = 1; j <= RightHandSide.size(); ++j)
		{
			if (LeftHandSide[i - 1] == RightHandSide[j - 1])
			{
				lcs[i][j] = lcs[i - 1][j - 1] + 1;
			}
			else
			{
				lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
			}
		}
	}

	cout << lcs[LeftHandSide.size()][RightHandSide.size()] << endl;
}

int test()
{
	//��ʼ��lcs����,ʹ����Ϊlcs[0..m, 0..n]
	lcs.clear();
	for (size_t i = 0; i < LeftHandSide.size() + 1; ++i)
	{
		vector<int> tmp(RightHandSide.size() + 1, -1);
		lcs.push_back(tmp);
	}


	cout << Calc1(LeftHandSide.size(), RightHandSide.size()) << endl;
	cout << Calc2(LeftHandSide.size(), RightHandSide.size()) << endl;
	Calc3();

	return 0;
}

}