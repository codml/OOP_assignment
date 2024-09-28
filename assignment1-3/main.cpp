#include <iostream>
#include <cmath>
using namespace std;

void    swap(int* a, int* b);
// a�� b�� Call-by-reference�� �ٲ��ִ� �Լ�
int	get_gcd(int a, int b);
// �ִ������� ���ؼ� ret �����Ͱ� ����Ű�� ������ �����ϴ� ����Լ�

int main()
{
	int a, b;
	long long num;
	int gcd;
	long long lcm;
	// num(a * b)�� lcm(�ּҰ����)�� long long ������ ����
	// �̴� a * b�� int�� ������ ��� �����÷ο찡 �Ͼ�� ���� ���� ����
	// 8byte �ڷ��� long long�� �� ����
	cout << "Input: ";
	cin >> a >> b;

	if (a < b)
		swap(&a, &b);
	if (b == 0)
		gcd = a;
	// �� �� �� ���� ���� 0�̸� �ִ������� ū ��
	else
		gcd = get_gcd(a, b);
	cout << "gcd :" << gcd << endl;
	if (a == 0)
		lcm = 0;
	// ������ �̿��� LCM�� ���� �� 0���� ������ ���� ���� ����
	else
	{
		num = (long long)a * b;
		lcm = num / (long long)gcd;
	}
	cout << "LCM: " << lcm << endl;
	return (0);
}

void	swap(int* a, int* b)
{
	int		temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int	get_gcd(int a, int b)
{
	int ret;

	if (a % b == 0)
		return (b);
	else
		ret = get_gcd(b, a % b);
	return (ret);
	// ù ��° ���ڿ� �� ��° ������ ������ ������ ����� 0�� ������ ��������� �Լ��� ȣ��
}