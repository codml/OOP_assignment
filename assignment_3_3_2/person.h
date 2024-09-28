#pragma once
#pragma warning(disable:4996)
#include <cstring>
#include <iostream>

class Person
{
protected:
    int age;
    char name[32];

public:
    Person();
    ~Person();
    virtual void Say() = 0; // pure virtual function, Person class는 생성 불가능!
};

class Professor : public Person // Person class 상속(public은 멤버의 상태를 그대로 반영)
{
protected:
    int profNum;
    char major[128];

public:
    Professor();
    ~Professor();
	void Setage(int num);
    void Setname(char *ptr);
	int Getage();
    char* Getname();
    void SetprofNum(int num);
    void Setmajor(char *ptr);
	int GetprofNum();
    char* Getmajor(); // set*: 멤버 변수에 값 카피, get*: 멤버 변수 반환
	virtual void Say(); // 가상함수 오버라이딩
};

class Student : public Person
{
protected:
    int stuNum;
    char major[128];
    int schoolYear;

public:
    Student();
    ~Student();
	void Setage(int num);
    void Setname(char *ptr);
	int Getage();
    char* Getname();
	void SetstuNum(int num);
    void Setmajor(char *ptr);
	void SetschoolYear(int num);
	int GetstuNum();
    char* Getmajor();
	int GetschoolYear(); // set*: 멤버 변수에 값 카피, get*: 멤버 변수 반환
	virtual void Say(); // 가상함수 오버라이딩
};