#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

typedef struct s_buff_list
{
	char                buf[100];
	struct s_buff_list* next;
}   buff_list; // ���ϸ���� ������ ��ũ�帮��Ʈ

void	make_buff_list(ifstream& fin, buff_list** head); // ���ϸ���� �о� ����Ʈ�� ����
char	**read_wildcards(void); // wildcard ������ ���Ե� ���ڿ��� �޾� 2���� �迭�� �Ҵ�
int		ptrlen_star(char* ptr); // �ι��ڳ� '*'������ ���ڿ� ���� ��ȯ
int		strncmp_q(char* s1, char* s2, int n); // ���ϸ�� wildcard ���� �� �Ϻθ� ��
void	find_w_line(char* str, char* ptr); // ���ϸ� �ϳ�, wildcard ���� �ϳ��� ���� ��ġ ���� Ȯ��
void	find_wildcards(buff_list* head, char** pptr); // ���ϸ��� wildcard ���ϵ��� ��
void	free_all(buff_list* head, char** pptr); // ���ϸ� ����Ʈ, wildcard 2���� �迭�� ����

int main()
{
	ifstream    fin;
	char		file_name[100];
	buff_list* head;
	char** pptr;

	head = 0;
	pptr = 0;
	cout << "Input file name: ";
	cin >> file_name;
	fin.open(file_name);
	if (!fin)
		cout << "no" << endl; // �Է¹��� filename�� �������� ������ fin == 0
	else
	{
		make_buff_list(fin, &head);
		pptr = read_wildcards();
		find_wildcards(head, pptr);
	}
	free_all(head, pptr);
	fin.close(); // stream �ݱ�
	return (0);
}

void	make_buff_list(ifstream& fin, buff_list** head)
{
	buff_list* node; // ���ϸ� �ϳ��� ���� ������ �߰��Ǵ� ���
	buff_list* tmp; // ����Ʈ�� ���� ������ ��带 ����Ű�� ������

	tmp = *head;
	while (!fin.eof()) // ������ �� ���� ������ �ݺ�
	{
		node = new buff_list; // �� ��� �Ҵ�
		fin.getline(node->buf, 100); // ���� ���� �б�
		node->next = 0;
		if (*head) // head�� ������ �� �ڿ� �� ��� ����
		{
			tmp->next = node;
			tmp = node;
		}
		else // head�� ������ �� ��带 head�� �ϰ� main�� head���� �ּ� ����(�����ͷ�)
		{
			*head = node;
			tmp = node;
		}
	}
}

char** read_wildcards(void)
{
	char** pptr;
	int		cnt;

	cin >> cnt; // �� ���� wildcard ������ ���� �� �Է¹���
	pptr = new char* [cnt + 1]; // wildcard ������ ������ �迭
	for (int i = 0; i < cnt; i++)
	{
		pptr[i] = new char[100];
		cin >> pptr[i];
	}
	pptr[cnt] = 0;
	return (pptr);
}

int	ptrlen_star(char* ptr)
{
	int	i;

	i = 0;
	while (ptr[i] && ptr[i] != '*')
		i++;
	return (i);
}

int	strncmp_q(char* s1, char* s2, int n)
{
	int	i;
	// ���� �ϳ��� ���ϴµ�, s2(wildcard pattern)�� '?'�̸� ������ �ʰ�
	// ���� ���ڷ� �Ѿ��!
	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s2[i] != '?' && s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

void	find_w_line(char* str, char* ptr)
{
	int a, b;

	a = 0;
	b = 0;
	while (ptr[a])
	{
		while (ptr[a] == '*' && ptr[a]) // '*'�� �ƴ� ���ڸ� ���� ������ ���� �б�
			a++;
		if (!str[b] && ptr[a])	// '*'�� �ƴ� ����(�� ���)�� �ִµ�, ���ϸ���
			return;				// �̹� �� �о��ٸ� ��ġ���� ����
		while (str[b])
		{
			if (!a && strncmp_q(str, ptr, ptrlen_star(ptr)))
				return; // ������ ù�κ��� '*'�� �ƴϸ� ���ϸ��� ù�κа� ������ ���ƾ� ��!
			if (str[b] == ptr[a] || ptr[a] == '?')
			{
				// ���ϸ��� �κа� wildcard�� '*'�� �����ϴ� �κ��� ��ġ�� �� Ȯ���ϴ� �˻�
				// ���ϸ�� wildcard�� �տ������� �����Ƿ�, ���� ���� X
				if (!strncmp_q(str + b, ptr + a,
					ptrlen_star(ptr + a)))
				{
					b += ptrlen_star(ptr + a); // wildcard ���ϰ� ��ġ�� �κ��� �ǳʶٰ� ���� �б� ���� 
					break;
				}
			}
			b++;
			if (!str[b] && ptr[a]) // ���ϸ��� ������ �� �о��µ� ���� �κ��� ���Ҵ�..? -> ��ġ X
				return;
		}
		while (ptr[a] != '*' && ptr[a])
			a++; // '*'�� �κ��� ���� ������ �̵�
		if (str[b] && !ptr[a])
			return; // ������ �� �о��µ� ���ڿ��� �������� ��
	}
	cout << str << endl; // ������� �Դٴ� ���� ��ġ�ϴٴ� ���̹Ƿ� ���
}

void	find_wildcards(buff_list* head, char **pptr)
{
	buff_list* tmp;

	for (int i = 0; pptr[i]; i++)
	{
		for (tmp = head; tmp; tmp = tmp->next)
			find_w_line(tmp->buf, pptr[i]);
	}
}

void	free_all(buff_list* head, char** pptr)
{
	buff_list* tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	} // ����Ʈ�� ���� ��� �ϳ��� �޸� ����
	if (pptr)
	{
		for (int i = 0; pptr[i]; i++)
			delete[] pptr[i];
		// pptr[i]�� ����Ű�� �� ���ڿ� �޸� ����
		delete[] pptr;
	}
}
