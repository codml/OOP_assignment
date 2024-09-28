#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class Student
{
private:
	char* name;
	int age;
	char* class_name; // student의 정보들
	Student(char* name, int age, char* class_name);
	~Student();
	void print(); // 내용 출력

	friend class School; // School 클래스에서는 이 클래스의 private에도 접근이 가능함
};

class School
{
private:
	class Student* student_list[100]; // student를 저장할 리스트
	int size; // 리스트의 사이즈

public:
	School();
	~School();

	void insert_student(char* name, int age, char* class_name); // student 삽입
	void sort(); // 이름순으로 정렬
	void print_all(); // 전체 출력
	void print_class(char* class_name); // 매개변수로 들어온 클래스 출력
};
