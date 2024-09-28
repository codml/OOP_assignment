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
		delete tmp; // m_pHead���� �޸� ����
	}
}

void Stack::SetSize(int n)
{
	m_Size = n;
}

bool Stack::IsEmpty()
{
	if (m_NumElement == 0) // ������ ���������
		return true;
	else
		return false;
}

bool Stack::IsFull()
{
	if (m_NumElement == m_Size) // ������ ������ �ִ���
		return true;
	else
		return false;
}

bool Stack::Push(Node* pNode)
{
	if (IsFull()) // ������ �� ��������
		return false;
	pNode->SetNext(m_pHead); // m_pHead�� ������ �� �� �߰�, ������ ������� next�� NULL;
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
	m_NumElement--; // ť�� pop�� ����
	return tmp;
}

void Stack::PrintStack()
{
	for (Node* tmp = m_pHead; tmp; tmp = tmp->GetNext())
		std::cout << tmp->GetData() << " ";
	std::cout << std::endl;
}