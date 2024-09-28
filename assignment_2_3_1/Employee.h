#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class Employee
{
private:
    char* name;
    int age;
    char* country;
    char* job;

public:
    Employee(char* name, int age, char* country, char* job); // ������
    ~Employee(); // �Ҹ���
    bool isNameCorrect(char* name); // name�� this->name�� ������ �ٸ���
    void print(); // ��� ������ ���
    void change(char* name, int age, char* country, char* job); // �ش� �Ű�������� ���� ����
};