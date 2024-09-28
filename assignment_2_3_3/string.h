#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>	
namespace oopstd
{
	class string
	{
	public:
		string(); // 기본 생성자
		string(const char* s); // 문자열을 받는 생성자
		string(const string& str); // copy constructor
		~string();

		string& assign(const string& str); //string에 다른 string의 내용을 할당
		char& at(size_t pos); // pos위치의 문자를 반환
		const char* c_str() const; // string을 char형 배열로 반환
		void clear(); // string 내용 삭제
		void push_back(char c); // string의 맨 뒤에 문자 삽입
		int compare(const string* str) const; // 입력받은 string과의 비교
		string& replace(size_t pose, size_t len, const string* str); // 지정된 위치에 string 추가
		string substr(size_t pos, size_t len) const; // 지정된 위치의 문자열 추출
		size_t find(const string& str, size_t pos = 0) const; // string의 위치를 반환

	private:
		char* s; // 문자열
		size_t len; // 길이
	};

	int stoi(const string& str, size_t* idx, int base = 10); // string to int
	float stof(const string& str, size_t* idx); // string to float

	string to_string(int val); // int to string
	string to_string(float val); // float to string
}