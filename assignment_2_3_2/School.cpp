#include "School.h"

Student::Student(char* name, int age, char* class_name)
{
	this->name = new char[100];
	strcpy(this->name, name);
	this->age = age;
	this->class_name = new char[100];
	strcpy(this->class_name, class_name); // 메모리 할당 후 복사
}

Student::~Student()
{
	delete[] name;
	delete[] class_name; // 메모리 해제
}

void Student::print()
{
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Age: " << this->age << std::endl;
	std::cout << "Class: " << this->class_name << std::endl;
	std::cout << "----------" << std::endl; // 멤버 변수의 정보 출력
}

School::School()
{
	memset(student_list, 0, sizeof(Student *) * 100); // 리스트를 null로 초기화
	size = 0;
}

School::~School()
{
	for (int i = 0; i < size; i++)
		delete student_list[i]; // 리스트 내의 student 클래스 메모리 해제
}

void School::insert_student(char* name, int age, char* class_name)
{
	if (size == 100)
		std::cout << "full of students" << std::endl; // 리스트가 꽉참
	else
		student_list[size++] = new Student(name, age, class_name); // 리스트에 student 할당
}

void School::sort()
{
	Student* tmp;

	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (strcmp(student_list[j]->name, student_list[j + 1]->name) > 0) // 이름순 정렬
			{
				tmp = student_list[j];
				student_list[j] = student_list[j + 1];
				student_list[j + 1] = tmp;
			}
		}
	} // 버블 정렬 사용
}

void School::print_all()
{
	std::cout << "=====print_all=====" << std::endl;
	for (int i = 0; i < size; i++)
		student_list[i]->print(); // 리스트 내 요소 전체 출력
}

void School::print_class(char* class_name)
{
	int cnt;

	cnt = 0;
	std::cout << "=====print_class=====" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(class_name, student_list[i]->class_name)) // 매개변수로 들어온 클래스의 학생만
		{
			cnt++; // 출력되는 student 카운트
			student_list[i]->print(); // 출력
		}
	}
	std::cout << "Number of classmates: " << cnt << std::endl;// 출력된 학생 수 출력
}