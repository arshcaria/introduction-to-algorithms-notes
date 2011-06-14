//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2009
///    All rights reserved.
///
/// @file		best_binary_search_tree.cpp
/// @brief		best_binary_search_tree.cpp�ļ������
///
///  			best_binary_search_tree.cpp����ϸ����
///
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2011/06/01
/// @version 	1.0
///
///
///    �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
#include <fstream>
using namespace std;

namespace chapter15
{
	/// ���Ŷ��������
	void BestBinarySearchTree()
	{
		//p1 ... p5�������p0�Ǹ�ռλ����Ϊ�˺���ı��뷽�㣬p0���������
		double p[] = {0, 0.15, 0.1, 0.05, 0.1, 0.2};
		double q[] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1};

		//e[i][j]��ʾ��pi -- pj�����Ŷ�����������������Ҵ���
		vector< vector<double> > e(7, vector<double>(6));
		//w[i][j]��ʾ��pi -- pj�ĸ����ܺ�
		vector< vector<double> > w(7, vector<double>(6));

		//�ȼ����Ҷ�ӽ�㵥����Ϊһ����ʱ���������Ҵ���
		//��e[i][j]��j<iʱ��e[i][j]�������Ҷ�ӽ�㡣e[i][i-1]������ǵ�i-1��Ҷ�ӽ����������Ҵ���
		for (int i = 1; i < 7; ++i)
		{
			e[i][i - 1] = q[i - 1];
		}

		//�����pi -- pj�ĸ����ܺͣ�������ͨ�������������Ҷ�ӽ�㶼Ҫ����
		for (int i = 1; i < 7; ++i)
		{
			for (int j = i - 1; j < 6; ++j)
			{
				for (int k = i; k <= j; ++k)
				{//��ͨ���
					w[i][j] += p[k];
				}
				for (int k = i - 1; k <= j; ++k)
				{//����Ҷ�ӽ��
					w[i][j] += q[k];
				}
			}
		}

		//���ְ����������е��Ƶ��뷨�����ԣ���Ϊ������������ϵ
		//��֪������Ϊn���Ӽ������Ŷ�����������ض�Ҫ��֪������С��n�������Ӽ������Ŷ��������
		for (int length = 1; length <= 5; ++length)
		{//�ӳ��ȶ̵��Ӽ���ʼ�Ƶ����ȳ����Ӽ�
			for (int i = 1; i < 6 - length + 1; ++i)
			{
				//��[i...j]����Ӽ����м������������������Ҵ���
				int j = i + length - 1;

				vector<double> vs;
				for (int k = i; k <= j; ++k)
				{//i<=k<=j����kλ�ý�[i...j]���л��֣���pkΪ[pi...pj]��������ĸ�
					vs.push_back(p[k] + e[i][k - 1] + w[i][k - 1] + e[k + 1][j] + w[k + 1][j]);
				}
				e[i][j] = *min_element(vs.begin(), vs.end());
			}
		}

		//���p1...p5�����Ŷ�����������������Ҵ���
		cout << e[1][5] << endl;
		getchar();
	}
}