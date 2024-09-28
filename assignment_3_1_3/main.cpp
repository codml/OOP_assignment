#include <iostream>
#include <cstring>
#include "queue.h"

using namespace std;

int main()
{
	Node* tmp;
	Queue a;
	char cmd[100];
	int data;

	cout << "set queue size: ";
	cin >> data;
	a.SetSize(data); // ť ������ ����
	while (1)
	{
		cout << "write command: ";
		cin >> cmd; // ��ɾ� �Է�
		if (!strcmp(cmd, "push"))
		{
			cin >> data; // ��带 ������ ������
			tmp = new Node;
			tmp->SetData(data);
			if (!(a.Push(tmp))) // ť�� �� ��������
			{
				cout << "full of queue" << endl;
				delete tmp; // ��� �޸� ����
			}
		}
		else if (!strcmp(cmd, "pop"))
		{
			tmp = a.Pop();
			if (!tmp) // ť�� ���������
				cout << "empty queue" << endl;
			else
				cout << tmp->GetData() << endl; // pop�� ��� ���� ���
			delete tmp; // ��� �޸� ����
		}
		else if (!strcmp(cmd, "print"))
		{
			a.PrintQueue();
		}
		else if (!strcmp(cmd, "isempty"))
		{
			if (a.IsEmpty())
				cout << "yes" << endl;
			else
				cout << "no" << endl;
		}
		else if (!strcmp(cmd, "isfull"))
		{
			if (a.IsFull())
				cout << "yes" << endl;
			else
				cout << "no" << endl;
		}
		else if (!strcmp(cmd, "exit"))
			break; // �ݺ��� Ż��
		else
			cout << "invalid input" << endl; // ��ɾ�� ����ġ�� �Է�
	}
	return 0;
}