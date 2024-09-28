#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class Node
{
private:
	char* ptr;
	class Node* next;

public:
	Node(); // ptr이 널 포인터를 가지게 되는 생성자
	Node(const char* ptr); // this->ptr이 문자열을 가지고 생성됨
	~Node();

	Node* next_node(); // next 멤버 변수를 반환함
	int nodcmp(Node* nod2); // nod2의 ptr과 대소문자 구분 없이 문자열 비교 수행
	void add_node(Node* nod); // 노드 뒤에 nod 붙이기
	void add_node_s(Node* nod); // 해당 인스턴스를 head로 가지는 리스트에 정렬된 위치로 nod 삽입
	void print_list(); // 해당 인스턴스를 head로 가지는 리스트 출력
};