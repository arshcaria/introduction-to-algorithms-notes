#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <iterator>
#include <bitset>
#include <queue>
#include <limits>
#include "graphics.h"

using namespace std;
using namespace chapter22;

namespace chapter24
{
	template<typename T>
	void InitializeSingleSource(GraphicsViaAdjacencyList<T> &g, vector<int> &d, vector<int> &parent_index, int start_index)
	{
		for (size_t i = 0; i < g.GetVertex().size(); ++i)
		{
			d[i] = numeric_limits<int>::max();
			parent_index[i] = -1;
		}
		d[start_index] = 0;
	}

	/// �ɳ�
	/// 
	/// ǰ�������ǣ�index1->index2������һ����
	/// �����index1�����������ɳ�index2��dֵ����������parent[index2] = index1
	template<typename T>
	void Relax(GraphicsViaAdjacencyList<T> &g, vector<int> &d, vector<int> &parent_index, int index1, int index2)
	{
		if (d[index2] > d[index1] + g.IsLinked(index1, index2).second->Weight)
		{
			d[index2] = d[index1] + g.IsLinked(index1, index2).second->Weight;
			parent_index[index2] = index1;
		}
	}

	/// Bellman-Ford���·���㷨
	template<typename T>
	bool BellmanFord(GraphicsViaAdjacencyList<T> &g, int start_index, vector<int> &d, vector<int> &parent_index)
	{
		auto edges = g.GetAllEdges();

		InitializeSingleSource(g, d, parent_index, start_index);		

		for (size_t i = 0; i < g.GetVertex().size() - 1; ++i)
		{			
			for_each(edges.begin(), edges.end(), [&](pair<size_t, size_t> const &p){
				Relax(g, d, parent_index, p.first, p.second);
			});
		}

		for (size_t i = 0; i < edges.size(); ++i)
		{
			if (d[edges[i].second] > d[edges[i].first] + g.IsLinked(edges[i].first, edges[i].second).second->Weight)
			{
				cout << "���ڸ�ֵ��·" << endl;
				return false;
			}
		}

		return true;
	}
}