/// ͼ�ı�ʾ��
/// 
/// ͼ�����ֱ�ʾ��������1���ڽӱ�����2���ڽӾ���
/// 


#include <vector>
using std::vector;

namespace chapter22
{
	/// ͼ�����ͣ�����ͼ��������ͼ
	enum GraphicsType
	{
		Digraph,			///< ����ͼ
		Undigraph			///< ����ͼ
	};

	/// ʹ���ڽӱ���ʾһ��ͼ
	template<typename T>
	class GraphicsViaAdjacencyList
	{
	public:
		/// �ڽӱ��ϵ�һ�����
		struct AdjacencyList
		{
			T				Item;		///< ����ı�ʶ
			AdjacencyList	*Next;		///< ָ����һ�����
		};

	public:
		/// ͨ���������ʼ��һ��ͼ
		GraphicsViaAdjacencyList(vector<T> const &v, GraphicsType type) : _v(v), _e(v.size(), NULL), _type(type)
		{

		}

		~GraphicsViaAdjacencyList()
		{
			for_each(_e.begin(), _e.end(), [](AdjacencyList *e){
				while (e)
				{
					AdjacencyList *temp = e;
					e = e->Next;
					delete temp;
				}
			});
		}


		/// ��ʶͼ���������֮����һ����
		void Link2Vertex(size_t index1, size_t index2)
		{
			AdjacencyList *node = new AdjacencyList();
			node->Item = _v[index2];
			node->Next = _e[index1];
			_e[index1] = node;

			if (_type == Undigraph)
			{
				//����ͼ
				node = new AdjacencyList();
				node->Item = _v[index1];
				node->Next = _e[index2];
				_e[index2] = node;
			}
		}

		/// ��ѯ���������Ƿ�����
		bool IsLinked(size_t index1, size_t index2) const
		{
			AdjacencyList *l = _e[index1];
			while(l)
			{
				if (l->Item == _v[index2])
				{
					return true;
				}
				l = l->Next;
			}
			return false;
		}

		inline vector<T> & GetVertex()				{return _v;}
		inline vector<AdjacencyList *> & GetEdge()	{return _e;}

	
	private:
		vector<T>				_v;		///< ͼ�Ķ���ļ���
		vector<AdjacencyList *>	_e;		///< ͼ�ıߣ����ڽӱ�
		GraphicsType			_type;	///< ͼ������
	};


	/// ʹ���ڽӾ�������ʾһ��ͼ
	template<typename VT, typename ET>
	class GrpahicsViaAdjacencyMatrix
	{
	public:
		GrpahicsViaAdjacencyMatrix(vector<VT> const &v, GraphicsType type = Digraph) : _v(v), _e(v.size(), vector<ET>(v.size())), _type(type)
		{

		}

		GrpahicsViaAdjacencyMatrix(vector<VT> const &v, vector<vector<ET>> const &e, GraphicsType type = Digraph) : _v(v), _e(e), _type(type)
		{
			assert(e.size() == v.size() && e[0].size() == v.size());
		}

		void Link2Vertex(size_t index1, size_t index2, ET weight)
		{
			_e[index1][index2] = weight;
			if (_type == Undigraph)
			{
				_e[index2][index1] = weight;
			}
		}

	
	private:
		vector<VT>				_v;		///< ͼ�Ķ���ļ���
		vector<vector<ET>>		_e;		///< ͼ�ıߣ����ڽӾ���
		GraphicsType			_type;	///< ͼ������
	};

}