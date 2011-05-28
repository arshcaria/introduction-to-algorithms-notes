#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
using namespace std;

namespace chapter12
{
	/// ���������
	class BinarySearchTree
	{
	private:
		/// ����������еĽ��
		struct _Node
		{
			int Item;
			_Node *Parent;
			_Node *Left;
			_Node *Right;
		};

	public:
		BinarySearchTree() : _root(NULL)
		{}

		~BinarySearchTree()
		{
			//�Ӹ���㿪ʼ�ݹ������
			_RecursiveReleaseNode(_root);
		}

		/// ����һ�����
		/// 
		/// �����������в���һ��ֵ
		/// @param		Ҫ�����ֵ
		/// @param		�Ƿ����ɹ���ʧ����ζ�������Ѿ����ڸ�ֵ
		bool Insert(int const new_value)
		{
			if (Search(new_value))
			{//�Ѿ�����
				return false;
			}

			if (!_root)
			{//������ǵ�1���ڵ�
				_root = new _Node();
				_root->Item = new_value;
				return true;
			}

			//�ǵ�1���ڵ�
			_Node *current_node = _root;

			while (current_node)
			{
				if (new_value > current_node->Item)
				{
					if (current_node->Right)
					{
						current_node = current_node->Right;
					}
					else
					{
						current_node->Right = new _Node();
						current_node->Right->Item = new_value;
						current_node->Right->Parent = current_node;
						break;
					}
				}
				if (new_value < current_node->Item)
				{
					if (current_node->Left)
					{
						current_node = current_node->Left;
					}
					else
					{
						current_node->Left = new _Node();
						current_node->Left->Item = new_value;
						current_node->Left->Parent = current_node;
						break;
					}
				}
			}
		}

		/// ɾ�����
		/// 
		/// �ڶ����������ɾ��һ��ֵ
		/// @param		Ҫɾ����ֵ
		/// @return		�Ƿ�ɾ���ɹ���ɾ��ʧ����ζ������û�����ֵ�Ľ��
		bool Delete(int const delete_value)
		{
			_Node *delete_node = _Search(_root, delete_value);
			if (!delete_node)
			{//δ�ҵ��õ�
				return false;
			}
			else
			{
				_DeleteNode(delete_node);
				return true;
			}
		}

		/// ����Ԫ��
		/// 
		/// �ڵ�ǰ����������в���ĳһֵ
		/// @param		search_valueҪ���ҵ�ֵ
		/// @return		�Ƿ��ڶ��������ҵ�ֵΪsearch_value�Ľ��
		bool Search(int const search_value) const
		{
			return _Search(_root, search_value);
		}

		/// ��ʾ��ǰ�����������״̬
		/// 
		/// ʹ��Graphviz��dot���Ի�����ǰ���������
		void Display() const
		{
			cout << "digraph graphname" << (rand() % 1000) << "{" << endl
				 << "    node [shape = record,height = .1];" << endl;
			_Display(_root);
			cout << "}" << endl;
		}
	
	private:
		void _DeleteNode( _Node * delete_node ) 
		{
			if (delete_node->Left && delete_node->Right)
			{//Ҫɾ���Ľ��ͬʱ������������������
				//ǰ����㣺ǰ��һ�����ڣ���Ϊ�ý��ͬʱ������������
				_Node *previous_node = delete_node; 
				//�����ǰ��������һ�£����ҵ�ͷ
				previous_node = previous_node->Left;
				while (previous_node->Right)
				{
					previous_node = previous_node->Right;
				}

				delete_node->Item = previous_node->Item;
				//previous_ndeһ��û���������������ٵݹ����һ���������if��else��֧
				_DeleteNode(previous_node);	
			}
			else
			{//Ҫɾ���Ľ��������һ���ӽ��Ϊ��
				//sub_nodeΪdelete_node������
				//sub_nodeҪôΪdelete_node����������ҪôΪdelete_node����������������delete_node���ӽ��ʱΪ��
				_Node *sub_node = (delete_node->Left ? delete_node->Left : delete_node->Right);

				if (delete_node->Parent == NULL)
				{//�ǵ�1�����
					_root = sub_node;
				}
				else
				{
					if (delete_node->Parent->Left == delete_node)
					{
						delete_node->Parent->Left = sub_node;
					}
					else
					{
						delete_node->Parent->Right = sub_node;
					}

					if (sub_node)
					{//��delete_node���ӽ��ʱ��Ҫ�����ӽ���Parentָ��
						sub_node->Parent = delete_node->Parent;
					}
				}

				delete delete_node;
			}
		}

		void _RecursiveReleaseNode(_Node *node)
		{
			if (node)
			{			
				_RecursiveReleaseNode(node->Left);
				_RecursiveReleaseNode(node->Right);
				delete node;
			}
		}

		_Node * _Search(_Node *node, int const search_value) const
		{
			if (node)
			{
				if (node->Item == search_value)
				{
					return node;
				}
				else if (search_value < node->Item)
				{
					return _Search(node->Left, search_value);
				}
				else
				{
					return _Search(node->Right, search_value);
				}
			}
			else
			{//node Ϊ�յ�Ȼ��δ�ҵ�
				return NULL;
			}
		}

		void _Display(_Node *node) const
		{
			if (node)
			{
				cout << "    node" << node->Item << "[label = \"<f0>|<f1>" << node->Item << "|<f2>\"];" << endl;

				if (node->Left)
				{
					cout << "    \"node" << node->Item << "\":f0 -> \"node" << node->Left->Item << "\":f1;" << endl;
					_Display(node->Left);
				}
				
				if (node->Right)
				{
					cout << "    \"node" << node->Item << "\":f2 -> \"node" << node->Right->Item << "\":f1;" << endl;
					_Display(node->Right);
				}
			}
		}

		_Node *_root;			///< ����������ĸ����
	};

	int test()
	{
		BinarySearchTree bst;
		//�����ֵ����һ�ö��������
		for (int i = 0; i < 100; ++i)
		{
			bst.Insert(rand() % 100);						
		}
		bst.Display();

		//ɾ�����е�����ֵ���
		for (int i = 1; i < 100; i += 2)
		{
			if(bst.Delete(i))
			{
				cout << "### Deleted [" << i << "] ###" << endl;
			}
		}
		bst.Display();

		//����100���ڵ���������ڶ���������У�����ʾ
		cout << endl;
		for (int i = 0; i < 100; i += 1)
		{
			if (bst.Search(i))
			{
				cout << "����[" << i << "]Ԫ�أ�" << boolalpha << true << endl;
			}			
		}

		return 0;
	}
}