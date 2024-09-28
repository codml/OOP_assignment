#include "queue.h"

Queue::Queue()
{
	m_pHead = 0;
	m_pTail = 0; // 포인터를 널로 초기화
	m_Size = 0;
	m_NumElement = 0;
}

Queue::~Queue()
{
	Node* tmp;

	while (m_pHead)
	{
		tmp = m_pHead; // m_pHead부터 메모리 해제
		m_pHead = m_pHead->GetNext();
		delete tmp;
	}
}

void Queue::SetSize(int n)
{
	m_Size = n; // 사이즈 지정
}

bool Queue::IsEmpty()
{
	if (m_NumElement == 0) // 현재 개수가 0이면
		return true;
	else
		return false;
}

bool Queue::IsFull()
{
	if (m_NumElement == m_Size) // 현재 개수가 전체 사이즈와 같으면
		return true;
	else
		return false;
}

bool Queue::Push(Node* pNode)
{
	if (IsFull()) // 큐가 차있으면
		return false;
	if (!m_pHead) // 큐가 비어있으면
		m_pHead = pNode;
	else
		m_pTail->SetNext(pNode);
	m_pTail = pNode;
	m_NumElement++; // 개수 카운트
	return true;
}

Node* Queue::Pop()
{
	Node* tmp;

	if (IsEmpty()) // 큐가 비어있으면
		return 0;
	tmp = m_pHead; // pop할 노드 주소 기억
	m_pHead = m_pHead->GetNext();
	tmp->SetNext(0); // 노드를 큐에서 분리
	m_NumElement--;
	return tmp;
}

void Queue::PrintQueue()
{
	for (Node* tmp = m_pHead; tmp; tmp = tmp->GetNext())
		std::cout << tmp->GetData() << " "; // m_pHead부터 끝까지 출력
	std::cout << std::endl;
}