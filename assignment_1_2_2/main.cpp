#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

void	Sender(char *arr); // input으로 FCS을 만들어 input에 붙임
int		return_bits(int num); // 문자열을 읽어 만들어진 수가 2진수로 몇자리인지 반환
void	Transmission_Channel(const char *coded_frame); // 각 비트가 5%확률로 바뀌는 과정
int		Receiver(const char* received_frame); // receiver가 값을 받아 나머지를 판별함

char	output[17]; // 결과값
int		binary_p = 0b11011; // CRC 다항식

int main()
{
	char	input[17];
	int		check_error;

	cout << "Data: ";
	cin >> input;
	Sender(input);
	cout << "Coded frame: " << input << endl;
	Transmission_Channel(input);
	cout << "Received frame: " << output << endl;
	check_error = Receiver(output); // Receiver는 XOR연산을 하고난 후 나머지를 반환
	output[12] = 0; // 현재 output은 16자리(12 + FCS 4자리)이므로 12자리만 출력하기 위함
	cout << "Reconstructed data: " << output << endl;
	if (!check_error) // 나머지가 0이면 == 에러가 발생하지 않았으면
		cout << "No detected error" << endl;
	else
		cout << "Receiver has detected error" << endl;
	return (0);
}

void	Sender(char *arr)
{
	int	binary_r;

	binary_r = 0;	// 5자리가 될때마다 CRC다항식과 XOR연산을 하는 수
					// 최종적으로 4bit remainder를 얻게 됨
	strcat_s(arr, 17, "0000"); // 나머지를 4자리까지 만들기 위해 4개의 0비트를 추가
	for (int i = 0; i < 16; i++)
	{
		binary_r = binary_r << 1; // remainder의 각 비트를 왼쪽으로 밈 == 2배
		binary_r += arr[i] - '0'; // input을 앞에서부터 한 비트씩 읽으며 remainder에 추가
		if (return_bits(binary_r) == 5) // remainer가 5자리가 되면
			binary_r = binary_r ^ binary_p; // XOR연산을 하고, 이 값을 remainder에 저장
	}
	for (int i = 0; i < 4; i++)
	{
		arr[15 - i] = (binary_r & 1) + '0'; // remainder의 뒤에서 한 자리씩 떼어 input에 추가
		binary_r = binary_r >> 1; // 맨 뒷자리 제거 == 나누기 2
	}
}

int		return_bits(int num)
{
	int		cnt;

	cnt = 0;
	while (num)
	{
		num = num >> 1;
		cnt++;
	}
	return (cnt);
}

void	Transmission_Channel(const char * coded_frame)
{
	int		num;

	srand((unsigned int)time(NULL)); // random seed를 현재 시간으로 초기화
	for (int i = 0; coded_frame[i]; i++)
	{
		num = rand() % 100; // 0 <= rand() <= 99
		output[i] = coded_frame[i] * (num > 4)
			+ ((coded_frame[i] - '0' + 1) % 2 + '0') * (num <= 4);
		// num이 4이상이면(95%확률) coded_frame[i]을 그대로 넣고
		// 4이하면(5%확률) coded_frame[i]를 반전시켜 넣는다.
		// 부등호가 참이면 1, 거짓이면 0을 반환하기 때문에 가능함
	}
	output[16] = 0;
}

int		Receiver(const char* received_frame)
{
	int	binary_r;

	binary_r = 0;
	for (int i = 0; i < 16; i++)
	{
		binary_r = binary_r << 1;
		binary_r += received_frame[i] - '0';
		if (return_bits(binary_r) == 5)
			binary_r = binary_r ^ binary_p;
	}
	// Sender와 나머지 삽입부분 제외하고 동일
	return (binary_r);
}