#include <iostream>
#include "Employee.h"

using namespace std;

int main()
{
	int idx;
	Employee* p_arr[10]; // 구조체 배열
	char buf[100];
	char name_buf[100];
	char buf1[100];
	char buf2[100];
	char buf3[100];
	int num;

	idx = 0; // Employee가 10명이 넘는지를 체크할 변수
	while (1)
	{
		cout << "order: ";
		cin >> buf; // 명령어의 첫 단어를 저장
		if (!strcmp(buf, "insert")) // insert면
		{
			cin >> buf1 >> num >> buf2 >> buf3; // 멤버 변수로 쓸 내용을 입력
			if (idx == 10)
				cout << "full of list" << endl; // 10명이 이미 있는 경우
			else
				p_arr[idx++] = new Employee(buf1, num, buf2, buf3); // 구조체 배열에 Employee 할당
		}
		else if (!strcmp(buf, "find")) // find면
		{
			cin >> name_buf; // 찾을 이름 입력
			cout << "=====find=====" << endl;
			for (int i = 0; i < idx; i++)
			{
				if (p_arr[i]->isNameCorrect(name_buf))
					p_arr[i]->print(); // 존재하면 출력
			}
		}
		else if (!strcmp(buf, "change")) // change 이면
		{
			cin >> name_buf >> buf1 >> num >> buf2 >> buf; // 바꿀 정보 입력
			for (int i = 0; i < idx; i++)
			{
				if (p_arr[i]->isNameCorrect(name_buf)) // 이름이 맞으면
				{
					delete p_arr[i]; // 기존 Employee 삭제
					p_arr[i] = new Employee(buf1, num, buf2, buf3); // 재할당
				}
			}
		}
		else if (!strcmp(buf, "print"))
		{
			cout << "=====print=====" << endl;
			for (int i = 0; i < idx; i++)
				p_arr[i]->print(); // print함수 사용
		}
		else if (!strcmp(buf, "exit")) // exit이면 break
			break;
		else
			cout << "wrong order" << endl; // 입력이 잘못됐을 경우
	}
	for (int i = 0; i < idx; i++)
		delete p_arr[i]; // 메모리 해제시키기
	return (0);
}