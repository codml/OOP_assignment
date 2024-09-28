#include <iostream>
#include <fstream>

using namespace std;

class Mydecoding
{
private:
	char b_arr[1024]; // ���̳ʸ� �ڵ带 ���� �迭
	char a_arr[512]; // �ؽ�Ʈ�� ���� �迭

public:
	void read_binary() // ���Ϸκ��� ���̳ʸ� �ڵ带 ����
	{
		ifstream fin;
		int i = 0;

		fin.open("binary.txt");
		if (!fin)
		{
			cout << "file load failed" << endl;
			return ;
		}
		fin.getline(b_arr, 1024);
		fin.close();
	}

	void decode_binary()
	{
		int j, k;

		k = 0;
		for(int i = 0; b_arr[i]; i += j)
		{
			for (j = 0; j < 25; j++)
			{
				if (b_arr[i + j] == '1' || !b_arr[i + j])
					break;
			} // b_arr�� �ִ� 25ĭ�� ������ 1�� �����ų� b_arr�� �� ������ ����
			if (j == 25)
				a_arr[k] = 'z'; // 0�� 25ĭ�̸� 'z'
			else if (b_arr[i + j] == '1')
				a_arr[k] = 'a' + j; // 1�� ���� Ż���ѰŸ� 'a' ~ 'y'
			if (b_arr[i + j])
				j++; // b_arr�� ���� ������ �ʾҴٸ� �� ĭ �ڿ��� �б� �ݺ�
			k++;
		}
		a_arr[k] = 0;
	}

	void write_alphabet() // a_arr�� �ۼ��� ���ĺ� �ؽ�Ʈ�� ���Ϸ� ���
	{
		ofstream fout;

		fout.open("alphabet.txt");
		if (!fout)
		{
			cout << "file generate failed" << endl;
			return ;
		}
		fout << a_arr;
		fout.close();
	}
};

int main()
{
	Mydecoding a; // Ŭ������ �ν��Ͻ� ����

	a.read_binary();
	a.decode_binary();
	a.write_alphabet();
	return (0);
}