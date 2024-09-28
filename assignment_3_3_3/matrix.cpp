#include "matrix.h"

Matrix::Matrix()
{
    double* ptr;

    data = new double*[3]; // double�� �ּҸ� ���� �� �ִ� �迭�� ��� ������ �Ҵ�
    ptr = new double[9]; // data[0][0] ~ data[2][2]
    memset(ptr, 0, sizeof(double) * 9); // 9ĭ ���� 0���� �ʱ�ȭ
    data[0] = ptr;
    for (int i = 1; i < 3; i++)
        data[i] = ptr + 3 * i; // 2���� �迭 ����
}

Matrix::Matrix(double** data)
{
    double* ptr;

    this->data = new double*[3];
    ptr = new double[9];
    this->data[0] = ptr;
    for (int i = 1; i < 3; i++)
        this->data[i] = ptr + 3 * i; // �� ������ó�� 2���� �迭 ����
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            this->data[i][j] = data[i][j]; // �Ű����� 2���� �迭�� ��Ҹ� ����
    }
}

Matrix::~Matrix()
{
    delete[] data[0];
    delete[] data; // 2���� �迭 �޸� ����
}

void Matrix::printMatrix()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            std::cout << data[i][j] << " "; // matrix�� ��Ҹ� ������ �������� ���
        std::cout << std::endl; // ���� �������� ����
    }
}

Matrix& Matrix::operator += (Matrix& Other)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            this->data[i][j] += Other.data[i][j]; // ��� ������ ������ �ݺ�
    }
    return *this; // a += b == a = a + b �̹Ƿ� a(*this)�� ��ȯ
}

Matrix& Matrix::operator -= (Matrix& Other)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            this->data[i][j] -= Other.data[i][j]; // ��� ������ ������ �ݺ�
    }
    return *this; // a -= b == a = a - b �̹Ƿ� a(*this)�� ��ȯ
}

Matrix* Matrix::operator * (Matrix& Other)
{
    Matrix* ret;
    double** data;
    double* ptr;
    double tmp;

    data = new double*[3];
    ptr = new double[9];
    data[0] = ptr;
    for (int i = 1; i < 3; i++)
        data[i] = ptr + 3 * i; // �� ������ ����� ���� 2���� �迭 ����
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tmp = 0; // this�� i�� ��ҿ� Other�� j�� ����� ���� ������ ����
            for (int k = 0; k < 3; k++)
                tmp += this->data[i][k] * Other.data[k][j]; // ��� ���� ����
            data[i][j] = tmp; // ������ ����� �Ҵ��� �迭�� ī��
        }
    }
    ret = new Matrix(data); // �� ����� �������� Matrix ����
    delete[] data[0];
    delete[] data; // matrix ret ���ο� ī�ǰ� �Ϸ�Ǿ����Ƿ� �޸� ����
    return ret;
}