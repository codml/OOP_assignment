#include <iostream>
#include <cstring>

using namespace std;

typedef struct s_node
{
	int num;
	struct s_node* next;
}t_node; // ������ �����ϴ� ���, ���� �ϳ��� ���

void delete_stack(t_node *top)
{
	t_node* tmp, * now;

	for (now = top; now;)
	{
		tmp = now;
		now = now->next;
		delete tmp;
	}
} // ������ top �κк��� �޸� ������Ű�� �Լ�

void push(t_node** top, int num)
{
	t_node* ptr = new t_node;

	if (!ptr)
	{
		cout << "push failed" << endl;
		return;
	} // �� ��带 ����� ���ؼ��� �޸� �Ҵ��� �ؾ���
	// �̰��� �����ϸ� push �Ұ�!
	ptr->num = num;
	ptr->next = 0;
	ptr->next = *top; // �� ��尡 top�� ����Ŵ
	*top = ptr; // �� ��尡 top�� ��
}

void pop(t_node **top)
{
	if (*top) // ���ÿ� ��Ұ� �ִٸ�
	{
		t_node* tmp = *top;
		*top = (*top)->next; // top�� ��ĭ �Ʒ��� ����
		cout << tmp->num << endl; // ���� top ���
		delete tmp; // ���� top �޸� ����
	}
}

void top(t_node* top)
{
	cout << top->num << endl;
} // top ��� ���

void print(t_node* top)
{
	t_node* prev = 0;
	t_node* now = 0;

	while (prev != top)
	{
		now = top;
		while (now->next != prev)
			now = now->next;
		cout << now->num << " ";
		prev = now;
	} // ���� ���� ������ �� ��尡 �Ʒ� ��带 ����ŵ�ϴ�
	// ���� �ٴڿ� �ִ� ������ ����� ��ƽ��ϴ�.
	// �׷��� ������ ������ �Ʒ��� ��� ���� ���� �� ��Ҹ� ��� ��
	// �� ����� �ּҸ� ������ ���� �ݺ����� �� ��
	// ���� ����� ����� ��ĭ �� ��Ҹ� ����ϰ� ��
	cout << endl;
}

int empty(t_node* top)
{
	if (top)
		return (0);
	else
		return (1);
} // ������ ��������� == ������ �� ���� ����Ű�� ������ top�� NULL�̸�

int main()
{
	t_node* top_node;
	char cmd[10];
	int push_num;

	top_node = 0; // ���� ���� �� ������ �ʱ�ȭ
	while (1)
	{
		cout << "write command: ";
		cin >> cmd;
		if (!strcmp(cmd, "push"))
		{
			cin >> push_num; // ���� �Է��� "push"�̸� push�� ���ڵ� �޾ƾ� ��
			push(&top_node, push_num);
		}
		else if (!strcmp(cmd, "pop"))
			pop(&top_node);
		else if (!strcmp(cmd, "top"))
			top(top_node);
		else if (!strcmp(cmd, "print"))
			print(top_node);
		else if (!strcmp(cmd, "empty"))
			cout << empty(top_node) << endl;
		else if (!strcmp(cmd, "exit"))
			break;
	}
	delete_stack(top_node); // �޸� ����
	return (0);
}