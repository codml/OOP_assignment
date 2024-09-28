#include "node.h"

Node::Node()
{
	m_data = 0;
	m_pNext = 0;
}

Node::~Node()
{
	m_data = 0;
	m_pNext = 0; // ũ�� �ǹ̴� ���� �Ҹ���
}

void Node::SetData(int n)
{
	m_data = n;
}

void Node::SetNext(Node* pNext)
{
	m_pNext = pNext; // ��� ������ ������ ��� �Լ���
}

int Node::GetData()
{
	return m_data;
}

Node* Node::GetNext()
{
	return m_pNext; // ��� ���� ��ȯ
}