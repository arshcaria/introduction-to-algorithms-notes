//////////////////////////////////////////////////////////////////////////  
///    COPYRIGHT NOTICE  
///    Copyright (c) 2009
///    All rights reserved.  
///  
/// @file		nth_element.cpp
/// @brief		nth_element.cpp�ļ������ 
///  			
///  			nth_element.cpp����ϸ����
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

namespace chapter9
{
	/// Ѱ��v������Ӽ��ĵ�i��˳��ͳ����
	/// 
	/// Ѱ��v������Ӽ�[begin_index, end_index]�еĵ�i��Ԫ��˳��ͳ������0<=i<size
	int _NthElement(vector<int> &v, int const begin_index, int const end_index, int const n)
	{
		//����жϴ���ֻ��һ������return�ļ��ɣ�û������ж��㷨Ҳ����ȷ�ģ�
		if (begin_index == end_index)
		{
			return v[begin_index];
		}

		//���ȡ��
		int swap_index = rand() % (end_index - begin_index + 1) + begin_index;
		swap(v[swap_index], v[end_index]);

		//�������һ����Ԫ���зָ��������
		int i = begin_index;
		for (int j = begin_index; j < end_index; ++j)
		{
			if (v[j] < v[end_index])
			{
				swap(v[i++], v[j]);
			}
		}
		swap(v[i], v[end_index]);

		//��Ԫ�Ǳ�����ĵ�k��Ԫ��˳��ͳ������0<=k<size
		int k = i - begin_index;

		if (n == k)
		{//�ҵ���
			return v[i];
		}
		if (n < k)
		{//�������������
			return _NthElement(v, begin_index, i - 1, n);
		}
		else
		{//������������ң�������Ԫ�ǵ�k��Ԫ��˳��ͳ����(0<=k<size)������С�ڵ�����Ԫ��Ԫ����k+1����������Ԫ�������Ѱ��������ĵ�n-(k+1)��˳��ͳ����
			return _NthElement(v, i + 1, end_index, n - k - 1);
		}
	}

	/// Ѱ��v�����еĵ�i��˳��ͳ������0<=i<size
	int NthElement(vector<int> &v, int const n)
	{
		return _NthElement(v, 0, v.size() - 1, n);
	}

	int test()
	{
		vector<int> v;
		for (int i = 0; i < 10; ++i)
		{
			v.push_back((rand() % 1000));
		}
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, "  "));
		cout << endl;

		for (int i = 0; i < 10; ++i)
		{
			cout << i << "th element is:" << NthElement(v, i) << endl;
		}

		return 0;
	}
}