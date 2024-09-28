#include "node.h"

Node::Node()
{
	this->ptr = 0;
	this->next = 0;
}

Node::Node(const char* ptr)
{
	this->ptr = new char[strlen(ptr) + 1]; // 문자열 공간 할당
	strcpy(this->ptr, ptr); // 문자열 복사
	this->next = 0;
}

Node::~Node()
{
	delete[] ptr;
}

Node* Node::next_node()
{
	return this->next;
}

int Node::nodcmp(Node* nod2)
{
	char ch1, ch2;
	int i;

	for (i = 0; this->ptr[i] && nod2->ptr[i]; i++)
	{
		if (this->ptr[i] > 'Z')
			ch1 = this->ptr[i] - 32;
		else
			ch1 = this->ptr[i]; // 비교할 문자를 대문자로 변환
		if (nod2->ptr[i] > 'Z')
			ch2 = nod2->ptr[i] - 32;
		else
			ch2 = nod2->ptr[i]; // 비교할 문자를 대문자로 변환(2)
		if (ch1 > ch2)
			return 1; // this->ptr이 후순위라면 1 반환
		else if (ch1 < ch2)
			return 0; // 그게 아니라면 0 반환
	}
	if (this->ptr[i])
		return 1; // this->ptr이 아직 남아있다면 후순위이므로 1 반환 
	else
		return 0;
}

void Node::add_node(Node* nod)
{
	this->next = nod;
}

void Node::add_node_s(Node* nod)
{
	Node* prev;
	Node* tmp;

	prev = this;
	for (tmp = this->next; tmp; prev = tmp, tmp = tmp->next)
	{// p1, p2는 더미 노드로 시작하므로 tmp를 this->next부터 시작
		if (tmp->nodcmp(nod)) // prev와 tmp 사이에 nod를 넣어야 한다면
		{
			nod->next = prev->next; // prev의 다음(tmp)을 nod의 다음이 가리키도록
			prev->next = nod; // prev의 다음이 nod를 가리키도록
			return; // 정렬 삽입 끝
		}
	}
	prev->next = nod; // 마지막까지 왔다면 마지막 노드 뒤에 nod 삽입
}

void Node::print_list()
{
	for (Node* tmp = this; tmp; tmp = tmp->next)
	{
		if (tmp->ptr) // 더미 노드를 제외하고 출력
			std::cout << tmp->ptr << " ";
	}
	std::cout << std::endl;
}