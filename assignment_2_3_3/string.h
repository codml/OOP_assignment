#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>	
namespace oopstd
{
	class string
	{
	public:
		string(); // �⺻ ������
		string(const char* s); // ���ڿ��� �޴� ������
		string(const string& str); // copy constructor
		~string();

		string& assign(const string& str); //string�� �ٸ� string�� ������ �Ҵ�
		char& at(size_t pos); // pos��ġ�� ���ڸ� ��ȯ
		const char* c_str() const; // string�� char�� �迭�� ��ȯ
		void clear(); // string ���� ����
		void push_back(char c); // string�� �� �ڿ� ���� ����
		int compare(const string* str) const; // �Է¹��� string���� ��
		string& replace(size_t pose, size_t len, const string* str); // ������ ��ġ�� string �߰�
		string substr(size_t pos, size_t len) const; // ������ ��ġ�� ���ڿ� ����
		size_t find(const string& str, size_t pos = 0) const; // string�� ��ġ�� ��ȯ

	private:
		char* s; // ���ڿ�
		size_t len; // ����
	};

	int stoi(const string& str, size_t* idx, int base = 10); // string to int
	float stof(const string& str, size_t* idx); // string to float

	string to_string(int val); // int to string
	string to_string(float val); // float to string
}