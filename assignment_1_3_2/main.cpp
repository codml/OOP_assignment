#include <iostream>
#include <cstring>

using namespace std;

int	get_gcd(int a, int b); // ���� �������� ��� GCD�� ���ϴ� �Լ�
void print_v_out(int num, int den); // V_out�� ��ȯ�Ҽ��� ����� ����ϴ� �Լ�

int main()
{
	int v_s;
	int arr_r[3];
	int num;
	int den;

	cout << "Vs: ";
	cin >> v_s;
	cout << "R1: ";
	cin >> arr_r[0];
	cout << "R2: ";
	cin >> arr_r[1];
	cout << "R(Load): ";
	cin >> arr_r[2];
	if (!arr_r[2]) // R_load�� ������
	{
		num = v_s * arr_r[1]; // �и�
		den = arr_r[0] + arr_r[1]; // ����
		cout << "Vout: " << num << "/" << den << " = ";
		print_v_out(num, den);
	}
	else
	{
		num = v_s * arr_r[1] * arr_r[2];
		den = arr_r[0] * (arr_r[1] + arr_r[2]) + arr_r[1] * arr_r[2];
		// ���� �Ŀ��� �и�, ���ڿ� (R_L + R_2)�� ���� �и�, ���ڰ� ����������
		// ������ �ʴ� ��츦 ����
		cout << "Vout: " << num << " / " << den << " = ";
		print_v_out(num, den);
		num = arr_r[1] * arr_r[1] * arr_r[2];
		den = ((arr_r[0] * (arr_r[1] + arr_r[2]) + arr_r[1] * arr_r[2]) * (arr_r[1] + arr_r[2]));
		cout << fixed; // �Ҽ��� ����� ����
		cout.precision(2); // �Ҽ����� 2�ڸ��� �������� ��� ����
		cout << num * (double)100 / den;
		cout << "%\n";
	}
	return (0);
}

int	get_gcd(int a, int b)
{
	int ret;

	if (a % b == 0)
		return (b);
	else
		ret = get_gcd(b, a % b);
	return (ret);
}

void	print_v_out(int num, int den)
{
	int gcd, tmp, i, k, prev = 0;
	int* ptr;

	if (num > den)
		gcd = get_gcd(num, den);
	else
		gcd = get_gcd(den, num);
	num /= gcd;
	den /= gcd; // �и�, ���ڸ� �׵��� �ִ������� ������ ���м��� ����
	for (tmp = den; tmp % 2 == 0; tmp /= 2);
	for (; tmp % 5 == 0; tmp /= 5);
	// � ���м��� �и� 2�� 5�� ������ �̷������ �ʾҴٸ� ���ѼҼ�
	if (tmp != 1)
	{
		cout << num / den << "."; // �Ҽ��κ��� �ݺ� ������ ǥ���ϱ� ���� �����κ� �켱 ���
		ptr = new int[den]; // ������ �������� ������ ������ ����� �迭
		memset(ptr, 0, den * sizeof(int)); // �� ���� �������� �Ǻ��ϱ� ���� 0���� �ʱ�ȭ
		for (i = 0, tmp = num % den; ptr[tmp] == 0; i++, tmp = (tmp * 10) % den)
			ptr[tmp] = i + 1; // ������ ���� �������� ���� ������ �� �������� ���� ���
		for (int j = 0; j < i; j++)
		{
			for (k = 0; k < den; k++)
			{
				if (ptr[k] == j + 1) // j + 1��° ������ ã��
					break;
			}
			if (prev)
				cout << (prev * 10 - k) / den; // �������� �ش��ϴ� �� ã�Ƽ� ���
			prev = k;
			if (k == tmp)
				cout << "("; // ��ȯ�Ҽ� ������ ���۵Ǹ� ��ȣ ���
		}
		cout << (prev * 10 - tmp) / den;
		cout << ")" << endl;
		delete[]ptr;
	}
	else
		cout << num / (double)den << endl; // ���ѼҼ� or ������ �״�� ���
}