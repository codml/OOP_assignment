#include "node.h"

Node::Node()
{
	m_data = 0;
	m_pNext = 0;
}

Node::~Node()
{
	m_data = 0;
	m_pNext = 0; // 크게 의미는 없는 소멸자
}

void Node::SetData(int n)
{
	m_data = n;
}

void Node::SetNext(Node* pNext)
{
	m_pNext = pNext; // 멤버 변수의 변경은 멤버 함수로
}

int Node::GetData()
{
	return m_data;
}

Node* Node::GetNext()
{
	return m_pNext; // 멤버 변수 반환
}