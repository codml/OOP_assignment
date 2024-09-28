#pragma once
#include "node.h"
#include <iostream>

class Queue
{
private:
	Node* m_pHead; // ť�� �� �� ��带 ����Ŵ
	Node* m_pTail; // ť�� �� �� ��带 ����Ŵ
	int m_Size; // ť�� ��ü ������
	int m_NumElement; // ť�� ���� ������

public:
	Queue();
	~Queue();

	void SetSize(int n); // ť�� ��ü ������ ����
	bool IsEmpty(); // ť�� �����
	bool IsFull(); // ť�� �� á��
	bool Push(Node* pNode); // ��带 ť�� ����
	Node* Pop(); // ��带 ť���� ����
	void PrintQueue(); // ��ü ť ���
};