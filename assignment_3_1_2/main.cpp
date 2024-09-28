#include <iostream>
using namespace std;

class Data
{
public:
	char* ptr; // 전체 문자열
	size_t idx; // 현재 인덱스
	size_t len; // 총 길이

	Data()
	{
		ptr = 0;
		idx = 0;
		len = 0;
	}

	~Data()
	{
		if (ptr)
			delete[] ptr; // ptr이 delete 되지 않고 프로그램이 종료되는 것을 대비해
		// static 변수의 data type을 class로 만들어 소멸자로 메모리 해제를 하게 만듦 
	}
};

char* my_strtok(char* str)
{
	static Data data; // 데이터를 저장할 변수
	size_t num;
	char* ret; // 리턴할 주소

	if (!str) // NULL이 들어오면
	{
		if (!(data.ptr)) // 기존 데이터가 없으면
			return 0; // 널 반환
		while (data.idx < data.len && !(data.ptr)[data.idx])
			(data.idx)++; // 널 문자인 부분 패스
		if (data.idx == data.len) // 데이터를 다 읽었으면
		{
			delete[] data.ptr; // 기존 데이터 삭제
			data.ptr = 0;
			return 0;
		}
	}
	else
	{
		for (num = 0; str[num]; num++); // str 길이 재기
		if (data.ptr)
			delete[] data.ptr; // 기존 데이터가 있으면 삭제
		data.ptr = new char[num + 1];
		data.idx = 0;
		data.len = num; // 클래스의 멤버 변수 할당
		for (int i = 0; i < num; i++)
		{
			if (str[i] == '@' || str[i] == '.')
				(data.ptr)[i] = 0; // 구분자라면 널 문자를 대신 삽입
			else
				(data.ptr)[i] = str[i]; // 구분자가 아니면 그냥 삽입
		}
		data.ptr[num] = 0;
		while (data.idx < data.len && !(data.ptr)[data.idx])
			(data.idx)++; // 널 문자 부분 패스
	}
	ret = data.ptr + data.idx; // 리턴할 문자열 주소
	while (data.idx < data.len && (data.ptr)[data.idx])
		(data.idx)++; // 널 문자 만날 때까지 idx 이동 
	return ret;
}

int main()
{
	char* tmp;
	char arr[512];

	cout << "input: ";
	cin >> arr;
	tmp = my_strtok(arr); // 첫번째 부분 반환
	while (tmp) // my_strtok가 NULL을 반환할 때까지 반복
	{
		cout << tmp << endl;
		tmp = my_strtok(0);
	}
	return 0;
}