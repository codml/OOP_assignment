#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

char* from_ten(char* str, int to_base); // 10진수에서 나머지로 바뀔 때
char* to_ten(char* str, int from_base); // 나머지에서 10진수로 바뀔 때
char* from_to_two(char* str, int from_base, int to_base); // from or to 에 2진수가 있을 때
void remove_zero(char* str); // 2진수로 바꾸거나 기타 경우에서 맨 앞에 0이 올 때 0 제거

char else_base[] = "0123456789ABCDEF"; //16진수와 나머지 진수를 표현하기 위한 base

int main()
{
	char input_arr[32];
	int from_base, to_base;
	char* return_arr = 0;
	char* tmp_arr = 0;

	cout << "Input: ";
	cin >> input_arr >> from_base >> to_base;
	if (!strcmp(input_arr, "0"))
	{
		cout << input_arr << endl;
		return (0);
	}
	if (from_base == 10)
		return_arr = from_ten(input_arr, to_base);
	else if (to_base == 10)
		return_arr = to_ten(input_arr, from_base);
	else if (from_base == 2 || to_base == 2)
		return_arr = from_to_two(input_arr, from_base, to_base);
	else
	{
		// 8진수에서 16진수, 혹은 그 반대 경우
		// 중간에 2진수로 바꾸고 그 2진수를 to_base로 전환
		tmp_arr = from_to_two(input_arr, from_base, 2);
		return_arr = from_to_two(tmp_arr, 2, to_base);
		if (tmp_arr)
			delete[]tmp_arr;
	}
	remove_zero(return_arr);
	cout << return_arr << endl;
	if (return_arr)
		delete[]return_arr;
	return (0);
}

void remove_zero(char* str)
{
	int i, j;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != '0')
			break;
	}
	if (i)
	{
		for (j = i; str[j]; j++)
			str[j - i] = str[j];
		str[j - i] = 0;
	}
}

char* from_ten(char* str, int to_base)
{
	int i;
	char tmp;
	int num = atoi(str);
	char* ptr = new char[33];

	memset(ptr, 0, 33);
	for (i = 0; num; num /= to_base, i++)
		ptr[i] = else_base[num % to_base]; // to_base로 계속 나누며 나머지를 기록
	for (int j = 0; j < i / 2; j++)
	{
		tmp = ptr[j];
		ptr[j] = ptr[i - j - 1];
		ptr[i - j - 1] = tmp;
	} // 나머지들이 역순으로 저장되어 있으므로 swap
	return ptr;
}

char* to_ten(char* str, int from_base)
{
	char* ptr = new char[11];
	int ret_num = 0;
	int tmp;
	int len;
	int idx1, idx2;

	len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		for (idx1 = 0; idx1 < 16; idx1++)
		{
			if (else_base[idx1] == str[len - i - 1])
				break; // 뒤에서부터 읽으며, 해당 자리가 10진수로 몇을 나타내는지를 표현
		}
		ret_num += idx1 * pow(from_base, i); // 각 자리 수를 곱함(예: 2 ^ 0, 2 ^ 1, ...)
	}
	tmp = ret_num;
	for (idx2 = 0; tmp; tmp /= 10, idx2++); // 10진수가 몇자리인지 계산
	for (int j = idx2 - 1; j >= 0; j--, ret_num /= 10)
		ptr[j] = ret_num % 10 + '0'; // 10진수를 문자열로 전환
	ptr[idx2] = 0;
	return (ptr);
}

char* from_to_two(char* str, int from_base, int to_base)
{
	int i, cnt;
	int len = strlen(str);
	int tmp;
	char* ptr = new char[33];

	if (from_base == to_base)
	{
		for (i = 0; i < len; i++)
			ptr[i] = str[i];
		ptr[i] = 0;
	}
	else if (from_base > to_base) // 예: input: 8진수, output: 2진수
	{
		cnt = log(from_base) / log(to_base); // 하나의 자리로 몇 자리의 2진수를 만들어야 하는지
		for (i = 0; i < len; i++)
		{
			for (tmp = 0; tmp < 16; tmp++)
			{
				if (else_base[tmp] == str[i]) // 각 자리가 10진수로 몇인지 찾기
					break;
			}
			for (int j = cnt - 1; j >= 0; j--)
			{
				ptr[j + i * cnt] = else_base[tmp % to_base]; // 해당 수를 2진수로 표현
				tmp /= to_base;
			}
		}
		ptr[i * cnt] = 0;
	}
	else
	{
		cnt = log(to_base) / log(from_base); // 예: input: 2진수, output: 8진수
		tmp = 0;
		i = 0;
		for (int j = 0; j < len; j++)
		{
			if (j && (j % cnt == 0 || j == len - 1))
			{
				if (j == len - 1)
					tmp += (str[0] - '0') * pow(from_base, j % cnt);
				ptr[i] = else_base[tmp];
				i++;
				tmp = 0;
			}
			tmp += (str[len - 1 - j] - '0') * pow(from_base, j % cnt);
		}// 2진수를 cnt칸만큼 묶어 하나로 바꿈 
		for (int j = 0; j < i / 2; j++)
		{
			tmp = ptr[j];
			ptr[j] = ptr[i - j - 1];
			ptr[i - j - 1] = tmp;
		} // 뒤에서부터 묶었으므로 swap
		ptr[i] = 0;
	}
	return ptr;
}