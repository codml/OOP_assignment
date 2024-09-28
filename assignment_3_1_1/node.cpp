#include "node.h"

Node::Node()
{
	this->ptr = 0;
	this->next = 0;
}

Node::Node(const char* ptr)
{
	this->ptr = new char[strlen(ptr) + 1]; // ���ڿ� ���� �Ҵ�
	strcpy(this->ptr, ptr); // ���ڿ� ����
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
			ch1 = this->ptr[i]; // ���� ���ڸ� �빮�ڷ� ��ȯ
		if (nod2->ptr[i] > 'Z')
			ch2 = nod2->ptr[i] - 32;
		else
			ch2 = nod2->ptr[i]; // ���� ���ڸ� �빮�ڷ� ��ȯ(2)
		if (ch1 > ch2)
			return 1; // this->ptr�� �ļ������ 1 ��ȯ
		else if (ch1 < ch2)
			return 0; // �װ� �ƴ϶�� 0 ��ȯ
	}
	if (this->ptr[i])
		return 1; // this->ptr�� ���� �����ִٸ� �ļ����̹Ƿ� 1 ��ȯ 
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
	{// p1, p2�� ���� ���� �����ϹǷ� tmp�� this->next���� ����
		if (tmp->nodcmp(nod)) // prev�� tmp ���̿� nod�� �־�� �Ѵٸ�
		{
			nod->next = prev->next; // prev�� ����(tmp)�� nod�� ������ ����Ű����
			prev->next = nod; // prev�� ������ nod�� ����Ű����
			return; // ���� ���� ��
		}
	}
	prev->next = nod; // ���������� �Դٸ� ������ ��� �ڿ� nod ����
}

void Node::print_list()
{
	for (Node* tmp = this; tmp; tmp = tmp->next)
	{
		if (tmp->ptr) // ���� ��带 �����ϰ� ���
			std::cout << tmp->ptr << " ";
	}
	std::cout << std::endl;
}