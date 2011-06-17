//////////////////////////////////////////////////////////////////////////  
/// @file		johnson.cpp
/// @brief		Johnsonÿ�Զ��������·���㷨
/// @details	COPYRIGHT NOTICE  
///			    Copyright (c) 2011
///			    All rights reserved.\n
///			    
///  
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2011/06/17
/// @version	1.0 
//////////////////////////////////////////////////////////////////////////  
/// �޸ļ�¼��
/// 2011/06/17   17:42	1.0	̷����	����

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
#include "bellman_ford.h"
#include "dijkstra.h"

using namespace std;



namespace ita
{
	/// Johnsonÿ�Զ��������·���㷨
	void Johnson()
	{
		cout << "Johnson���·��" << endl;
		//����P384ҳ��ͼ25-1
		vector<int> v;
		v.push_back( 1 );
		v.push_back( 2 );
		v.push_back( 3 );
		v.push_back( 4 );
		v.push_back( 5 );
		GraphicsViaAdjacencyList<int> g( v, Digraph );
		g.Link2Vertex( 0, 1, 3 );
		g.Link2Vertex( 0, 2, 8 );
		g.Link2Vertex( 0, 4, -4 );
		g.Link2Vertex( 1, 4, 7 );
		g.Link2Vertex( 1, 3, 1 );
		g.Link2Vertex( 2, 1, 4 );
		g.Link2Vertex( 3, 2, -5 );
		g.Link2Vertex( 3, 0, 2 );
		g.Link2Vertex( 4, 3, 6 );
		int const n = g.GetVertex().size();

		//generate g'
		GraphicsViaAdjacencyList<int> gplus( v, Digraph );
		for (int i = 0; i < g.GetVertex().size(); ++i)
		{
			for (int j = 0; j < g.GetVertex().size(); ++j)
			{
				if (g.IsLinked(i, j).first)
				{
					gplus.Link2Vertex(i, j, g.IsLinked(i, j).second->Weight);
				}
			}
		}
		gplus.GetVertex().push_back(0);
		gplus.GetEdges().push_back(nullptr);
		for (int i = 0; i < g.GetVertex().size(); ++i)
		{
			gplus.Link2Vertex(gplus.GetVertex().size() - 1, i, 0);
		}

		//call bellman-ford algorithm on g'
		vector<int> d(gplus.GetVertex().size());
		vector<int> parent_index(gplus.GetVertex().size());
		if (!BellmanFord(gplus, gplus.GetVertex().size() - 1, d, parent_index))
		{
			cout << "�����Ÿ�ֵ��·���㷨�޷�����" << endl;
			return;
		}

		//re-assign for g
		auto edges = g.GetAllEdges();
		for (int i = 0; i < edges.size(); ++i)
		{
			auto node = g.IsLinked(edges[i].first, edges[i].second).second;
			node->Weight += ( d[edges[i].first] - d[edges[i].second] );
		}

		//loop call dijkstra algorithm on g
		vector<vector<int>> D(n, vector<int>(n));
		for (int i = 0; i < g.GetVertex().size(); ++i)
		{
			vector<int> d2(g.GetVertex().size());
			vector<int> parent_index2(g.GetVertex().size());

			Dijkstra(g, i, d2, parent_index2);

			for (int j = 0; j < g.GetVertex().size(); ++j)
			{
				D[i][j] = d2[j] + d[j] - d[i];
			}
		}

		//display result
		for ( int i = 0; i < n; ++i )
		{
			for ( int j = 0; j < n; ++j )
			{
				cout << D[i][j] << "  ";
			}
			cout << endl;
		}
	}
}