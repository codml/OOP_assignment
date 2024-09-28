#include <iostream>
#include "node.h"
using namespace std;

void make_list(char *buf, Node* head) // ǥ�� �Է����� ���� p1, p2�� ����Ʈ�� ����
{
	int j;
	char node_buf[50];
	Node* tmp;

	for (int i = 0; buf[i]; i++)
	{
		for (j = i; buf[i] && buf[i] != ' '; i++)
			node_buf[i - j] = buf[i]; // ���� ������ ���ڿ� ����
		node_buf[i - j] = 0; // �� ���� �߰�
		tmp = new Node(node_buf); // �Ľ��� ���ڿ��� �� ��� ����
		head->add_node_s(tmp); // p1 or p2�� �߰�
		if (!buf[i])
			i--; // for�� �������� i++�� ����ǹǷ� i�� ������ �ε������ 1 ���ҽ��� ���� ����
	}
}

void Merge_list(Node* p1, Node* p2, Node* p3)
{
	Node* last;

	last = p3; // p3�� ���� ���
	while (p1 && p2)
	{
		if (p1->nodcmp(p2)) // p1�� �ļ������
		{
			last->add_node(p2); // p2 �߰�
			p2 = p2->next_node(); // p2 �� �ճ�� ����
		}
		else
		{
			last->add_node(p1);
			p1 = p1->next_node();
		}
		last = last->next_node(); // last ��� ����
		// ���⼭ ������ p3�� �߰��� ���� p1, p2 ����Ʈ���� ������ ������ ����
	}
	while (p1) // p1�� ����������
	{
		last->add_node(p1); // p1 ��� �߰�
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
	p3 = new Node(); // ������ sort�� ���� dummy node ����
	cout << "Input>>" << endl;
	cout << "Input list 1: ";
	cin.getline(buf, 1000); // ������ �ޱ� ���� getline���� �Է¹ޱ�
	make_list(buf, p1);
	cout << "Input list 2: ";
	cin.getline(buf, 1000);
	make_list(buf, p2);
	tmp = p1;
	p1 = p1->next_node();
	delete tmp;
	tmp = p2;
	p2 = p2->next_node();
	delete tmp; // �� ����Ʈ�� dummy node�� ����
	Merge_list(p1, p2, p3);
	cout << "Output>>" << endl;
	cout << "Result: ";
	p3->print_list();
	while (p3)
	{
		tmp = p3;
		p3 = p3->next_node();
		delete tmp; // �޸� ����
	}
	return 0;
}