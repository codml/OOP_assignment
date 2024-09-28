#pragma once
#include <iostream>
class Sale
{
private:
	double Price;

public:
	Sale();
	Sale(double ThePrice); // ��� ������ �Ű������� �ʱ�ȭ
	~Sale();

	double GetPrice(); // ��� ���� ��ȯ
	virtual double Bill(); // overriding �� �Լ�
	double Savings(Sale& Other); // Other���� �󸶳� �� ���� ��ȯ�ϴ� �Լ�
	bool operator < (Sale& Other); // Other�� ��� ���� ũ�� ��
};

class DiscountSale : public Sale
{
private:
	double DiscountPercent; // ������

public:
	DiscountSale();
	DiscountSale(double ThePrice); // Sale class�� Price�� �ʱ�ȭ
	~DiscountSale();
	double GetDiscount(); // DiscountPercent ��ȯ
	void SetDiscount(double discount); // DiscountSale�� ��� ����
	double Bill(); // �������� ����� ������ ��ȯ
	double Savings(DiscountSale& Other); // Sale�� Savings���� �������� ����� ���̸� ��ȯ
	bool operator < (DiscountSale& second); // Sale�� < �� ����(�������� ����ǵ�
											// �� ���� �������� ������ ���� ������)
};