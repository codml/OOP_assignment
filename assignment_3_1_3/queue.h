#pragma once
#include "node.h"
#include <iostream>

class Queue
{
private:
	Node* m_pHead; // 큐의 맨 앞 노드를 가리킴
	Node* m_pTail; // 큐의 맨 뒤 노드를 가리킴
	int m_Size; // 큐의 전체 사이즈
	int m_NumElement; // 큐의 현재 사이즈

public:
	Queue();
	~Queue();

	void SetSize(int n); // 큐의 전체 사이즈 설정
	bool IsEmpty(); // 큐가 비었나
	bool IsFull(); // 큐가 꽉 찼나
	bool Push(Node* pNode); // 노드를 큐에 삽입
	Node* Pop(); // 노드를 큐에서 제거
	void PrintQueue(); // 전체 큐 출력
};