#include <iostream>
#include "Employee.h"

using namespace std;

int main()
{
	int idx;
	Employee* p_arr[10]; // ����ü �迭
	char buf[100];
	char name_buf[100];
	char buf1[100];
	char buf2[100];
	char buf3[100];
	int num;

	idx = 0; // Employee�� 10���� �Ѵ����� üũ�� ����
	while (1)
	{
		cout << "order: ";
		cin >> buf; // ��ɾ��� ù �ܾ ����
		if (!strcmp(buf, "insert")) // insert��
		{
			cin >> buf1 >> num >> buf2 >> buf3; // ��� ������ �� ������ �Է�
			if (idx == 10)
				cout << "full of list" << endl; // 10���� �̹� �ִ� ���
			else
				p_arr[idx++] = new Employee(buf1, num, buf2, buf3); // ����ü �迭�� Employee �Ҵ�
		}
		else if (!strcmp(buf, "find")) // find��
		{
			cin >> name_buf; // ã�� �̸� �Է�
			cout << "=====find=====" << endl;
			for (int i = 0; i < idx; i++)
			{
				if (p_arr[i]->isNameCorrect(name_buf))
					p_arr[i]->print(); // �����ϸ� ���
			}
		}
		else if (!strcmp(buf, "change")) // change �̸�
		{
			cin >> name_buf >> buf1 >> num >> buf2 >> buf; // �ٲ� ���� �Է�
			for (int i = 0; i < idx; i++)
			{
				if (p_arr[i]->isNameCorrect(name_buf)) // �̸��� ������
				{
					delete p_arr[i]; // ���� Employee ����
					p_arr[i] = new Employee(buf1, num, buf2, buf3); // ���Ҵ�
				}
			}
		}
		else if (!strcmp(buf, "print"))
		{
			cout << "=====print=====" << endl;
			for (int i = 0; i < idx; i++)
				p_arr[i]->print(); // print�Լ� ���
		}
		else if (!strcmp(buf, "exit")) // exit�̸� break
			break;
		else
			cout << "wrong order" << endl; // �Է��� �߸����� ���
	}
	for (int i = 0; i < idx; i++)
		delete p_arr[i]; // �޸� ������Ű��
	return (0);
}