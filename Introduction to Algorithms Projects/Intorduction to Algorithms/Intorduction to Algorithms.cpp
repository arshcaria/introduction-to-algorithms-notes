// Intorduction to Algorithms.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

namespace chapter6
{
int test();
}
namespace chapter7
{
int test();
}
namespace chapter8
{
int test();
}
namespace chapter9
{
int test();
}
namespace chapter11
{
int test();
}
namespace chapter12
{
int test();
}
namespace chapter13
{
int test();
}
namespace chapter15
{//��̬�滮

void AssembleDispatch();				//װ���ߵ���
void MatrixListMultiply();				//�������˷�
int LongestCommonSubsequence();			//�����������
void BestBinarySearchTree();			//���Ŷ��������
void NeatlyPrint();						//�����ӡ
void PlanParty();						//�ۻ�ƻ�
void BitonicTour();						//˫���ó�

}


int _tmain( int argc, _TCHAR* argv[] )
{
    //chapter13::test();
    chapter15::BitonicTour();
	int a[2][2] ={{1,2},{2,3}};
    return 0;
}

