#pragma once
#include "node.h"
#include <iostream>

class Stack
{
private:
	Node* m_pHead;
	int m_Size;
	int m_NumElement;

public:
	Stack();
	~Stack();

	void SetSize(int n); // ���� ������ ����
	bool IsEmpty(); // ������ �����
	bool IsFull();
	bool Push(Node* pNode); // ������ �� �տ� ��� ����
	Node* Pop(); // �� �� ��� ��ȯ
	void PrintStack(); // ���� ���������� ���
};