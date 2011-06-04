#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <numeric>
#include <set>
#include <cmath>
using namespace std;

namespace chapter15
{
	struct Point
	{
		int X, Y;
		Point(int x, int y) : X(x), Y(y){}
		Point() : X(0), Y(0){}
	};

	/// ˫��ŷ���������������
	/// 
	/// �ο�����ƪBlog http://blog.sina.com.cn/s/blog_41630e7e0100dp4o.html 
	/// ���ĵ�˼����ȷ�������ڱ�������ЩСBUG���ڴ˻���������������
	/// ����������Ҫ����Ҫ���ף�˫���ó������ÿһ�˶��ǵ����ģ�Ҫ������Ҫ����������ȷ��ⲢӦ��������������ǽ���Ĺؼ���
	void BitonicTour()
	{
		//��ʼ��ֵΪ�㷨�����ϵ����ӵ�ֵ
		vector<Point> points;
		points.push_back(Point(1, 7));
		points.push_back(Point(2, 1));
		points.push_back(Point(3, 4));
		points.push_back(Point(6, 5));
		points.push_back(Point(7, 2));
		points.push_back(Point(8, 6));
		points.push_back(Point(9, 3));

		//��������֮��ľ���
		vector<vector<double>> distances(points.size(), vector<double>(points.size()));
		for (size_t i = 0; i < points.size(); ++i)
		{
			for (size_t j = 0; j < points.size(); ++j)
			{
				if (i != j)
				{
					distances[i][j] = sqrt(pow(points[i].X - points[j].X, 2.0) + pow(points[i].Y - points[j].Y, 2.0));
				}
			}
		}

		//B[i][j]��ʾ��i�㵽��0�㣬���ۻص���j�������˫���ó�
		vector<vector<double>> B(points.size(), vector<double>(points.size(), 0));
		for (size_t i = 1; i < points.size(); ++i)
		{
			B[0][i] = B[0][i - 1] + distances[i - 1][i];
			B[i][0] = B[0][i];
		}

		for (size_t i = 1; i < points.size(); ++i)
		{
			for (size_t j = i; j < points.size(); ++j)
			{
				//���뵽������һ������Ҫ���Ⱦ�������
				//B[<=i][<=j]������ֵ�Ѿ�����������ˣ�������������B[i][j]
				//��������һ�㣬�ټ�������˫���ó��ǵ����ģ�ÿһ�˵��±�����ǵ������ߵݼ��Ϳ����������������⡣

				if (i == j)
				{//������i����ǰ���ƽ�1�ķ�֧
					vector<double> vd;
					for (size_t k = 0; k < i; ++k)
					{
						vd.push_back( distances[j][k] + B[k][j] );
					}
					B[i][j] = *min_element(vd.begin(), vd.end());
				}
				else if (j == i + 1)
				{
					vector<double> vd;
					for (size_t k = 0; k < i; ++k)
					{
						vd.push_back( B[i][k] + distances[k][j] );
					}
					B[i][j] = *min_element(vd.begin(), vd.end());
				}
				else
				{
					B[i][j] = B[i][j - 1] + distances[j - 1][j];
				}

				B[j][i] = B[i][j];
			}
		}

		cout << B[points.size() - 1][points.size() - 1] << endl;
	}
}