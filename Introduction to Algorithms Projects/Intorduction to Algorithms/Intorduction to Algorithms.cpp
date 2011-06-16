// Intorduction to Algorithms.cpp : �������̨Ӧ�ó������ڵ㡣
//



#include <iostream>

namespace ita
{
	//��6�£�������
    int testHeapSort();

	//��7�£���������
    int testQuickSort();

	//��8�£�����ʱ������
    int testLinearSort();

	//��9�£���λ����˳��ͳ��ѧ
    int testNthElement();

	//��11�£�ɢ�б�
    int testHashTable();

	//��12�£����������
    int testBinarySearchTree();

	//��13�£������
    int testRedBlackTree();

	//��15�£���̬�滮
    void AssembleDispatch();				//װ���ߵ���
    void MatrixListMultiply();				//�������˷�
    int LongestCommonSubsequence();			//�����������
    void BestBinarySearchTree();			//���Ŷ��������
    void NeatlyPrint();						//�����ӡ
    void PlanParty();						//�ۻ�ƻ�
    void BitonicTour();						//˫���ó�

	//��16�£�̰���㷨
    void HuffmanCode();						//����������

	//��18�£�B��
	void testBTree();

	//��19�£������
	void testBinomialHeaps();

	//��20�£�쳲�������
	int testFibonacciHeap();				 

	//��21�£����ڲ��ཻ���ϵ����ݽṹ�����鼯��
	void testDisjointSetForest();

	//��22�£�ͼ�Ļ����㷨 
	void BFS_And_DFS();						//���&������ȱ���
	void TopologicalSort();					//��������
	void StronglyConnectedComponent();		//ǿ��ͨ��֧

	//��23�£���С������
	void Kruskal();
	void Prim();

	//��24�£���Դ���·��
	bool testBellmanFord();
	void testDijkstra();

	//��25�£�ÿ�Զ��������·��
	void FloydWarshall();
	void Johnson();

	//��26�£������
	void testFordFulkerson();
}

int _tmain( int argc, _TCHAR* argv[] )
{
    ita::testHeapSort();
    return 0;
}

