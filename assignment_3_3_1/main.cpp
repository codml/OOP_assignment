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
	cin >> item2; // item1, item2의 가격을 "$1234..."의 형태로 받음
	ptr1 = new DiscountSale(atof(item1 + 1));
	ptr2 = new DiscountSale(atof(item2 + 1)); // 문자열에서 '$'를 빼고 가격으로 변환해 인스턴스 생성
	cout << endl;
	for (int i = 0; i < 40; i++)
		cout << "-";
	cout << endl << "Insert discount percent: ";
	cin >> discount; // "25.xx%"형태로 %까지 받음
	ptr1->SetDiscount(atof(discount)); // atof에 그대로 넣으면 '%' 이전까지의 값을 변환함
	ptr2->SetDiscount(atof(discount)); // 입력받은 할인율을 객체의 멤버 변수에 카피
	for (int i = 0; i < 40; i++)
		cout << "-";
	cout << endl << "Result: " << endl;
	cout << "Discount price of ";
	if (*ptr1 < *ptr2) // 오버라이딩된 연산자(할인율이 적용된 가격을 비교)
	{
		cout << "item1";
		cout << " is cheaper." << endl;
		cout << "Savings discount price is $" << ptr1->Savings(*ptr2);
		// ptr1이 가리키는 객체의 가격이 작으므로 ptr1의 멤버 함수 Savings를 호출
	}
	else
	{
		cout << "item2";
		cout << " is cheaper." << endl;
		cout << "Savings discount price is $" << ptr2->Savings(*ptr1);
	}
	delete ptr1;
	delete ptr2; // 메모리 해제
	return 0;
}