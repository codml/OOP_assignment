#include "person.h"

Person::Person()
{
    age = 0;
    memset(name, 0, 32); // �޸� ������ 0���� ä��
}

Person::~Person()
{
    age = 0; // char name[32]�� �����Ҵ�� �޸𸮰� �ƴϹǷ� ���� ������ �ʿ� ����
}

Professor::Professor()
{
    profNum = 0;
    memset(major, 0, 128); // �޸� ���� 0���� �ʱ�ȭ
}

Professor::~Professor()
{
    profNum = 0;
}

void Professor::Setage(int num)
{
    age = num; // �θ� Ŭ�������� ��ӹ��� int age�� �� ī��
}

void Professor::Setname(char *ptr)
{
    strcpy(name, ptr); // �θ� Ŭ�������� ��ӹ��� char name[32]�� ���ڿ� ī��
}

int Professor::Getage()
{
    return age;
}

char* Professor::Getname()
{
    return name; // Person class�� ��� ���� ��ȯ
}

void Professor::SetprofNum(int num)
{
    profNum = num;
}

void Professor::Setmajor(char *ptr)
{
    strcpy(major, ptr); // Professor class�� ��� ������ �Ű����� ī��
}

int Professor::GetprofNum()
{
    return profNum;
}

char* Professor::Getmajor()
{
    return major; // ��� ���� ��ȯ
}

void Professor::Say()
{
    std::cout << "I'm professor." << std::endl; // �� �Լ��� Professor class �Լ����� ��Ÿ��
    std::cout << "I'm " << age << " years old." << std::endl;
    std::cout << "My name is " << name << "." << std::endl;
    std::cout << "My professor number is " << profNum << "." << std::endl;
    std::cout << "MY major is " << major << "." << std::endl; // ��� ���� ���
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
    strcpy(name, ptr); // �θ� Ŭ�������� ��ӹ��� ��� ������ ī��
}

int Student::Getage()
{
    return age;
}

char* Student::Getname()
{
    return name; // ��� ���� ��ȯ
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
    schoolYear = num; // Student class�� ��� ������ �� ī��
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
    return schoolYear; // ��� ���� ��ȯ
}

void Student::Say()
{
    std::cout << "I'm student." << std::endl; // �� �Լ��� Student class�� ��� �Լ����� ��Ÿ��
    std::cout << "I'm " << age << " years old." << std::endl;
    std::cout << "My name is " << name << "." << std::endl;
    std::cout << "My student number is " << stuNum << "." << std::endl;
    std::cout << "MY major is " << major << "." << std::endl;
    std::cout << "MY school year is " << schoolYear << "." << std::endl; // ��� ���� ���
}