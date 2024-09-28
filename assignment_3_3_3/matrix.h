#pragma once
#include <iostream>
#include <cstring>

class Matrix
{
private:
    double** data; // double 2차원 배열의 첫 주소

public:
    Matrix(); // 3 x 3의 배열 메모리 공간을 만들고 0으로 초기화
    Matrix(double** data); // 이미 생성된 2차원 배열의 요소를 복사해 생성
    ~Matrix(); // 할당된 메모리 해제

    void printMatrix(); // 행렬 출력
    Matrix& operator += (Matrix& Other); // this에 this의 matrix + Other의 matrix를 더한 matrix 저장
	Matrix& operator -= (Matrix& Other); // this에 this의 matrix - Other의 matrix를 더한 matrix 저장
	Matrix* operator * (Matrix& Other); // this의 matrix * Other의 matrix의 결과 matrix 반환
};