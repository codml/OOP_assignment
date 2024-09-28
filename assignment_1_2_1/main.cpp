#include <iostream>
#include <cstring>

using namespace std;

int	check_dup(char *str, int index);
// 앞서 나온 숫자와의 중복을 체크

int main()
{
	char	str1[1024];
	char	str2[1024];
	int		arr[10] = { 0, }; // 숫자별 나온 개수를 체크하기 위해 만든 배열

	cout << "Input: ";
	cin >> str1 >> str2;
	strcat_s(str1, str2); // 숫자 세기를 편하게 하기 위해 두 문자열을 하나로 합침
	for (int i = 0; str1[i]; i++)
		arr[str1[i] - '0'] += 1; // 숫자가 나오면 해당 인덱스(0~9)에 개수 카운트
	for (int i = 0; str1[i]; i++)
	{
		if (!check_dup(str1, i))
			cout << str1[i] << arr[str1[i] - '0'];
		// 출력하고자 하는 수가 앞에 없다면(중복되지 않는다면), 숫자와 개수 출력
	}
	return (0);
}

int	check_dup(char *str, int index)
{
	for (int i = 0; i < index; i++)
	{
		if (str[i] == str[index])
			return (1);
		// 해당 인덱스의 문자가 앞선 인덱스에 있다면 중복!
	}
	return (0);
}
