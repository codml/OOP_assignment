#include <iostream>
#include <fstream>

using namespace std;

class Mydecoding
{
private:
	char b_arr[1024]; // 바이너리 코드를 담을 배열
	char a_arr[512]; // 텍스트를 담을 배열

public:
	void read_binary() // 파일로부터 바이너리 코드를 읽음
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
			} // b_arr을 최대 25칸씩 읽으며 1을 만나거나 b_arr을 다 읽으면 멈춤
			if (j == 25)
				a_arr[k] = 'z'; // 0만 25칸이면 'z'
			else if (b_arr[i + j] == '1')
				a_arr[k] = 'a' + j; // 1을 만나 탈출한거면 'a' ~ 'y'
			if (b_arr[i + j])
				j++; // b_arr이 끝을 만나지 않았다면 한 칸 뒤에서 읽기 반복
			k++;
		}
		a_arr[k] = 0;
	}

	void write_alphabet() // a_arr에 작성된 알파벳 텍스트를 파일로 출력
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
	Mydecoding a; // 클래스의 인스턴스 생성

	a.read_binary();
	a.decode_binary();
	a.write_alphabet();
	return (0);
}