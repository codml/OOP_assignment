#include "School.h"

Student::Student(char* name, int age, char* class_name)
{
	this->name = new char[100];
	strcpy(this->name, name);
	this->age = age;
	this->class_name = new char[100];
	strcpy(this->class_name, class_name); // �޸� �Ҵ� �� ����
}

Student::~Student()
{
	delete[] name;
	delete[] class_name; // �޸� ����
}

void Student::print()
{
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Age: " << this->age << std::endl;
	std::cout << "Class: " << this->class_name << std::endl;
	std::cout << "----------" << std::endl; // ��� ������ ���� ���
}

School::School()
{
	memset(student_list, 0, sizeof(Student *) * 100); // ����Ʈ�� null�� �ʱ�ȭ
	size = 0;
}

School::~School()
{
	for (int i = 0; i < size; i++)
		delete student_list[i]; // ����Ʈ ���� student Ŭ���� �޸� ����
}

void School::insert_student(char* name, int age, char* class_name)
{
	if (size == 100)
		std::cout << "full of students" << std::endl; // ����Ʈ�� ����
	else
		student_list[size++] = new Student(name, age, class_name); // ����Ʈ�� student �Ҵ�
}

void School::sort()
{
	Student* tmp;

	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (strcmp(student_list[j]->name, student_list[j + 1]->name) > 0) // �̸��� ����
			{
				tmp = student_list[j];
				student_list[j] = student_list[j + 1];
				student_list[j + 1] = tmp;
			}
		}
	} // ���� ���� ���
}

void School::print_all()
{
	std::cout << "=====print_all=====" << std::endl;
	for (int i = 0; i < size; i++)
		student_list[i]->print(); // ����Ʈ �� ��� ��ü ���
}

void School::print_class(char* class_name)
{
	int cnt;

	cnt = 0;
	std::cout << "=====print_class=====" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(class_name, student_list[i]->class_name)) // �Ű������� ���� Ŭ������ �л���
		{
			cnt++; // ��µǴ� student ī��Ʈ
			student_list[i]->print(); // ���
		}
	}
	std::cout << "Number of classmates: " << cnt << std::endl;// ��µ� �л� �� ���
}