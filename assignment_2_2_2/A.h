#pragma once

#include <iostream>
using namespace std;

class A
{
private:
	double num; // private 변수: 클래스 내부에서만(예: 멤버 함수) 접근 가능

public: // public: 클래스 외부에서 사용 가능
	A(double input); // 생성자: 객체가 만들어질 때 호출
	~A(); // 소멸자: 객체가 소멸될 때 호출
};