#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

typedef struct s_buff_list
{
	char                buf[100];
	struct s_buff_list* next;
}   buff_list; // 파일명들을 저장할 링크드리스트

void	make_buff_list(ifstream& fin, buff_list** head); // 파일명들을 읽어 리스트에 저장
char	**read_wildcards(void); // wildcard 패턴이 포함된 문자열을 받아 2차원 배열로 할당
int		ptrlen_star(char* ptr); // 널문자나 '*'까지의 문자열 길이 반환
int		strncmp_q(char* s1, char* s2, int n); // 파일명과 wildcard 패턴 중 일부를 비교
void	find_w_line(char* str, char* ptr); // 파일명 하나, wildcard 패턴 하나를 비교해 일치 여부 확인
void	find_wildcards(buff_list* head, char** pptr); // 파일명들과 wildcard 패턴들을 비교
void	free_all(buff_list* head, char** pptr); // 파일명 리스트, wildcard 2차원 배열을 해제

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
		cout << "no" << endl; // 입력받은 filename이 존재하지 않으면 fin == 0
	else
	{
		make_buff_list(fin, &head);
		pptr = read_wildcards();
		find_wildcards(head, pptr);
	}
	free_all(head, pptr);
	fin.close(); // stream 닫기
	return (0);
}

void	make_buff_list(ifstream& fin, buff_list** head)
{
	buff_list* node; // 파일명 하나씩 읽을 때마다 추가되는 노드
	buff_list* tmp; // 리스트의 가장 마지막 노드를 가리키는 포인터

	tmp = *head;
	while (!fin.eof()) // 파일을 다 읽을 때까지 반복
	{
		node = new buff_list; // 새 노드 할당
		fin.getline(node->buf, 100); // 파일 한줄 읽기
		node->next = 0;
		if (*head) // head가 있으면 맨 뒤에 새 노드 삽입
		{
			tmp->next = node;
			tmp = node;
		}
		else // head가 없으면 새 노드를 head로 하고 main의 head에도 주소 전달(포인터로)
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

	cin >> cnt; // 몇 개의 wildcard 패턴을 읽을 지 입력받음
	pptr = new char* [cnt + 1]; // wildcard 패턴을 저장할 배열
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
	// 문자 하나씩 비교하는데, s2(wildcard pattern)이 '?'이면 비교하지 않고
	// 다음 문자로 넘어간다!
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
		while (ptr[a] == '*' && ptr[a]) // '*'가 아닌 문자를 만날 때까지 패턴 읽기
			a++;
		if (!str[b] && ptr[a])	// '*'가 아닌 문자(비교 대상)가 있는데, 파일명을
			return;				// 이미 다 읽었다면 일치하지 않음
		while (str[b])
		{
			if (!a && strncmp_q(str, ptr, ptrlen_star(ptr)))
				return; // 패턴의 첫부분이 '*'가 아니면 파일명의 첫부분과 무조건 같아야 함!
			if (str[b] == ptr[a] || ptr[a] == '?')
			{
				// 파일명의 부분과 wildcard의 '*'를 제외하는 부분이 겹치는 지 확인하는 검사
				// 파일명과 wildcard를 앞에서부터 읽으므로, 순서 걱정 X
				if (!strncmp_q(str + b, ptr + a,
					ptrlen_star(ptr + a)))
				{
					b += ptrlen_star(ptr + a); // wildcard 패턴과 겹치는 부분을 건너뛰고 다음 읽기 시작 
					break;
				}
			}
			b++;
			if (!str[b] && ptr[a]) // 파일명을 끝까지 다 읽었는데 비교할 부분이 남았다..? -> 일치 X
				return;
		}
		while (ptr[a] != '*' && ptr[a])
			a++; // '*'인 부분을 만날 때까지 이동
		if (str[b] && !ptr[a])
			return; // 패턴을 다 읽었는데 문자열이 남아있을 때
	}
	cout << str << endl; // 여기까지 왔다는 것은 일치하다는 것이므로 출력
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
	} // 리스트를 돌며 노드 하나씩 메모리 해제
	if (pptr)
	{
		for (int i = 0; pptr[i]; i++)
			delete[] pptr[i];
		// pptr[i]가 가리키는 각 문자열 메모리 해제
		delete[] pptr;
	}
}
