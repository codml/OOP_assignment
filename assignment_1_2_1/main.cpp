#include <iostream>
#include <cstring>

using namespace std;

int	check_dup(char *str, int index);
// �ռ� ���� ���ڿ��� �ߺ��� üũ

int main()
{
	char	str1[1024];
	char	str2[1024];
	int		arr[10] = { 0, }; // ���ں� ���� ������ üũ�ϱ� ���� ���� �迭

	cout << "Input: ";
	cin >> str1 >> str2;
	strcat_s(str1, str2); // ���� ���⸦ ���ϰ� �ϱ� ���� �� ���ڿ��� �ϳ��� ��ħ
	for (int i = 0; str1[i]; i++)
		arr[str1[i] - '0'] += 1; // ���ڰ� ������ �ش� �ε���(0~9)�� ���� ī��Ʈ
	for (int i = 0; str1[i]; i++)
	{
		if (!check_dup(str1, i))
			cout << str1[i] << arr[str1[i] - '0'];
		// ����ϰ��� �ϴ� ���� �տ� ���ٸ�(�ߺ����� �ʴ´ٸ�), ���ڿ� ���� ���
	}
	return (0);
}

int	check_dup(char *str, int index)
{
	for (int i = 0; i < index; i++)
	{
		if (str[i] == str[index])
			return (1);
		// �ش� �ε����� ���ڰ� �ռ� �ε����� �ִٸ� �ߺ�!
	}
	return (0);
}
