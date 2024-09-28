#include "matrix.h"

Matrix::Matrix()
{
    double* ptr;

    data = new double*[3]; // double의 주소를 담을 수 있는 배열을 멤버 변수에 할당
    ptr = new double[9]; // data[0][0] ~ data[2][2]
    memset(ptr, 0, sizeof(double) * 9); // 9칸 전부 0으로 초기화
    data[0] = ptr;
    for (int i = 1; i < 3; i++)
        data[i] = ptr + 3 * i; // 2차원 배열 생성
}

Matrix::Matrix(double** data)
{
    double* ptr;

    this->data = new double*[3];
    ptr = new double[9];
    this->data[0] = ptr;
    for (int i = 1; i < 3; i++)
        this->data[i] = ptr + 3 * i; // 위 생성자처럼 2차원 배열 생성
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            this->data[i][j] = data[i][j]; // 매개변수 2차원 배열의 요소를 복사
    }
}

Matrix::~Matrix()
{
    delete[] data[0];
    delete[] data; // 2차원 배열 메모리 해제
}

void Matrix::printMatrix()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            std::cout << data[i][j] << " "; // matrix의 요소를 공백을 기준으로 출력
        std::cout << std::endl; // 행은 개행으로 구분
    }
}

Matrix& Matrix::operator += (Matrix& Other)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            this->data[i][j] += Other.data[i][j]; // 요소 단위로 연산을 반복
    }
    return *this; // a += b == a = a + b 이므로 a(*this)를 반환
}

Matrix& Matrix::operator -= (Matrix& Other)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            this->data[i][j] -= Other.data[i][j]; // 요소 단위로 연산을 반복
    }
    return *this; // a -= b == a = a - b 이므로 a(*this)를 반환
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
        data[i] = ptr + 3 * i; // 곱 연산의 결과를 담을 2차원 배열 생성
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tmp = 0; // this의 i행 요소와 Other의 j열 요소의 곱을 저장할 변수
            for (int k = 0; k < 3; k++)
                tmp += this->data[i][k] * Other.data[k][j]; // 요소 단위 곱셈
            data[i][j] = tmp; // 곱셈의 결과를 할당한 배열에 카피
        }
    }
    ret = new Matrix(data); // 위 결과를 바탕으로 Matrix 생성
    delete[] data[0];
    delete[] data; // matrix ret 내부에 카피가 완료되었으므로 메모리 해제
    return ret;
}