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
        pptr[i] = ptr + 3 * i; // matrix의 생성을 위한 2차원 배열 할당
    cout << "insert matrix a:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> pptr[i][j];
    }
    a = new Matrix(pptr); // double** pptr로 Matrix 생성
    cout << "insert matrix b:" << endl; // 위와 같이 Matrix b 생성
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> pptr[i][j];
    }
    b = new Matrix(pptr);
    cout << "operator += :" << endl;
    *a += *b; // 오버로딩한 연산자 +=로 행렬 덧셈 연산
    a->printMatrix();
    *a -= *b; // 원래의 Matrix a를 복구하기 위해 뺄셈 연산
    cout << "operator -= : " << endl;
    *a -= *b; // 오버로딩한 연산자 -=로 행렬 덧셈 연산
    a->printMatrix();
    *a += *b; // 원래의 Matrix a를 복구하기 위해 덧셈 연산
    cout << "operator * : " << endl;
    c = (*a)* (*b); // a와 b를 곱한 결과 matrix의 주소값을 c에 할당
    c->printMatrix();
    delete[] pptr[0];
    delete[] pptr;
    delete a;
    delete b; 
    delete c; // 사용한 2차원 배열, matrix 메모리 해제
    return 0;
}