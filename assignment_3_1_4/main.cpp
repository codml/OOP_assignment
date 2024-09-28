#include "stack.h"

using namespace std;

int main()
{
	Node* tmp;
	Stack a;
	char cmd[100];
	int data;

	cout << "set stack size: ";
	cin >> data;
	a.SetSize(data);
	while (1)
	{
		cout << "write command: ";
		cin >> cmd;
		if (!strcmp(cmd, "push"))
		{
			cin >> data;
			tmp = new Node;
			tmp->SetData(data);
			if (!(a.Push(tmp))) // push 실패 -> 스택이 꽉 참
			{
				cout << "full of stack" << endl;
				delete tmp;
			}
		}
		else if (!strcmp(cmd, "pop"))
		{
			tmp = a.Pop();
			if (!tmp) // pop 실패 -> 스택이 비어있음
				cout << "empty stack" << endl;
			else
				cout << tmp->GetData() << endl;
			delete tmp;
		}
		else if (!strcmp(cmd, "print"))
		{
			a.PrintStack();
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
			break;
		else
			cout << "invalid input" << endl;
	}
	return 0;
}