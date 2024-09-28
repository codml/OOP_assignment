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
	a.SetSize(data); // 큐 사이즈 지정
	while (1)
	{
		cout << "write command: ";
		cin >> cmd; // 명령어 입력
		if (!strcmp(cmd, "push"))
		{
			cin >> data; // 노드를 구성할 데이터
			tmp = new Node;
			tmp->SetData(data);
			if (!(a.Push(tmp))) // 큐가 꽉 차있으면
			{
				cout << "full of queue" << endl;
				delete tmp; // 노드 메모리 해제
			}
		}
		else if (!strcmp(cmd, "pop"))
		{
			tmp = a.Pop();
			if (!tmp) // 큐가 비어있으면
				cout << "empty queue" << endl;
			else
				cout << tmp->GetData() << endl; // pop된 노드 정보 출력
			delete tmp; // 노드 메모리 해제
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
			break; // 반복문 탈출
		else
			cout << "invalid input" << endl; // 명령어와 불일치한 입력
	}
	return 0;
}