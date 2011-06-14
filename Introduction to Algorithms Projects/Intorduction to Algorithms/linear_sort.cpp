//////////////////////////////////////////////////////////////////////////  
///    COPYRIGHT NOTICE  
///    Copyright (c) 2009
///    All rights reserved.  
///  
/// @file		liner_sort.cpp
/// @brief		liner_sort.cpp�ļ������ 
///  			
///  			liner_sort.cpp����ϸ����
/// 
/// @author		̷����	chuanqi.tan@gmail.com 
/// @date		2011/05/26
/// @version 	1.0
///  
///  
///    �޶�˵��������汾  
//////////////////////////////////////////////////////////////////////////  


#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

namespace chapter8
{
	/// ��������
	void counting_sort()
	{
		int const k_max_size = 100;		//�����������Ԫ�ض�����λ������[0, k_max_size)
		//��ʼ������Ϊ[0, k_max_size)֮����������Ϊ����
		std::vector<int> v;
		for (int i = 0; i < 100; ++i)
		{
			v.push_back(rand() % k_max_size);
		}

		//���м��� c[i] = j������i�����������г�����j��
		std::vector<int> c(k_max_size, 0);
		std::for_each(v.begin(), v.end(), [&](int i){++c[i];});

		//�����еļ����������ܽ���������򣬲�û��ʹ��ԭ���ϵķ���
		//�����ϵ��㷨��ֱ�ӣ��������ϳ���һ����Ч������ͬ���Ľ���ʱ�临�Ӷȵģ��ƺ����õ㡣
		v.clear();
		for (int i = 0; i < k_max_size; ++i)
		{
			for (int k = 0; k < c[i]; ++k)
			{
				v.push_back(i);
			}
		}

		copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "  "));
	}

	/// ��������ʱֵ����ά����3��ζ��Ԫ�ص�����Ϊ[0, 999]
	int const k_max_dim = 3;

	/// ��������
	void radix_sort(std::vector<int> &v, int dim)
	{
		//���ݵ�dimά�Ĵ�С���С��ȶ������������stable����Ҫ���ǻ�������Ļ�ʯ
		stable_sort(v.begin(), v.end(), [&](int left, int right) -> bool{
			//�õ�һ������ĳһά��ֵ
			//eg:	GetDim(987, 1) = 9
			//		GetDim(987, 2) = 8
			//		GetDim(987, 3) = 7
			auto GetDim = [](int number, int d) -> int
			{
				for (int i = 1; i <= k_max_dim - d; ++i)
				{
					number /= 10;
				}
				return number % 10;
			};
			return GetDim(left, dim) < GetDim(right, dim);
		});

		if (dim > 1)
		{
			radix_sort(v, dim - 1);
		}
	}

	/// ���������㷨�ĳ�ʼ���͵���
	void radix_sort_caller()
	{
		//��ʼ��[0,999]֮����������Ϊ����
		std::vector<int> v;
		for (int i = 0; i < 10; ++i)
		{
			v.push_back(rand() % static_cast<int>(pow(10.0, static_cast<double>(k_max_dim))));
		}
		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "  ")); std::cout << std::endl;

		radix_sort(v, k_max_dim);
		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "  "));
	}

	/// Ͱ����
	void bucket_sort()
	{
		//��ʼ��[0,1)֮��������
		vector<double> v;
		for (int i = 0; i < 10; ++i)
		{
			v.push_back((rand() % 100) * 1.0 / 100.0);
		}
		copy(v.begin(), v.end(), ostream_iterator<double>(cout, "  "));
		cout << endl;

		//����Ͱ���������е�Ԫ�ط��뵽��Ӧ��Ͱ��ȥ
		vector< vector<double> > bucket(10);	//10��Ͱ
		for_each(v.begin(), v.end(), [&](double d){
			bucket[d * 10].push_back(d);
		});

		//��ÿһ��Ͱ���Ԫ�ؽ�������
		for_each(bucket.begin(), bucket.end(), [](vector<double> &sub_v){
			sort(sub_v.begin(), sub_v.end());
		});

		//���ΰ�ÿ��Ͱ�е�Ԫ����ȡ�����������һ��
		v.clear();
		for_each(bucket.begin(), bucket.end(), [&](vector<double> &sub_v){
			v.insert(v.end(), sub_v.begin(), sub_v.end());
		});

		copy(v.begin(), v.end(), ostream_iterator<double>(cout, "  "));
	}

	int test()
	{
		cout << endl << "===========��ʼ��������===========" << endl;
		counting_sort();
		cout << endl << "===========��ʼ��������===========" << endl;
		radix_sort_caller();
		cout << endl << "===========��ʼͰ����===========" << endl;
		bucket_sort();

		getchar();
		return 0;
	}
}