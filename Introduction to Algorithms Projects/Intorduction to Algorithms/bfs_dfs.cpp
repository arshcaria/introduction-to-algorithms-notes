/// ����������� & �����������

#include "stdafx.h"

#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <bitset>
#include "graphics.h"

using namespace std;

namespace chapter22
{
	/// ������ȱ���
	template<typename T>
	void BreadthFirstSearch(GraphicsViaAdjacencyList<T> &g, size_t start_index)
	{
		queue<size_t>	q;
		vector<bool>	trivaled(g.GetVertex().size(), false);
		q.push(start_index);
		trivaled[start_index] = true;

		cout << "������ȱ�����";
		while (!q.empty())
		{//���û�б��������еĽ��
			char current = q.front();
			q.pop();
			cout << g.GetVertex()[current] << "  ";

			for (size_t i = 0; i < g.GetVertex().size(); ++i)
			{
				if (!trivaled[i] && g.IsLinked(current, i).first)
				{
					//û�б������� �� �뵱ǰ������Ԫ���ڽ�
					q.push(i);
					trivaled[i] = true;
				}
			}
		}
	}

	/// ������ȱ����ĵݹ����
	/// 
	/// @return		���ر���������ȱ����õ��������������������Ľ��
	template<typename T>
	vector<int> DFS_Visit(GraphicsViaAdjacencyList<T> &g, size_t index, vector<int> &d, vector<int> &f, vector<bool> &traversed, int &time)
	{
		vector<int> this_time_traversed;
		this_time_traversed.push_back(index);
		traversed[index] = true;
		++time;
		d[index] = time;

		for (size_t i = 0; i < g.GetVertex().size(); ++i)
		{
			if (!traversed[i] && g.IsLinked(index, i).first)
			{
				vector<int> v = DFS_Visit(g, i, d, f, traversed, time);
				this_time_traversed.insert(this_time_traversed.end(), v.begin(), v.end());
			}
		}

		++time; 
		f[index] = time;
		return this_time_traversed;
	}

	/// ������ȱ���
	template<typename T>
	void DeapthFirstSearch(GraphicsViaAdjacencyList<T> &g)
	{
		vector<int>		d(g.GetVertex().size());				//ʱ���d
		vector<int>		f(g.GetVertex().size());				//ʱ���f
		vector<bool>	traversed(g.GetVertex().size(), false);	//��ʶ�����Ƿ��Ѿ�������
		int				time = 0;
		
		cout << endl << "������ȱ�����";
		for (size_t i = 0; i < g.GetVertex().size(); ++i)
		{
			if (!traversed[i])
			{
				vector<int> ids = DFS_Visit(g, i, d, f, traversed, time);
				for (size_t k = 0; k < ids.size(); ++k)
				{
					cout << g.GetVertex()[ids[k]] << "[" << d[ids[k]] << "," << f[ids[k]] << "] ";
				}
			}			
		}

		cout << endl << "������ȱ�����";
		vector<pair<int, pair<int, int>>> r;
		for (size_t i = 0; i < g.GetVertex().size(); ++i)
		{
			r.push_back(make_pair(i, make_pair(d[i], f[i])));
		}
		//����ʱ���d������ú���֮�����������ȱ����Ľ��
		//�������Լ��Ƶ������ģ��ҵ�֤��˼·�ǣ�����������ȵġ����Ŷ�����ʱ���d����ǰ��Ľ������λ��ǰ��������ڣ�Ҳ����λ������������������ǰ��
		//����˵����ͬʱ����ʱ����������������ð�������d����Ϳ��Եó�������ȵĴ��򣬸���f�����ֿ��Եó����������˳��
		sort(r.begin(), r.end(), [](pair<int, pair<int, int>> const &p1, pair<int, pair<int, int>> const &p2){return p1.second.first < p2.second.first;});
		for (size_t i = 0; i < r.size(); ++i)
		{
			cout << g.GetVertex()[r[i].first] << "[" << r[i].second.first << "," << r[i].second.second << "] ";
		}
	}



	void BFS_And_DFS()
	{
		vector<char> v;
		for (int i = 0; i < 8; ++i)
		{
			v.push_back('r' + i);
		}
		GraphicsViaAdjacencyList<char> g(v, Undigraph);
		g.Link2Vertex(0, 1);
		g.Link2Vertex(0, 4);
		g.Link2Vertex(1, 5);
		g.Link2Vertex(2, 5);
		g.Link2Vertex(2, 3);
		g.Link2Vertex(2, 6);
		g.Link2Vertex(3, 6);
		g.Link2Vertex(3, 7);
		g.Link2Vertex(5, 6);
		g.Link2Vertex(6, 7);

		BreadthFirstSearch(g, 1);
		cout << endl;
		DeapthFirstSearch(g);
		cout << endl;
	}
}