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
		cin >> buf; // ��� ����
		if (!strcmp(buf, "new_student")) // �� �л� ����
		{
			cin >> buf1 >> num >> buf2;
			ins.insert_student(buf1, num, buf2); // �Է¹��� �������� ����Ʈ�� �л� �߰�
		}
		else if (!strcmp(buf, "sort_by_name"))
			ins.sort(); // �̸� �� ����
		else if (!strcmp(buf, "print_all"))
			ins.print_all(); // ��ü ���
		else if (!strcmp(buf, "print_class"))
		{
			cin >> name_buf;
			ins.print_class(name_buf); // �Է¹��� Ŭ������ �л��鸸 ���
		}
		else if (!strcmp(buf, "exit"))
			break; // exit�̸� ����
		else
			cout << "wrong order" << endl; // �߸� �Է�
	}
	return (0);
}