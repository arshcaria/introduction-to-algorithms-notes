//////////////////////////////////////////////////////////////////////////  
///    COPYRIGHT NOTICE  
///    Copyright (c) 2009
///    All rights reserved.  
///  
/// @file		HeapSort.cpp  
/// @brief		�������ѧϰ��ʹ�ô�ͷ��  
///  
///  
/// @author		̷����	chuanqi.tan@gmail.com
/// @date		2011-5-25
///  
///  
///    �޶�˵��������汾  
//////////////////////////////////////////////////////////////////////////  

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

namespace chapter6
{


/// ���ֶѵ�����
/// 
/// ��to_make��[0,length)Ԫ����Ϊһ����ȫ���������Ե�i��Ԫ��Ϊ�����������˵�i��Ԫ��֮�ⶼ�����ѵ�����
/// ���ô˷���֮�������ȫ�������Ե�i��Ԫ��Ϊ���������������ѵ�����
/// @to_make	�������ݵ�����
/// @length		���to_make��[0,length)Ԫ����Ϊһ����ȫ������
///				��length��Ԫ��֮��[length, n)��Ԫ�ز������������ȫ��������
/// @i			��Ҫ����ĵ�i��Ԫ��
/// @note		to_make��ǰlength��Ԫ�ز���һ����һ���ѣ���Ϊ���������ѵ����ʣ���������ӳ��Ϊ��ȫ������
void MakeHeap(vector<int> &to_make, size_t length, size_t i)
{
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;
	size_t the_max = i;

	if (left < length && to_make[left] > to_make[i])
	{
		the_max = left;
	}	
	if (right < length && to_make[right] > to_make[the_max])
	{
		the_max = right;
	}

	if (the_max != i)
	{
		std::swap(to_make[i], to_make[the_max]);
		MakeHeap(to_make, length, the_max);
	}
}

/// ����
/// 
/// ��to_built����Ľ���һ����ͷ��
void BuildHeap(vector<int> &to_built)
{
	//����ֻ��Ҫ��to_built.size() / 2 - 1��ʼ��ԭ�����ڣ�
	//��Ҷ�ӽ����˵�����������ӽ�㣨Ϊ�գ���������ѵĶ���ģ�����ֻ��Ҫ�����Ҷ�ӽ��
	for (int i = to_built.size() / 2 - 1; i >= 0; --i)
	{
		MakeHeap(to_built, to_built.size(), i);
	}
}

/// ������
void HeapSort(vector<int> &to_sort)
{
	BuildHeap(to_sort);
	for (int i = to_sort.size() - 1; i > 0; --i)
	{
		std::swap(to_sort[0], to_sort[i]);
		MakeHeap(to_sort, i, 0);
	}
}


/// ���ȶ���
/// 
/// �ѵ���ҪӦ��֮һ�����ȶ���
class PriorityQueue
{
public:
	PriorityQueue()
	{
		int to_init[] = {8,5,78,45,64,987,45,34,23,4,23};
		_queue.assign(to_init, to_init + sizeof(to_init) / sizeof(int));
		BuildHeap(_queue);
	}

	int GetMaxPriority()
	{
		return _queue[0];
	}

	int GetAndPopMaxPriority()
	{
		int max_priority = GetMaxPriority();

		std::swap(_queue[0], _queue[_queue.size() - 1]);
		_queue.erase(_queue.end() - 1);
		MakeHeap(_queue, _queue.size(), 0);

		return max_priority;
	}

	void ChangePriority(int index, int new_priority)
	{
		if (_queue[index] == new_priority)
		{//���ȼ����䣬ֱ�ӷ���
			return;
		}

		if (_queue[index] > new_priority)
		{//�������ȼ�
			_queue[index] = new_priority;
			MakeHeap(_queue, _queue.size(), index);
		}
		else
		{//�������ȼ�			
			_queue[index] = new_priority;
			while(index > 0)
			{
				int parent_index = static_cast<int>((index + 1) / 2) - 1;

				if (_queue[parent_index] < _queue[index])
				{
					std::swap(_queue[parent_index], _queue[index]);
					index = parent_index;
				}
				else
				{
					break;
				}			
			}
		}
	}

	void Insert(int priority)
	{
		_queue.push_back(std::numeric_limits<int>::min());
		ChangePriority(_queue.size() - 1, priority);
	}

	bool IsEmpty()
	{
		return _queue.empty();
	}

	void Display()
	{
		copy(_queue.begin(), _queue.end(), ostream_iterator<int>(cout, "  "));
		cout << endl;
	}

private:
	vector<int> _queue;
};



int test()
{
	int to_init[] = {8,5,78,45,64,987,45,34,23,4,23};
	vector<int> to_sort(to_init, to_init + sizeof(to_init) / sizeof(int));
	cout << "ԭʼ���飬׼�����ж�����";
	copy(to_sort.begin(), to_sort.end(), ostream_iterator<int>(cout, "  "));
	HeapSort(to_sort);
	//reverse(result.begin(), result.end());
	cout << endl << "�����������";
	copy(to_sort.begin(), to_sort.end(), ostream_iterator<int>(cout, "  "));
	cout << endl;

	cout << "��ʼ��һ�����ȶ��У�";
	PriorityQueue queue;
	queue.Display();
	cout << "��ʼ���ϵ�ȡ������ȼ���������У�" << endl;
	while(!queue.IsEmpty())
	{
		cout << queue.GetAndPopMaxPriority() << ":\t";
		queue.Display();
	}

	cout << "��ʼ����������У�" << endl;
	for (size_t i = 0; i < to_sort.size(); ++i)
	{
		queue.Insert(to_sort[i]);
		queue.Display();
	}

	cout << "����һ����������ȼ�������2���ȼ�����Ϊ-9���Զ������ѣ�" << endl;
	queue.ChangePriority(2, -9);
	queue.Display();

	return 0;
}

}