#include "sale.h"

Sale::Sale()
{
	Price = 0; // ��� ���� �ʱ�ȭ
}

Sale::Sale(double ThePrice)
{
	Price = ThePrice; // �Ű������� ��� ���� �ʱ�ȭ
}

Sale::~Sale()
{
	Price = 0; // ������ �޸𸮰� ����
}

double Sale::GetPrice()
{
	return Price; // ��� ���� ��ȯ
}

double Sale::Bill()
{
	return Price; // ������ �������� �����Ƿ� �׳� price ��ȯ
}

double Sale::Savings(Sale& Other)
{
	return Other.Price - this->Price; // Other�� price���� this�� price�� �󸶳� �� ���� ��ȯ
}

bool Sale::operator < (Sale& Other)
{
	if (this->Price < Other.Price) // ������ �������� �� ����� �� ��ü�� ��� ����(price)�� ��
		return true;
	else
		return false;
}

DiscountSale::DiscountSale()
{
	DiscountPercent = 0; // Price�� Sale�� �����ڰ� ȣ��� �� �ʱ�ȭ��
}

DiscountSale::DiscountSale(double ThePrice) : Sale(ThePrice)
{
	DiscountPercent = 0; // Price�� Sale(double ThePrice)�� �ʱ�ȭ
}

DiscountSale::~DiscountSale()
{
	DiscountPercent = 0;
}

double DiscountSale::GetDiscount()
{
	return DiscountPercent; // ��� ���� ��ȯ
}

void DiscountSale::SetDiscount(double discount)
{
	DiscountPercent = discount; // ��� ������ �Ű� ���� �� ī��
}

double DiscountSale::Bill()
{
	return (this->GetPrice() * (((double)100 - DiscountPercent) / (double)100));
	// �������� ����� ������ ��ȯ
}

double DiscountSale::Savings(DiscountSale& Other)
{
	return (Other.Bill() - this->Bill());
	// �������� ����� ������ ���̸� ��ȯ
}

bool DiscountSale::operator < (DiscountSale& second)
{
	if (this->GetPrice() < second.GetPrice()) // Sale class�� < �� ����
		return true;
	else
		return false;
}