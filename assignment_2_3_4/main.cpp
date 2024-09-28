#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
	int rows, cols, x, y;
	float buf;
	float** pptr;

	cout << "insert rows and cols: ";
	cin >> rows >> cols;
	ooplinalg::Matrix a(rows, cols); // 미리 메모리 공간 할당
	ooplinalg::Matrix b; // 메모리 공간 할당 X
	ooplinalg::Matrix c(rows, cols);
	cout << "set Matrix a" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin >> buf;
			a.setElement(i, j, buf); // setElement로 할당된 공간에 데이터 삽입
		}
	}
	pptr = new float* [rows];
	pptr[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		pptr[i] = pptr[i - 1] + cols; // float** data를 미리 만듦
	cout << "set Matrix b" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cin >> pptr[i][j];
	}
	b.setData(rows, cols, pptr); // setData로 data 통으로 넘김
	delete[] pptr[0];
	delete[] pptr; // Matrix 내에서 할당 후 복사했으니 메모리 해제
	cout << "search position(x, y): ";
	cin >> x >> y; // 값 검색할 위치
	cout << "Matrix a(x,y): " << a.getElement(x, y) << endl;
	cout << "Matrix b(x,y): " << b.getElement(x, y) << endl; // 해당 위치 값 반환
	cout << "det(a), det(b): " << a.determinant() << " " << b.determinant() << endl; // 행렬식
	cout << "mul a * b: " << endl;
	ooplinalg::mul(c, a, b);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << c.getElement(i, j) << " ";
		cout << endl;
	} // 행렬 곱 후 출력
	cout << "elementSub (a - 4): " << endl;
	ooplinalg::elementSub(c, a, 4);
	pptr = c.getData();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << pptr[i][j] << " ";
		cout << endl;
	}// 상수 연산 후 출력
	cout << "inv(a): " << endl;
	ooplinalg::inverse(c, a);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << c.getElement(i, j) << " ";
		cout << endl;
	} // 역행렬 만들고 c에 넣은 후 출력
	return 0;
}