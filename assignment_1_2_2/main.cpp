#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

void	Sender(char *arr); // input���� FCS�� ����� input�� ����
int		return_bits(int num); // ���ڿ��� �о� ������� ���� 2������ ���ڸ����� ��ȯ
void	Transmission_Channel(const char *coded_frame); // �� ��Ʈ�� 5%Ȯ���� �ٲ�� ����
int		Receiver(const char* received_frame); // receiver�� ���� �޾� �������� �Ǻ���

char	output[17]; // �����
int		binary_p = 0b11011; // CRC ���׽�

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
	check_error = Receiver(output); // Receiver�� XOR������ �ϰ� �� �������� ��ȯ
	output[12] = 0; // ���� output�� 16�ڸ�(12 + FCS 4�ڸ�)�̹Ƿ� 12�ڸ��� ����ϱ� ����
	cout << "Reconstructed data: " << output << endl;
	if (!check_error) // �������� 0�̸� == ������ �߻����� �ʾ�����
		cout << "No detected error" << endl;
	else
		cout << "Receiver has detected error" << endl;
	return (0);
}

void	Sender(char *arr)
{
	int	binary_r;

	binary_r = 0;	// 5�ڸ��� �ɶ����� CRC���׽İ� XOR������ �ϴ� ��
					// ���������� 4bit remainder�� ��� ��
	strcat_s(arr, 17, "0000"); // �������� 4�ڸ����� ����� ���� 4���� 0��Ʈ�� �߰�
	for (int i = 0; i < 16; i++)
	{
		binary_r = binary_r << 1; // remainder�� �� ��Ʈ�� �������� �� == 2��
		binary_r += arr[i] - '0'; // input�� �տ������� �� ��Ʈ�� ������ remainder�� �߰�
		if (return_bits(binary_r) == 5) // remainer�� 5�ڸ��� �Ǹ�
			binary_r = binary_r ^ binary_p; // XOR������ �ϰ�, �� ���� remainder�� ����
	}
	for (int i = 0; i < 4; i++)
	{
		arr[15 - i] = (binary_r & 1) + '0'; // remainder�� �ڿ��� �� �ڸ��� ���� input�� �߰�
		binary_r = binary_r >> 1; // �� ���ڸ� ���� == ������ 2
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

	srand((unsigned int)time(NULL)); // random seed�� ���� �ð����� �ʱ�ȭ
	for (int i = 0; coded_frame[i]; i++)
	{
		num = rand() % 100; // 0 <= rand() <= 99
		output[i] = coded_frame[i] * (num > 4)
			+ ((coded_frame[i] - '0' + 1) % 2 + '0') * (num <= 4);
		// num�� 4�̻��̸�(95%Ȯ��) coded_frame[i]�� �״�� �ְ�
		// 4���ϸ�(5%Ȯ��) coded_frame[i]�� �������� �ִ´�.
		// �ε�ȣ�� ���̸� 1, �����̸� 0�� ��ȯ�ϱ� ������ ������
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
	// Sender�� ������ ���Ժκ� �����ϰ� ����
	return (binary_r);
}