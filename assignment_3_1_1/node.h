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
	Node(); // ptr�� �� �����͸� ������ �Ǵ� ������
	Node(const char* ptr); // this->ptr�� ���ڿ��� ������ ������
	~Node();

	Node* next_node(); // next ��� ������ ��ȯ��
	int nodcmp(Node* nod2); // nod2�� ptr�� ��ҹ��� ���� ���� ���ڿ� �� ����
	void add_node(Node* nod); // ��� �ڿ� nod ���̱�
	void add_node_s(Node* nod); // �ش� �ν��Ͻ��� head�� ������ ����Ʈ�� ���ĵ� ��ġ�� nod ����
	void print_list(); // �ش� �ν��Ͻ��� head�� ������ ����Ʈ ���
};