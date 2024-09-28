#include "queue.h"

Queue::Queue()
{
	m_pHead = 0;
	m_pTail = 0; // �����͸� �η� �ʱ�ȭ
	m_Size = 0;
	m_NumElement = 0;
}

Queue::~Queue()
{
	Node* tmp;

	while (m_pHead)
	{
		tmp = m_pHead; // m_pHead���� �޸� ����
		m_pHead = m_pHead->GetNext();
		delete tmp;
	}
}

void Queue::SetSize(int n)
{
	m_Size = n; // ������ ����
}

bool Queue::IsEmpty()
{
	if (m_NumElement == 0) // ���� ������ 0�̸�
		return true;
	else
		return false;
}

bool Queue::IsFull()
{
	if (m_NumElement == m_Size) // ���� ������ ��ü ������� ������
		return true;
	else
		return false;
}

bool Queue::Push(Node* pNode)
{
	if (IsFull()) // ť�� ��������
		return false;
	if (!m_pHead) // ť�� ���������
		m_pHead = pNode;
	else
		m_pTail->SetNext(pNode);
	m_pTail = pNode;
	m_NumElement++; // ���� ī��Ʈ
	return true;
}

Node* Queue::Pop()
{
	Node* tmp;

	if (IsEmpty()) // ť�� ���������
		return 0;
	tmp = m_pHead; // pop�� ��� �ּ� ���
	m_pHead = m_pHead->GetNext();
	tmp->SetNext(0); // ��带 ť���� �и�
	m_NumElement--;
	return tmp;
}

void Queue::PrintQueue()
{
	for (Node* tmp = m_pHead; tmp; tmp = tmp->GetNext())
		std::cout << tmp->GetData() << " "; // m_pHead���� ������ ���
	std::cout << std::endl;
}