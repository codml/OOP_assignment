#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    Matrix* a, * b, * c;
    double** pptr, * ptr;

    pptr = new double*[3];
    ptr = new double[9];
    pptr[0] = ptr;
    for (int i = 1; i < 3; i++)
        pptr[i] = ptr + 3 * i; // matrix�� ������ ���� 2���� �迭 �Ҵ�
    cout << "insert matrix a:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> pptr[i][j];
    }
    a = new Matrix(pptr); // double** pptr�� Matrix ����
    cout << "insert matrix b:" << endl; // ���� ���� Matrix b ����
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> pptr[i][j];
    }
    b = new Matrix(pptr);
    cout << "operator += :" << endl;
    *a += *b; // �����ε��� ������ +=�� ��� ���� ����
    a->printMatrix();
    *a -= *b; // ������ Matrix a�� �����ϱ� ���� ���� ����
    cout << "operator -= : " << endl;
    *a -= *b; // �����ε��� ������ -=�� ��� ���� ����
    a->printMatrix();
    *a += *b; // ������ Matrix a�� �����ϱ� ���� ���� ����
    cout << "operator * : " << endl;
    c = (*a)* (*b); // a�� b�� ���� ��� matrix�� �ּҰ��� c�� �Ҵ�
    c->printMatrix();
    delete[] pptr[0];
    delete[] pptr;
    delete a;
    delete b; 
    delete c; // ����� 2���� �迭, matrix �޸� ����
    return 0;
}