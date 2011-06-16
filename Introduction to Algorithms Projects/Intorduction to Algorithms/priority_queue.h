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



#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
using namespace std;

namespace ita
{
	/// ���ȶ���
	/// 
	/// �ѵ���ҪӦ��֮һ�����ȶ���
	/// @notes	�����ж��е�Ԫ��һ�������뵽������ȥ�˾Ͳ�Ӧ�����޸ģ����ڶ����е�Ԫ��Ӧ��ֻ֧��Top, Pop, Push����
	template<
		typename ItemType,								///< ������Ԫ������
		typename Comparator = less<ItemType>,			///< �ж����ȼ�ʱ��ʹ�õĶ���
		typename ContainerType = vector<ItemType>>		///< �����ڲ���ʹ�õ���������
	class PriorityQueue
	{
	public:
		typedef PriorityQueue<ItemType, Comparator, ContainerType>	_MyType;
		typedef	ItemType &			Reference;
		typedef ItemType const &	ConstReference;

		PriorityQueue()
		{}

		template<typename IterType>
		PriorityQueue(IterType begin, IterType end) : _queue(begin, end)
		{
			make_heap(_queue.begin(), _queue.end(), _comparator);
		}

		void Push(ItemType const &item)
		{
			_queue.push_back(item);
			push_heap(_queue.begin(), _queue.end(), _comparator);
		}

		ConstReference Top() const
		{
			return *_queue.begin();
		}

		///// ���ط�const�Ķ���Ԫ��
		///// 
		///// ����Ϊ��Ӧ���������������Ϊ�����Ļ�����ͨ�������const�������޸�Top Item�����ȼ������������жӾͿ��ܲ��پ���һ�����ˣ�
		///// �����Ҫ�ı����ȼ���Ӧ��ʹ��RefreshQueue����ܵķ���
		///// @deprecated
		//Reference Top()
		//{
		//	return *_queue.begin();
		//}

		void Pop()
		{
			pop_heap(_queue.begin(), _queue.end(), _comparator);
			_queue.pop_back();
		}

		bool IsEmpty()
		{
			return _queue.empty();
		}

		/// �������������ж��е�Ԫ��
		/// 
		/// ��������ǳ���Ҫ�������������֮�������жӾͿ���֧���޸����ȼ��Ĳ����ˡ�
		/// @code
		/// 
		/// auto comparator = [](ItemType *item1, ItemType *item2){return item1->Priority() < item2->Priority();};
		/// PriorityQueue<ItemType *, comparator> q;
		/// items[6]->SetPriority(66);		//�ӱ𴦸ı���ĳ��Ԫ�ص����ȼ�
		/// q.RefreshQueue();				//һ��Ҫ�ǵõ���RefreshQueue������������Ԫ�ص����ȼ����ⲿ�޸�֮�����ȶ��е��ڲ�״̬����һ�£�
		/// 
		/// @endcode
		void RefreshQueue()
		{
			make_heap(_queue.begin(), _queue.end(), _comparator);
		}

		void Display()
		{
			copy(_queue.begin(), _queue.end(), ostream_iterator<ItemType>(cout, "  "));
			cout << endl;
		}

	private:
		ContainerType			_queue;			///< ����
		Comparator				_comparator;	///< �Ƚ���
	};

}