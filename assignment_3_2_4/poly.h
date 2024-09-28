#pragma once
#include <iostream>

class Term
{
private:
	int m_Coefficient; // 계수
	int m_Exponent; // 차수
	Term* m_pNext; // 다음 노드

public:
	Term();
	~Term();

	void SetCoeff(int coeff);
	void SetExponent(int exponent);
	int GetCoeff();
	int GetExponent();
	void SetNext(Term* pNext);
	Term* GetNext(); // 멤버 변수 설정 및 반환
};

class Polynomial
{
private:
	Term* m_pHead; // 다항식의 맨 앞 노드

public:
	Polynomial();
	~Polynomial();

	void Insert(Term* pTerm); // 항 하나를 다항식 리스트에 삽입
	void PrintList(); // 다항식 출력
	void Add(Polynomial& poly); // 다항식 덧셈
	void Sub(Polynomial& poly); // 다항식 뺄셈
};