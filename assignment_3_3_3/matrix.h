#pragma once
#include <iostream>
#include <cstring>

class Matrix
{
private:
    double** data; // double 2���� �迭�� ù �ּ�

public:
    Matrix(); // 3 x 3�� �迭 �޸� ������ ����� 0���� �ʱ�ȭ
    Matrix(double** data); // �̹� ������ 2���� �迭�� ��Ҹ� ������ ����
    ~Matrix(); // �Ҵ�� �޸� ����

    void printMatrix(); // ��� ���
    Matrix& operator += (Matrix& Other); // this�� this�� matrix + Other�� matrix�� ���� matrix ����
	Matrix& operator -= (Matrix& Other); // this�� this�� matrix - Other�� matrix�� ���� matrix ����
	Matrix* operator * (Matrix& Other); // this�� matrix * Other�� matrix�� ��� matrix ��ȯ
};