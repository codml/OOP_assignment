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
	ooplinalg::Matrix a(rows, cols); // �̸� �޸� ���� �Ҵ�
	ooplinalg::Matrix b; // �޸� ���� �Ҵ� X
	ooplinalg::Matrix c(rows, cols);
	cout << "set Matrix a" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin >> buf;
			a.setElement(i, j, buf); // setElement�� �Ҵ�� ������ ������ ����
		}
	}
	pptr = new float* [rows];
	pptr[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		pptr[i] = pptr[i - 1] + cols; // float** data�� �̸� ����
	cout << "set Matrix b" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cin >> pptr[i][j];
	}
	b.setData(rows, cols, pptr); // setData�� data ������ �ѱ�
	delete[] pptr[0];
	delete[] pptr; // Matrix ������ �Ҵ� �� ���������� �޸� ����
	cout << "search position(x, y): ";
	cin >> x >> y; // �� �˻��� ��ġ
	cout << "Matrix a(x,y): " << a.getElement(x, y) << endl;
	cout << "Matrix b(x,y): " << b.getElement(x, y) << endl; // �ش� ��ġ �� ��ȯ
	cout << "det(a), det(b): " << a.determinant() << " " << b.determinant() << endl; // ��Ľ�
	cout << "mul a * b: " << endl;
	ooplinalg::mul(c, a, b);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << c.getElement(i, j) << " ";
		cout << endl;
	} // ��� �� �� ���
	cout << "elementSub (a - 4): " << endl;
	ooplinalg::elementSub(c, a, 4);
	pptr = c.getData();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << pptr[i][j] << " ";
		cout << endl;
	}// ��� ���� �� ���
	cout << "inv(a): " << endl;
	ooplinalg::inverse(c, a);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << c.getElement(i, j) << " ";
		cout << endl;
	} // ����� ����� c�� ���� �� ���
	return 0;
}