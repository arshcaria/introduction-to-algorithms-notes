#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
using namespace std;


namespace chapter11
{
	/// ȫ��ɢ�б�
	/// 
	/// ���ȣ�ȫ��ɢ�б���һ��ʹ�á����ӷ����������ײ�����ɢ�б�����
	/// ȫ��ɢ�к����࣬����ѡ��һ���㹻�������p ��ʹ��ÿһ�����ܵĹؼ���k ���䵽0 ��p-1 ��
	/// ��Χ�ڣ�������β��0 ��p-1���������Ǽ���ȫ����0 �C 15��p Ϊ17���輯��Zp Ϊ
	/// {0, 1, 2, ��, p-1}������Zp* Ϊ{1, 2, 3, ��, p-1}������p �����������ǿ��Զ���ɢ��
	/// ����h(a, b, k) = ((a*k + b) mod p) mod m������a ����Zp��b ����Zp*��
	/// ������������a ��b ���ɵ�ɢ�к���������˺����ء���ȫ��ɢ�С�
	/// ȫ��ɢ�еĻ���˼������ִ��<b>��ʼ</b>ʱ����һ����ϸ��Ƶĺ����У������ѡ��һ����Ϊɢ�к�����	
	/// ʹ֮������Ҫ�洢�Ĺؼ��֡����ܶ���ѡ���������Ĺؼ��֣���ƽ����̬���ܺá�
	template<typename T>		///< T��ɢ�б���Ҫ�洢��Ԫ������
	class UniversalHashTable
	{
	public:
		UniversalHashTable()
		{
			_p = 101;		//һ���㹻�������
			_m = 10;		//�۵ĸ���
			_items.resize(_m, NULL);
			for (int i = 0; i < _m; ++i)
			{//ȫ�������ú�ͷ���
				_items[i] = new _Node();
				_items[i]->Next = NULL;
			}

			// ȫ��ɢ�еĻ���˼������ִ��<b>��ʼ</b>ʱ����һ����ϸ��Ƶĺ����У������ѡ��һ����Ϊɢ�к�����
			_a = rand() % (_p - 1) + 1;
			_b = rand() % _p;			
		}

		~UniversalHashTable()
		{
			for_each(_items.begin(), _items.end(), [](_Node *item){
				while (item)
				{
					auto next = item->Next;
					delete item;
					item = next;
				}
			});
		}

		void Insert(T const &new_value)
		{//ʼ�ղ����ڼ����ͷ��ͷ���֮��ĵ�1��λ��
			_Node *new_item = new _Node;
			new_item->Item = new_value;
			new_item->Next = NULL;
			int hash_value = _HashFunction(new_value);

			new_item->Next = _items[hash_value]->Next;
			_items[hash_value]->Next = new_item;
		}

		void Delete(T const &delete_value)
		{
			int hash_value = _HashFunction(delete_value);
			_Node *root = _items[hash_value];

			while (root->Next)
			{
				if (root->Next->Item == delete_value)
				{
					auto temp = root->Next;
					root->Next = root->Next->Next;
					delete temp;
					break;
				}
				else
				{
					root = root->Next;
				}
			}
		}

		T * Search(T const &search_value)
		{
			int hash_value = _HashFunction(search_value);
			_Node *root = _items[hash_value]->Next;

			while (root)
			{
				if (root->Item == search_value)
				{
					return &(root->Item);
				}
				root = root->Next;
			}
			return NULL;
		}


		void Display()
		{
			for (int i = 0; i < _m; ++i)
			{
				_Node *item = _items[i]->Next;	//����ͷ���

				cout << "��[" << setw(3) << i << setw(3) << "]";
				while (item)
				{
					cout << " -> " << item->Item;
					item = item->Next;
				}
				cout << endl;
			}
		}

	protected:

	private:
		/// �ڵ㣨ʹ�õ�����
		/// 
		/// Ҫ����˫����ͻ᷽��ܶడ
		struct _Node
		{
			T Item;
			_Node *Next;
		};

		/// ȫ��ɢ�к���
		/// 
		/// ��������һ��ʼʱ���ѡȡ_a,_b���ټ���ѡȡ_p,_m�ķ���������ȫ��ɢ�еĺ������ڣ�����
		/// h(a, b, k) = ((a*k + b) mod p) mod m
		int _HashFunction(T k)
		{
			return static_cast<int>(_a * k + _b) % _p % _m;
		}


		int _p, _m, _a, _b;
		vector<_Node *> _items;		///< �洢�����ļ���ʹ�õ��Ǵ�ͷ���ĵ�����
	};



	int test()
	{		
		UniversalHashTable<int> table;
		cout << "��ʼ��UniversalHashTable���������[0,100)��" << endl;
		for (int i = 0; i < 100; ++i)
		{
			table.Insert(i);
		}
		table.Display();

		cout << "��ʼɾ������[0,5)��" << endl;
		for (int i = 0; i < 5; ++i)
		{
			table.Delete(i);
		}
		table.Display();
		
		for (int i = 0; i < 10; ++i)
		{
			auto finded = table.Search(i);
			cout << "��ʼ�������[" << i << "]��";
			if (finded)
			{
				cout << *finded << endl;
			}
			else
			{
				cout <<  "δ�ҵ�" << endl;
			}			
		}

		return 0;
	}

}