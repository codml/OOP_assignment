#include <iostream>
using namespace std;

class Data
{
public:
	char* ptr; // ��ü ���ڿ�
	size_t idx; // ���� �ε���
	size_t len; // �� ����

	Data()
	{
		ptr = 0;
		idx = 0;
		len = 0;
	}

	~Data()
	{
		if (ptr)
			delete[] ptr; // ptr�� delete ���� �ʰ� ���α׷��� ����Ǵ� ���� �����
		// static ������ data type�� class�� ����� �Ҹ��ڷ� �޸� ������ �ϰ� ���� 
	}
};

char* my_strtok(char* str)
{
	static Data data; // �����͸� ������ ����
	size_t num;
	char* ret; // ������ �ּ�

	if (!str) // NULL�� ������
	{
		if (!(data.ptr)) // ���� �����Ͱ� ������
			return 0; // �� ��ȯ
		while (data.idx < data.len && !(data.ptr)[data.idx])
			(data.idx)++; // �� ������ �κ� �н�
		if (data.idx == data.len) // �����͸� �� �о�����
		{
			delete[] data.ptr; // ���� ������ ����
			data.ptr = 0;
			return 0;
		}
	}
	else
	{
		for (num = 0; str[num]; num++); // str ���� ���
		if (data.ptr)
			delete[] data.ptr; // ���� �����Ͱ� ������ ����
		data.ptr = new char[num + 1];
		data.idx = 0;
		data.len = num; // Ŭ������ ��� ���� �Ҵ�
		for (int i = 0; i < num; i++)
		{
			if (str[i] == '@' || str[i] == '.')
				(data.ptr)[i] = 0; // �����ڶ�� �� ���ڸ� ��� ����
			else
				(data.ptr)[i] = str[i]; // �����ڰ� �ƴϸ� �׳� ����
		}
		data.ptr[num] = 0;
		while (data.idx < data.len && !(data.ptr)[data.idx])
			(data.idx)++; // �� ���� �κ� �н�
	}
	ret = data.ptr + data.idx; // ������ ���ڿ� �ּ�
	while (data.idx < data.len && (data.ptr)[data.idx])
		(data.idx)++; // �� ���� ���� ������ idx �̵� 
	return ret;
}

int main()
{
	char* tmp;
	char arr[512];

	cout << "input: ";
	cin >> arr;
	tmp = my_strtok(arr); // ù��° �κ� ��ȯ
	while (tmp) // my_strtok�� NULL�� ��ȯ�� ������ �ݺ�
	{
		cout << tmp << endl;
		tmp = my_strtok(0);
	}
	return 0;
}