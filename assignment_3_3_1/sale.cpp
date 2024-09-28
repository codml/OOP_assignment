#include "sale.h"

Sale::Sale()
{
	Price = 0; // 멤버 변수 초기화
}

Sale::Sale(double ThePrice)
{
	Price = ThePrice; // 매개변수로 멤버 변수 초기화
}

Sale::~Sale()
{
	Price = 0; // 해제할 메모리가 없다
}

double Sale::GetPrice()
{
	return Price; // 멤버 변수 반환
}

double Sale::Bill()
{
	return Price; // 적용할 할인율이 없으므로 그냥 price 반환
}

double Sale::Savings(Sale& Other)
{
	return Other.Price - this->Price; // Other의 price보다 this의 price가 얼마나 싼 지를 반환
}

bool Sale::operator < (Sale& Other)
{
	if (this->Price < Other.Price) // 기존의 연산자의 비교 대상을 각 객체의 멤버 변수(price)로 함
		return true;
	else
		return false;
}

DiscountSale::DiscountSale()
{
	DiscountPercent = 0; // Price는 Sale의 생성자가 호출될 때 초기화됨
}

DiscountSale::DiscountSale(double ThePrice) : Sale(ThePrice)
{
	DiscountPercent = 0; // Price는 Sale(double ThePrice)로 초기화
}

DiscountSale::~DiscountSale()
{
	DiscountPercent = 0;
}

double DiscountSale::GetDiscount()
{
	return DiscountPercent; // 멤버 변수 반환
}

void DiscountSale::SetDiscount(double discount)
{
	DiscountPercent = discount; // 멤버 변수에 매개 변수 값 카피
}

double DiscountSale::Bill()
{
	return (this->GetPrice() * (((double)100 - DiscountPercent) / (double)100));
	// 할인율이 적용된 가격을 반환
}

double DiscountSale::Savings(DiscountSale& Other)
{
	return (Other.Bill() - this->Bill());
	// 할인율이 적용된 가격의 차이를 반환
}

bool DiscountSale::operator < (DiscountSale& second)
{
	if (this->GetPrice() < second.GetPrice()) // Sale class의 < 와 동일
		return true;
	else
		return false;
}