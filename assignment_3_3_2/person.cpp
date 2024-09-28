#include "person.h"

Person::Person()
{
    age = 0;
    memset(name, 0, 32); // 메모리 공간을 0으로 채움
}

Person::~Person()
{
    age = 0; // char name[32]는 동적할당된 메모리가 아니므로 따로 해제할 필요 없음
}

Professor::Professor()
{
    profNum = 0;
    memset(major, 0, 128); // 메모리 공간 0으로 초기화
}

Professor::~Professor()
{
    profNum = 0;
}

void Professor::Setage(int num)
{
    age = num; // 부모 클래스에서 상속받은 int age에 값 카피
}

void Professor::Setname(char *ptr)
{
    strcpy(name, ptr); // 부모 클래스에서 상속받은 char name[32]에 문자열 카피
}

int Professor::Getage()
{
    return age;
}

char* Professor::Getname()
{
    return name; // Person class의 멤버 변수 반환
}

void Professor::SetprofNum(int num)
{
    profNum = num;
}

void Professor::Setmajor(char *ptr)
{
    strcpy(major, ptr); // Professor class의 멤버 변수에 매개변수 카피
}

int Professor::GetprofNum()
{
    return profNum;
}

char* Professor::Getmajor()
{
    return major; // 멤버 변수 반환
}

void Professor::Say()
{
    std::cout << "I'm professor." << std::endl; // 이 함수가 Professor class 함수임을 나타냄
    std::cout << "I'm " << age << " years old." << std::endl;
    std::cout << "My name is " << name << "." << std::endl;
    std::cout << "My professor number is " << profNum << "." << std::endl;
    std::cout << "MY major is " << major << "." << std::endl; // 멤버 변수 출력
}

Student::Student()
{
    stuNum = 0;
    memset(major, 0, 128);
    schoolYear = 0;
}

Student::~Student()
{
    stuNum = 0;
    schoolYear = 0;
}

void Student::Setage(int num)
{
    age = num;
}

void Student::Setname(char *ptr)
{
    strcpy(name, ptr); // 부모 클래스에서 상속받은 멤버 변수에 카피
}

int Student::Getage()
{
    return age;
}

char* Student::Getname()
{
    return name; // 멤버 변수 반환
}

void Student::SetstuNum(int num)
{
    stuNum = num;
}

void Student::Setmajor(char *ptr)
{
    strcpy(major, ptr);
}

void Student::SetschoolYear(int num)
{
    schoolYear = num; // Student class의 멤버 변수에 값 카피
}

int Student::GetstuNum()
{
    return stuNum;
}

char* Student::Getmajor()
{
    return major;
}

int Student::GetschoolYear()
{
    return schoolYear; // 멤버 변수 반환
}

void Student::Say()
{
    std::cout << "I'm student." << std::endl; // 이 함수가 Student class의 멤버 함수임을 나타냄
    std::cout << "I'm " << age << " years old." << std::endl;
    std::cout << "My name is " << name << "." << std::endl;
    std::cout << "My student number is " << stuNum << "." << std::endl;
    std::cout << "MY major is " << major << "." << std::endl;
    std::cout << "MY school year is " << schoolYear << "." << std::endl; // 멤버 변수 출력
}