#pragma once
#include <iostream>
class Sale
{
private:
	double Price;

public:
	Sale();
	Sale(double ThePrice); // 멤버 변수를 매개변수로 초기화
	~Sale();

	double GetPrice(); // 멤버 변수 반환
	virtual double Bill(); // overriding 될 함수
	double Savings(Sale& Other); // Other보다 얼마나 싼 지를 반환하는 함수
	bool operator < (Sale& Other); // Other와 멤버 변수 크기 비교
};

class DiscountSale : public Sale
{
private:
	double DiscountPercent; // 할인율

public:
	DiscountSale();
	DiscountSale(double ThePrice); // Sale class의 Price만 초기화
	~DiscountSale();
	double GetDiscount(); // DiscountPercent 반환
	void SetDiscount(double discount); // DiscountSale의 멤버 변수
	double Bill(); // 할인율이 적용된 가격을 반환
	double Savings(DiscountSale& Other); // Sale의 Savings에서 할인율이 적용된 차이를 반환
	bool operator < (DiscountSale& second); // Sale의 < 와 같음(할인율이 적용되도
											// 양 변을 할인율로 나누면 같은 연산임)
};