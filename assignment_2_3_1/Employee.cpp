#include "Employee.h"

Employee::Employee(char* name, int age, char* country, char* job)
{
	this->name = new char[100];
	strcpy(this->name, name);
	this->age = age;
	this->country = new char[100];
	strcpy(this->country, country);
	this->job = new char[100];
	strcpy(this->job, job); // �޸� �Ҵ� �� ����
}

Employee::~Employee()
{
	delete[] name;
	delete[] country;
	delete[] job; // �Ҵ��� �޸� ����
}

bool Employee::isNameCorrect(char* name)
{
	int num;

	num = strcmp(this->name, name); // 0�̸� ����, 0�� �ƴϸ� �ٸ�
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
	std::cout << "----------" << std::endl; // �� ��� ���� ��� �� �� ���
}

void Employee::change(char* name, int age, char* country, char* job)
{
	strcpy(this->name, name); // ���� �޸� ������ �����
	this->age = age;
	strcpy(this->country, country);
	strcpy(this->job, job);
}