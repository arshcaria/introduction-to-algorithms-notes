#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

namespace chapter21
{

	/// ���ڲ��ཻ���ϵ����ݽṹ�����鼯��
	class DisjointSetForest
	{
	public:
		/// �����е�һ��Ԫ��
		template<typename T>
		struct DisjointSet
		{
			T				Item;		///< Ԫ�ص�ֵ
			int				Rank;		///< Ԫ�ص���
			DisjointSet		*Parent;	///< Ԫ�صĸ�Ԫ��

			/// ����һ����㣺��ӦMAKE-SET����
			DisjointSet(T const &item) : Item(item), Rank(0)
			{
				Parent = this;
			}
		};

		#pragma region �鲢����3����������

		/// ����һ�����ϵĲ�����MAKE-SET
		template<typename T>
		static DisjointSet<T> & MakeSet(T const &item)
		{
			return *new DisjointSet<T>(item);
		}

		/// �����������ϵĲ�����FIND-SET
		template<typename T>
		static DisjointSet<T> & FindSet(DisjointSet<T> &a_set)
		{
			//·��ѹ��
			if (&a_set != a_set.Parent)		//ͨ����ַ�е�
			{
				a_set.Parent = &FindSet(*a_set.Parent);
			}
			return *a_set.Parent;
		}

		/// �ϲ�������UNION
		template<typename T>
		static void Union(DisjointSet<T> &x, DisjointSet<T> &y)
		{
			_Link(FindSet(x), FindSet(y));
		}

		#pragma endregion

	private:
		template<typename T>
		static void _Link(DisjointSet<T> &x, DisjointSet<T> &y)
		{
			if (x.Rank > y.Rank)
			{
				y.Parent = &x;
			}
			else
			{
				x.Parent = &y;
			}

			if (x.Rank == y.Rank)
			{
				++y.Rank;
			}
		}
	};

	void test()
	{
		vector<DisjointSetForest::DisjointSet<int> *> nodes;
		for (int i = 0; i < 10; ++i)
		{
			nodes.push_back(&DisjointSetForest::MakeSet(i));
		}

		
		for (int i = 0; i < 5; ++i)
		{
			int index1 = rand() % 10;
			int index2 = rand() % 10;
			DisjointSetForest::Union(*nodes[index1], *nodes[index2]);
			cout << "Union : " << index1 << "---" << index2 << endl;
		}

		for (int i = 0; i < 10; ++i)
		{
			cout << i << "-------------->" << DisjointSetForest::FindSet(*nodes[i]).Item << endl;
		}

		//for (int i = 0; i < nodes.size(); ++i)
		//{
		//	FindSet(nodes[i]);
		//	cout << FindSet(nodes[i])->Item << endl;
		//}
	}
}