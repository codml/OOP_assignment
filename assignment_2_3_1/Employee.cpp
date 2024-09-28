#include "Employee.h"

Employee::Employee(char* name, int age, char* country, char* job)
{
	this->name = new char[100];
	strcpy(this->name, name);
	this->age = age;
	this->country = new char[100];
	strcpy(this->country, country);
	this->job = new char[100];
	strcpy(this->job, job); // 메모리 할당 후 복사
}

Employee::~Employee()
{
	delete[] name;
	delete[] country;
	delete[] job; // 할당한 메모리 해제
}

bool Employee::isNameCorrect(char* name)
{
	int num;

	num = strcmp(this->name, name); // 0이면 같고, 0이 아니면 다름
	if (num)
		return false;
	else
		return true;
}

void Employee::print()
{
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Age: " << this->age << std::endl;
	std::cout << "Country: " << this->country << std::endl;
	std::cout << "Job: " << this->job << std::endl;
	std::cout << "----------" << std::endl; // 각 멤버 변수 출력 후 선 출력
}

void Employee::change(char* name, int age, char* country, char* job)
{
	strcpy(this->name, name); // 기존 메모리 공간에 덮어쓰기
	this->age = age;
	strcpy(this->country, country);
	strcpy(this->job, job);
}