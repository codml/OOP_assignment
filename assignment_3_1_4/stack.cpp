#include "stack.h"

Stack::Stack()
{
	m_pHead = 0;
	m_Size = 0;
	m_NumElement = 0;
}

Stack::~Stack()
{
	Node* tmp;

	while (m_pHead)
	{
		tmp = m_pHead;
		m_pHead = m_pHead->GetNext();
		delete tmp; // m_pHead부터 메모리 해제
	}
}

void Stack::SetSize(int n)
{
	m_Size = n;
}

bool Stack::IsEmpty()
{
	if (m_NumElement == 0) // 스택이 비어있으면
		return true;
	else
		return false;
}

bool Stack::IsFull()
{
	if (m_NumElement == m_Size) // 스택의 개수가 최대라면
		return true;
	else
		return false;
}

bool Stack::Push(Node* pNode)
{
	if (IsFull()) // 스택이 꽉 차있으면
		return false;
	pNode->SetNext(m_pHead); // m_pHead가 있으면 맨 앞 추가, 없으면 기존대로 next가 NULL;
	m_pHead = pNode;
	m_NumElement++;
	return true;
}

Node* Stack::Pop()
{
	Node* tmp;

	if (IsEmpty())
		return 0;
	tmp = m_pHead;
	m_pHead = m_pHead->GetNext();
	tmp->SetNext(0);
	m_NumElement--; // 큐의 pop과 같음
	return tmp;
}

void Stack::PrintStack()
{
	for (Node* tmp = m_pHead; tmp; tmp = tmp->GetNext())
		std::cout << tmp->GetData() << " ";
	std::cout << std::endl;
}