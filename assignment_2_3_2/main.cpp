#include <iostream>
#include "School.h"

using namespace std;

int main()
{
	School ins;
	char buf[100];
	char name_buf[100];
	char buf1[100];
	char buf2[100];
	int num;

	while (1)
	{
		cout << "order: ";
		cin >> buf; // 명령 받음
		if (!strcmp(buf, "new_student")) // 새 학생 만듦
		{
			cin >> buf1 >> num >> buf2;
			ins.insert_student(buf1, num, buf2); // 입력받은 내용으로 리스트에 학생 추가
		}
		else if (!strcmp(buf, "sort_by_name"))
			ins.sort(); // 이름 순 정렬
		else if (!strcmp(buf, "print_all"))
			ins.print_all(); // 전체 출력
		else if (!strcmp(buf, "print_class"))
		{
			cin >> name_buf;
			ins.print_class(name_buf); // 입력받은 클래스의 학생들만 출력
		}
		else if (!strcmp(buf, "exit"))
			break; // exit이면 종료
		else
			cout << "wrong order" << endl; // 잘못 입력
	}
	return (0);
}