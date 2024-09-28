#include <iostream>
#include <cstring>
#include "sale.h"

using namespace std;

int main()
{
	char item1[10];
	char item2[10];
	char discount[10];
	DiscountSale* ptr1, * ptr2;

	for (int i = 0; i < 40; i++)
		cout << "=";
	cout << endl << "Price Compare Program" << endl;
	for (int i = 0; i < 40; i++)
		cout << "=";
	cout << endl << "Insert item1 price: ";
	cin >> item1;
	cout << "Insert item2 price: ";
	cin >> item2; // item1, item2�� ������ "$1234..."�� ���·� ����
	ptr1 = new DiscountSale(atof(item1 + 1));
	ptr2 = new DiscountSale(atof(item2 + 1)); // ���ڿ����� '$'�� ���� �������� ��ȯ�� �ν��Ͻ� ����
	cout << endl;
	for (int i = 0; i < 40; i++)
		cout << "-";
	cout << endl << "Insert discount percent: ";
	cin >> discount; // "25.xx%"���·� %���� ����
	ptr1->SetDiscount(atof(discount)); // atof�� �״�� ������ '%' ���������� ���� ��ȯ��
	ptr2->SetDiscount(atof(discount)); // �Է¹��� �������� ��ü�� ��� ������ ī��
	for (int i = 0; i < 40; i++)
		cout << "-";
	cout << endl << "Result: " << endl;
	cout << "Discount price of ";
	if (*ptr1 < *ptr2) // �������̵��� ������(�������� ����� ������ ��)
	{
		cout << "item1";
		cout << " is cheaper." << endl;
		cout << "Savings discount price is $" << ptr1->Savings(*ptr2);
		// ptr1�� ����Ű�� ��ü�� ������ �����Ƿ� ptr1�� ��� �Լ� Savings�� ȣ��
	}
	else
	{
		cout << "item2";
		cout << " is cheaper." << endl;
		cout << "Savings discount price is $" << ptr2->Savings(*ptr1);
	}
	delete ptr1;
	delete ptr2; // �޸� ����
	return 0;
}