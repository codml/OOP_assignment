#include <iostream>
#include "node.h"
using namespace std;

void make_list(char *buf, Node* head) // 표준 입력으로 받은 p1, p2를 리스트로 만듦
{
	int j;
	char node_buf[50];
	Node* tmp;

	for (int i = 0; buf[i]; i++)
	{
		for (j = i; buf[i] && buf[i] != ' '; i++)
			node_buf[i - j] = buf[i]; // 공백 단위로 문자열 생성
		node_buf[i - j] = 0; // 널 문자 추가
		tmp = new Node(node_buf); // 파싱한 문자열로 새 노드 생성
		head->add_node_s(tmp); // p1 or p2에 추가
		if (!buf[i])
			i--; // for문 마지막에 i++가 실행되므로 i가 마지막 인덱스라면 1 감소시켜 에러 막기
	}
}

void Merge_list(Node* p1, Node* p2, Node* p3)
{
	Node* last;

	last = p3; // p3는 더미 노드
	while (p1 && p2)
	{
		if (p1->nodcmp(p2)) // p1이 후순위라면
		{
			last->add_node(p2); // p2 추가
			p2 = p2->next_node(); // p2 맨 앞노드 제거
		}
		else
		{
			last->add_node(p1);
			p1 = p1->next_node();
		}
		last = last->next_node(); // last 노드 갱신
		// 여기서 이전에 p3에 추가한 노드와 p1, p2 리스트와의 연결이 완전히 끊김
	}
	while (p1) // p1이 남아있으면
	{
		last->add_node(p1); // p1 노드 추가
		last = last->next_node();
		p1 = p1->next_node();
	}
	while (p2)
	{
		last->add_node(p2);
		last = last->next_node();
		p2 = p2->next_node();
	}
}

int main()
{
	Node* p1;
	Node* p2;
	Node* p3;
	Node* tmp;
	char buf[1000];

	p1 = new Node();
	p2 = new Node();
	p3 = new Node(); // 간편한 sort를 위해 dummy node 생성
	cout << "Input>>" << endl;
	cout << "Input list 1: ";
	cin.getline(buf, 1000); // 공백을 받기 위해 getline으로 입력받기
	make_list(buf, p1);
	cout << "Input list 2: ";
	cin.getline(buf, 1000);
	make_list(buf, p2);
	tmp = p1;
	p1 = p1->next_node();
	delete tmp;
	tmp = p2;
	p2 = p2->next_node();
	delete tmp; // 두 리스트의 dummy node를 제거
	Merge_list(p1, p2, p3);
	cout << "Output>>" << endl;
	cout << "Result: ";
	p3->print_list();
	while (p3)
	{
		tmp = p3;
		p3 = p3->next_node();
		delete tmp; // 메모리 해제
	}
	return 0;
}