#include "Matrix.h"

using namespace ooplinalg;

Matrix::Matrix()
{
	data = 0;
	rows = 0;
	cols = 0; // 멤버 변수 초기화
}

Matrix::Matrix(const Matrix& mat)
{
	this->rows = mat.rows; // mat의 rows로 초기화
	this->cols = mat.cols; // mat의 cols로 초기화
	this->data = new float* [this->rows];
	this->data[0] = new float[this->rows * this->cols]; // data 메모리 할당(2차원 배열)
	for (int i = 1; i < this->rows; i++)
		this->data[i] = this->data[i - 1] + this->cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			this->data[i][j] = mat.data[i][j]; // element 단위로 copy
	}
}

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows; // rows 초기화
	this->cols = cols; // cols 초기화
	this->data = new float* [this->rows];
	this->data[0] = new float[this->rows * this->cols];
	for (int i = 1; i < this->rows; i++)
		this->data[i] = this->data[i - 1] + this->cols; // 입력받은 값으로 메모리만 할당
}

Matrix::~Matrix()
{
	delete[] this->data[0]; // float 배열 메모리 해제
	delete[] this->data; // float* 배열 메모리 해제
}

float Matrix::getElement(int row, int col) const
{
	if (rows <= row || cols <= col)
		return 0; // 인자가 배열을 초과한 값을 받으면 0 반환
	return this->data[row][col]; // 해당 위치의 데이터 반환
}

float** Matrix::getData() const
{
	return this->data; // data변수(주소값) 반환
}

void Matrix::setElement(const int row, const int col, float value)
{
	if (rows <= row || cols <= col)
		return; // 위치가 배열을 초과한 값이면 리턴
	this->data[row][col] = value; // 값 copy
}

void Matrix::setData(const int rows, const int cols, float** data)
{
	this->rows = rows; // rows 세팅
	this->cols = cols; // cols 세팅
	if (this->data) // 기존에 data가 있으면
	{
		delete[] this->data[0];
		delete[] this->data; // 메모리 초기화
	}
	this->data = new float* [this->rows];
	this->data[0] = new float[this->rows * this->cols]; // 메모리 새롭게 할당
	for (int i = 1; i < this->rows; i++)
		this->data[i] = this->data[i - 1] + this->cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			this->data[i][j] = data[i][j]; // data copy
	}
}

int Matrix::getRows() const
{
	return this->rows;
}

int Matrix::getCols() const
{
	return this->cols;
}

void Matrix::setRows(const int rows)
{
	this->rows = rows;
}

void Matrix::setCols(const int cols)
{
	this->cols = cols;
}

float Matrix::determinant()
{
	float** l_mat;
	float** u_mat;
	float** a_mat;
	float cnt;
	float tmp, det;

	if (rows != cols)
		return 0; // 정사각행렬이 아니면 0 반환
	cnt = 0; // 행 교환 횟수를 저장하는 변수
	l_mat = new float* [rows]; // L(lower triangle) Matrix 생성
	l_mat[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		l_mat[i] = l_mat[i - 1] + cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			l_mat[i][j] = 0; // 배열 0으로 초기화
	}
	u_mat = new float* [rows]; // U(upper triangle) Matrix 생성
	u_mat[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		u_mat[i] = u_mat[i - 1] + cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			u_mat[i][j] = 0; // 배열 0으로 초기화
	}
	a_mat = new float* [rows]; // A Matrix(this->data) 생성
	a_mat[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		a_mat[i] = a_mat[i - 1] + cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			a_mat[i][j] = data[i][j]; // this->data copy
	} // L, U, A matrix 세팅 완료
	for (int i = 0; i < rows; i++)
	{
		if (a_mat[i][i] == 0) // pivot 위치에 0이 있으면
		{
			for (int j = i + 1; j < rows; j++) // 행 교환을 위해 반복
			{
				if (a_mat[j][i]) // 교환할 행을 찾으면(0이 아닌 값을 가짐)
				{
					for (int k = 0; k < rows; k++) // 행 교환
					{
						tmp = a_mat[i][k];
						a_mat[i][k] = a_mat[j][k];
						a_mat[j][k] = tmp;
					}
					cnt++; // 행 교환 횟수 세기
					break;
				}
			}
		}// permutation(행 교환)
		l_mat[i][i] = 1;
		for (int j = i + 1; j < rows; j++)
		{
			l_mat[j][i] = a_mat[j][i] / a_mat[i][i]; // multiplier 저장(L matrix 만들기)
			for (int k = i + 1; k < cols; k++)
				a_mat[j][k] -= l_mat[j][i] * a_mat[i][k]; // A matrix를 한 행씩 upper triangle로 만드는 과정
		}
		for (int j = i; j < cols; j++)
			u_mat[i][j] = a_mat[i][j]; // upper triangle로 바뀔 A matrix를 한 행씩 U matrix에 저장
	}
	det = 1; // 행렬식 값 초기화
	for (int i = 0; i < rows; i++)
		det *= l_mat[i][i];
	for (int i = 0; i < rows; i++)
		det *= u_mat[i][i]; // L, U matrix의 주대각 성분 곱한 값 == det(L) * det(U)
	for (int i = 0; i < cnt; i++)
		det *= -1; // 행 교환한 횟수만큼 행렬식의 부호가 바뀜
	delete[] l_mat[0];
	delete[] l_mat;
	delete[] u_mat[0];
	delete[] u_mat;
	delete[] a_mat[0];
	delete[] a_mat; // L, U, A matrix 메모리 해제
	return det;
}

Matrix& ooplinalg::add(Matrix& r, Matrix& a, Matrix& b)
{
	int rows, cols;

	rows = a.getRows(); // rows 값 설정
	cols = a.getCols(); // cols 값 설정
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			r.setElement(i, j, a.getElement(i, j) + b.getElement(i, j));
		// a, b matrix의 각 요소를 더한 값을 요소 단위로 삽입
	}
	return r;
}

Matrix& ooplinalg::sub(Matrix& r, Matrix& a, Matrix& b)
{
	int rows, cols;

	rows = a.getRows();
	cols = a.getCols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			r.setElement(i, j, a.getElement(i, j) - b.getElement(i, j));
		// a의 요소에서 b의 요소를 뺀 값을 r에 요소 단위로 삽입
	}
	return r;
}

Matrix& ooplinalg::mul(Matrix& r, Matrix& a, Matrix& b)
{
	int rows_a, cols_a, cols_b;
	float tmp;

	if (a.getCols() != b.getRows())
		return a; // 행렬 곱 안 되면 a 반환
	rows_a = a.getRows();
	cols_a = a.getCols();
	cols_b = b.getCols();
	for (int i = 0; i < rows_a; i++)
	{
		for (int j = 0; j < cols_b; j++)
		{
			tmp = 0;
			for (int k = 0; k < cols_a; k++)
				tmp += a.getElement(i, k) * b.getElement(k, j);
			r.setElement(i, j, tmp);
		}
	}// 곱셈 연산
	return r;
}

Matrix& ooplinalg::elementAdd(Matrix& r, Matrix& a, float v)
{
	int rows, cols;

	rows = a.getRows();
	cols = a.getCols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			r.setElement(i, j, a.getElement(i, j) + v);
	}// a의 요소에 v를 더한 값을 r에 요소 단위로 저장
	return r;
}

Matrix& ooplinalg::elementSub(Matrix& r, Matrix& a, float v)
{
	int rows, cols;

	rows = a.getRows();
	cols = a.getCols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			r.setElement(i, j, a.getElement(i, j) - v);
	} // a의 요소에서 v를 뺀 값을 r에 저장
	return r;
}

Matrix& ooplinalg::elementMul(Matrix& r, Matrix& a, float v)
{
	int rows, cols;

	rows = a.getRows();
	cols = a.getCols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			r.setElement(i, j, a.getElement(i, j) * v);
	} // a의 요소에 v를 곱한 값을 r에 저장
	return r;
}

Matrix& ooplinalg::elementDiv(Matrix& r, Matrix& a, float v)
{
	int rows, cols;

	if (!v)
		return a; // v가 0이면 나눌 수 없으므로 a matrix 반환
	rows = a.getRows();
	cols = a.getCols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			r.setElement(i, j, a.getElement(i, j) / v);
	}
	return r;
}

Matrix& ooplinalg::transpose(Matrix& r, Matrix& m)
{
	int rows, cols;
	float tmp;

	rows = r.getRows();
	cols = r.getCols();
	if (m.getRows() != m.getCols()) // 정사각 행렬이 아니면
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				r.setElement(i, j, m.getElement(j, i)); // r에 m의 요소 값들을 전치해서 복사
		}
	}
	else // 정사각 행렬이면
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				r.setElement(i, j, m.getElement(i, j)); // r에 m의 요소 값들을 그대로 복사
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = i + 1; j < cols; j++)
			{
				tmp = r.getElement(i, j);
				r.setElement(i, j, r.getElement(j, i));
				r.setElement(j, i, tmp);
			} // 주대각성분 기준 위쪽요소를 아래쪽 요소와 swap
		}
	}
	return r;
}

Matrix& ooplinalg::adjoint(Matrix& r, Matrix& m)
{
	int rows, cols;
	float sign;
	int row_flag, col_flag;

	rows = r.getRows();
	cols = r.getCols();
	if (rows != cols)
		return m; // 정사각 행렬이 아니면 m 반환
	Matrix tmp(rows - 1, cols - 1); // 여인수 값을 계산하기 위한 소행렬
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			sign = 1;
			for (int k = 0; k < i + j; k++)
				sign *= -1; // 여인수 행렬의 요소에 곱해져야 하는 -1 값
			row_flag = 0;
			for (int l = 0; l < rows; l++)
			{
				if (l == i) // 소행렬에 들어가선 안되는 행이라면
				{
					row_flag++; // flag 세워서 그 행의 값은 복사하지 않도록
					continue; // 조건문으로 넘어감
				}
				col_flag = 0;
				for (int n = 0; n < cols; n++)
				{
					if (n == j) // 소행렬에 들어가선 안되는 열이라면
					{
						col_flag++; // flag 세워서 그 열의 값은 복사하지 않도록
						continue; // 조건문으로 넘어감
					}
					tmp.setElement(l - row_flag, n - col_flag, m.getElement(l, n));
					// m의 요소 중 여인수에 해당하는 값만 복사
				}
			}
			r.setElement(i, j, tmp.determinant() * sign); // 여인수와 부호를 곱해 여인수 행렬 생성
		}
	}
	transpose(r, r); // 여인수 행렬의 전치행렬: 수반 행렬
	return r;
}

Matrix& ooplinalg::inverse(Matrix& r, Matrix& m)
{
	if (m.getRows() != m.getCols())
		return m; // 정사각행렬이 아니면 m 반환
	adjoint(r, m);// r에 m의 수반행렬을 저장
	elementDiv(r, r, m.determinant());// r행렬을 m의 행렬식 값으로 나눔
	return r;
}