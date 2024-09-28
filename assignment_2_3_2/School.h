#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class Student
{
private:
	char* name;
	int age;
	char* class_name; // student�� ������
	Student(char* name, int age, char* class_name);
	~Student();
	void print(); // ���� ���

	friend class School; // School Ŭ���������� �� Ŭ������ private���� ������ ������
};

class School
{
private:
	class Student* student_list[100]; // student�� ������ ����Ʈ
	int size; // ����Ʈ�� ������

public:
	School();
	~School();

	void insert_student(char* name, int age, char* class_name); // student ����
	void sort(); // �̸������� ����
	void print_all(); // ��ü ���
	void print_class(char* class_name); // �Ű������� ���� Ŭ���� ���
};
