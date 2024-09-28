#include "node.h"

Node::Node()
{
	m_data = 0;
	m_pNext = 0;
}

Node::~Node()
{
	m_data = 0;
	m_pNext = 0; // ���� m_pNext�� delete �ϸ� ���� free�� �ǹǷ� �� ��
}

void Node::SetData(int n)
{
	m_data = n; // m_data�� ī��
}

void Node::SetNext(Node* pNext)
{
	m_pNext = pNext; // m_pNext�� ī��
}

int Node::GetData()
{
	return m_data; // m_data ��ȯ
}

Node* Node::GetNext()
{
	return m_pNext; // m_pNext ��ȯ
}