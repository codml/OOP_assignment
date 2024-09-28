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
    virtual void Say() = 0; // pure virtual function, Person class�� ���� �Ұ���!
};

class Professor : public Person // Person class ���(public�� ����� ���¸� �״�� �ݿ�)
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
    char* Getmajor(); // set*: ��� ������ �� ī��, get*: ��� ���� ��ȯ
	virtual void Say(); // �����Լ� �������̵�
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
	int GetschoolYear(); // set*: ��� ������ �� ī��, get*: ��� ���� ��ȯ
	virtual void Say(); // �����Լ� �������̵�
};