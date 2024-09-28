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

	void SetSize(int n); // 스택 사이즈 설정
	bool IsEmpty(); // 스택이 비었나
	bool IsFull();
	bool Push(Node* pNode); // 스택의 맨 앞에 노드 삽입
	Node* Pop(); // 맨 앞 노드 반환
	void PrintStack(); // 스택 위에서부터 출력
};