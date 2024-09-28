#include <iostream>
#include <cstring>

using namespace std;

typedef struct s_node
{
	int num;
	struct s_node* next;
}t_node; // 스택을 구성하는 노드, 숫자 하나가 담김

void delete_stack(t_node *top)
{
	t_node* tmp, * now;

	for (now = top; now;)
	{
		tmp = now;
		now = now->next;
		delete tmp;
	}
} // 스택을 top 부분부터 메모리 해제시키는 함수

void push(t_node** top, int num)
{
	t_node* ptr = new t_node;

	if (!ptr)
	{
		cout << "push failed" << endl;
		return;
	} // 새 노드를 만들기 위해서는 메모리 할당을 해야함
	// 이것이 실패하면 push 불가!
	ptr->num = num;
	ptr->next = 0;
	ptr->next = *top; // 새 노드가 top을 가리킴
	*top = ptr; // 새 노드가 top이 됨
}

void pop(t_node **top)
{
	if (*top) // 스택에 요소가 있다면
	{
		t_node* tmp = *top;
		*top = (*top)->next; // top을 한칸 아래로 내림
		cout << tmp->num << endl; // 이전 top 출력
		delete tmp; // 이전 top 메모리 해제
	}
}

void top(t_node* top)
{
	cout << top->num << endl;
} // top 요소 출력

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
	} // 제가 만든 스택은 각 노드가 아래 노드를 가리킵니다
	// 따라서 바닥에 있는 노드부터 출력이 어렵습니다.
	// 그래서 스택을 위부터 아래로 계속 내려 가장 밑 요소를 출력 후
	// 그 요소의 주소를 저장해 다음 반복문을 돌 때
	// 전에 출력한 요소의 한칸 위 요소를 출력하게 함
	cout << endl;
}

int empty(t_node* top)
{
	if (top)
		return (0);
	else
		return (1);
} // 스택이 비어있으면 == 스택의 맨 위를 가리키는 포인터 top이 NULL이면

int main()
{
	t_node* top_node;
	char cmd[10];
	int push_num;

	top_node = 0; // 스택 생성 전 포인터 초기화
	while (1)
	{
		cout << "write command: ";
		cin >> cmd;
		if (!strcmp(cmd, "push"))
		{
			cin >> push_num; // 이전 입력이 "push"이면 push할 숫자도 받아야 함
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
	delete_stack(top_node); // 메모리 해제
	return (0);
}