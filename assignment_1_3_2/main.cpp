#include <iostream>
#include <cstring>

using namespace std;

int	get_gcd(int a, int b); // 이전 과제에서 썼던 GCD를 구하는 함수
void print_v_out(int num, int den); // V_out을 순환소수를 고려해 출력하는 함수

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
	if (!arr_r[2]) // R_load가 없으면
	{
		num = v_s * arr_r[1]; // 분모
		den = arr_r[0] + arr_r[1]; // 분자
		cout << "Vout: " << num << "/" << den << " = ";
		print_v_out(num, den);
	}
	else
	{
		num = v_s * arr_r[1] * arr_r[2];
		den = arr_r[0] * (arr_r[1] + arr_r[2]) + arr_r[1] * arr_r[2];
		// 원래 식에서 분모, 분자에 (R_L + R_2)를 곱해 분모, 분자가 정수형으로
		// 나오지 않는 경우를 막음
		cout << "Vout: " << num << " / " << den << " = ";
		print_v_out(num, den);
		num = arr_r[1] * arr_r[1] * arr_r[2];
		den = ((arr_r[0] * (arr_r[1] + arr_r[2]) + arr_r[1] * arr_r[2]) * (arr_r[1] + arr_r[2]));
		cout << fixed; // 소수점 출력을 고정
		cout.precision(2); // 소수점이 2자리만 나오도록 출력 조정
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
	den /= gcd; // 분모, 분자를 그들의 최대공약수로 나눠서 기약분수로 만듦
	for (tmp = den; tmp % 2 == 0; tmp /= 2);
	for (; tmp % 5 == 0; tmp /= 5);
	// 어떤 기약분수의 분모가 2와 5의 곱으로 이루어지지 않았다면 무한소수
	if (tmp != 1)
	{
		cout << num / den << "."; // 소수부분의 반복 패턴을 표현하기 위해 정수부분 우선 출력
		ptr = new int[den]; // 나눗셈 나머지가 나오는 순서를 기록할 배열
		memset(ptr, 0, den * sizeof(int)); // 안 나온 나머지를 판별하기 위해 0으로 초기화
		for (i = 0, tmp = num % den; ptr[tmp] == 0; i++, tmp = (tmp * 10) % den)
			ptr[tmp] = i + 1; // 이전에 나온 나머지가 나올 때까지 각 나머지의 순서 기록
		for (int j = 0; j < i; j++)
		{
			for (k = 0; k < den; k++)
			{
				if (ptr[k] == j + 1) // j + 1번째 나머지 찾기
					break;
			}
			if (prev)
				cout << (prev * 10 - k) / den; // 나머지에 해당하는 몫 찾아서 출력
			prev = k;
			if (k == tmp)
				cout << "("; // 순환소수 패턴이 시작되면 괄호 출력
		}
		cout << (prev * 10 - tmp) / den;
		cout << ")" << endl;
		delete[]ptr;
	}
	else
		cout << num / (double)den << endl; // 유한소수 or 정수면 그대로 출력
}