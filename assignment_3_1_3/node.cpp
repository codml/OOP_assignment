#include "node.h"

Node::Node()
{
	m_data = 0;
	m_pNext = 0;
}

Node::~Node()
{
	m_data = 0;
	m_pNext = 0; // 만약 m_pNext를 delete 하면 이중 free가 되므로 안 됨
}

void Node::SetData(int n)
{
	m_data = n; // m_data에 카피
}

void Node::SetNext(Node* pNext)
{
	m_pNext = pNext; // m_pNext에 카피
}

int Node::GetData()
{
	return m_data; // m_data 반환
}

Node* Node::GetNext()
{
	return m_pNext; // m_pNext 반환
}