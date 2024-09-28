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
    Employee(char* name, int age, char* country, char* job); // 생성자
    ~Employee(); // 소멸자
    bool isNameCorrect(char* name); // name과 this->name이 같은지 다른지
    void print(); // 멤버 변수들 출력
    void change(char* name, int age, char* country, char* job); // 해당 매개변수들로 정보 수정
};