#include "Matrix.h"

using namespace ooplinalg;

Matrix::Matrix()
{
	data = 0;
	rows = 0;
	cols = 0; // ��� ���� �ʱ�ȭ
}

Matrix::Matrix(const Matrix& mat)
{
	this->rows = mat.rows; // mat�� rows�� �ʱ�ȭ
	this->cols = mat.cols; // mat�� cols�� �ʱ�ȭ
	this->data = new float* [this->rows];
	this->data[0] = new float[this->rows * this->cols]; // data �޸� �Ҵ�(2���� �迭)
	for (int i = 1; i < this->rows; i++)
		this->data[i] = this->data[i - 1] + this->cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			this->data[i][j] = mat.data[i][j]; // element ������ copy
	}
}

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows; // rows �ʱ�ȭ
	this->cols = cols; // cols �ʱ�ȭ
	this->data = new float* [this->rows];
	this->data[0] = new float[this->rows * this->cols];
	for (int i = 1; i < this->rows; i++)
		this->data[i] = this->data[i - 1] + this->cols; // �Է¹��� ������ �޸𸮸� �Ҵ�
}

Matrix::~Matrix()
{
	delete[] this->data[0]; // float �迭 �޸� ����
	delete[] this->data; // float* �迭 �޸� ����
}

float Matrix::getElement(int row, int col) const
{
	if (rows <= row || cols <= col)
		return 0; // ���ڰ� �迭�� �ʰ��� ���� ������ 0 ��ȯ
	return this->data[row][col]; // �ش� ��ġ�� ������ ��ȯ
}

float** Matrix::getData() const
{
	return this->data; // data����(�ּҰ�) ��ȯ
}

void Matrix::setElement(const int row, const int col, float value)
{
	if (rows <= row || cols <= col)
		return; // ��ġ�� �迭�� �ʰ��� ���̸� ����
	this->data[row][col] = value; // �� copy
}

void Matrix::setData(const int rows, const int cols, float** data)
{
	this->rows = rows; // rows ����
	this->cols = cols; // cols ����
	if (this->data) // ������ data�� ������
	{
		delete[] this->data[0];
		delete[] this->data; // �޸� �ʱ�ȭ
	}
	this->data = new float* [this->rows];
	this->data[0] = new float[this->rows * this->cols]; // �޸� ���Ӱ� �Ҵ�
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
		return 0; // ���簢����� �ƴϸ� 0 ��ȯ
	cnt = 0; // �� ��ȯ Ƚ���� �����ϴ� ����
	l_mat = new float* [rows]; // L(lower triangle) Matrix ����
	l_mat[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		l_mat[i] = l_mat[i - 1] + cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			l_mat[i][j] = 0; // �迭 0���� �ʱ�ȭ
	}
	u_mat = new float* [rows]; // U(upper triangle) Matrix ����
	u_mat[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		u_mat[i] = u_mat[i - 1] + cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			u_mat[i][j] = 0; // �迭 0���� �ʱ�ȭ
	}
	a_mat = new float* [rows]; // A Matrix(this->data) ����
	a_mat[0] = new float[rows * cols];
	for (int i = 1; i < rows; i++)
		a_mat[i] = a_mat[i - 1] + cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			a_mat[i][j] = data[i][j]; // this->data copy
	} // L, U, A matrix ���� �Ϸ�
	for (int i = 0; i < rows; i++)
	{
		if (a_mat[i][i] == 0) // pivot ��ġ�� 0�� ������
		{
			for (int j = i + 1; j < rows; j++) // �� ��ȯ�� ���� �ݺ�
			{
				if (a_mat[j][i]) // ��ȯ�� ���� ã����(0�� �ƴ� ���� ����)
				{
					for (int k = 0; k < rows; k++) // �� ��ȯ
					{
						tmp = a_mat[i][k];
						a_mat[i][k] = a_mat[j][k];
						a_mat[j][k] = tmp;
					}
					cnt++; // �� ��ȯ Ƚ�� ����
					break;
				}
			}
		}// permutation(�� ��ȯ)
		l_mat[i][i] = 1;
		for (int j = i + 1; j < rows; j++)
		{
			l_mat[j][i] = a_mat[j][i] / a_mat[i][i]; // multiplier ����(L matrix �����)
			for (int k = i + 1; k < cols; k++)
				a_mat[j][k] -= l_mat[j][i] * a_mat[i][k]; // A matrix�� �� �྿ upper triangle�� ����� ����
		}
		for (int j = i; j < cols; j++)
			u_mat[i][j] = a_mat[i][j]; // upper triangle�� �ٲ� A matrix�� �� �྿ U matrix�� ����
	}
	det = 1; // ��Ľ� �� �ʱ�ȭ
	for (int i = 0; i < rows; i++)
		det *= l_mat[i][i];
	for (int i = 0; i < rows; i++)
		det *= u_mat[i][i]; // L, U matrix�� �ִ밢 ���� ���� �� == det(L) * det(U)
	for (int i = 0; i < cnt; i++)
		det *= -1; // �� ��ȯ�� Ƚ����ŭ ��Ľ��� ��ȣ�� �ٲ�
	delete[] l_mat[0];
	delete[] l_mat;
	delete[] u_mat[0];
	delete[] u_mat;
	delete[] a_mat[0];
	delete[] a_mat; // L, U, A matrix �޸� ����
	return det;
}

Matrix& ooplinalg::add(Matrix& r, Matrix& a, Matrix& b)
{
	int rows, cols;

	rows = a.getRows(); // rows �� ����
	cols = a.getCols(); // cols �� ����
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			r.setElement(i, j, a.getElement(i, j) + b.getElement(i, j));
		// a, b matrix�� �� ��Ҹ� ���� ���� ��� ������ ����
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
		// a�� ��ҿ��� b�� ��Ҹ� �� ���� r�� ��� ������ ����
	}
	return r;
}

Matrix& ooplinalg::mul(Matrix& r, Matrix& a, Matrix& b)
{
	int rows_a, cols_a, cols_b;
	float tmp;

	if (a.getCols() != b.getRows())
		return a; // ��� �� �� �Ǹ� a ��ȯ
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
	}// ���� ����
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
	}// a�� ��ҿ� v�� ���� ���� r�� ��� ������ ����
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
	} // a�� ��ҿ��� v�� �� ���� r�� ����
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
	} // a�� ��ҿ� v�� ���� ���� r�� ����
	return r;
}

Matrix& ooplinalg::elementDiv(Matrix& r, Matrix& a, float v)
{
	int rows, cols;

	if (!v)
		return a; // v�� 0�̸� ���� �� �����Ƿ� a matrix ��ȯ
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
	if (m.getRows() != m.getCols()) // ���簢 ����� �ƴϸ�
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				r.setElement(i, j, m.getElement(j, i)); // r�� m�� ��� ������ ��ġ�ؼ� ����
		}
	}
	else // ���簢 ����̸�
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				r.setElement(i, j, m.getElement(i, j)); // r�� m�� ��� ������ �״�� ����
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = i + 1; j < cols; j++)
			{
				tmp = r.getElement(i, j);
				r.setElement(i, j, r.getElement(j, i));
				r.setElement(j, i, tmp);
			} // �ִ밢���� ���� ���ʿ�Ҹ� �Ʒ��� ��ҿ� swap
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
		return m; // ���簢 ����� �ƴϸ� m ��ȯ
	Matrix tmp(rows - 1, cols - 1); // ���μ� ���� ����ϱ� ���� �����
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			sign = 1;
			for (int k = 0; k < i + j; k++)
				sign *= -1; // ���μ� ����� ��ҿ� �������� �ϴ� -1 ��
			row_flag = 0;
			for (int l = 0; l < rows; l++)
			{
				if (l == i) // ����Ŀ� ���� �ȵǴ� ���̶��
				{
					row_flag++; // flag ������ �� ���� ���� �������� �ʵ���
					continue; // ���ǹ����� �Ѿ
				}
				col_flag = 0;
				for (int n = 0; n < cols; n++)
				{
					if (n == j) // ����Ŀ� ���� �ȵǴ� ���̶��
					{
						col_flag++; // flag ������ �� ���� ���� �������� �ʵ���
						continue; // ���ǹ����� �Ѿ
					}
					tmp.setElement(l - row_flag, n - col_flag, m.getElement(l, n));
					// m�� ��� �� ���μ��� �ش��ϴ� ���� ����
				}
			}
			r.setElement(i, j, tmp.determinant() * sign); // ���μ��� ��ȣ�� ���� ���μ� ��� ����
		}
	}
	transpose(r, r); // ���μ� ����� ��ġ���: ���� ���
	return r;
}

Matrix& ooplinalg::inverse(Matrix& r, Matrix& m)
{
	if (m.getRows() != m.getCols())
		return m; // ���簢����� �ƴϸ� m ��ȯ
	adjoint(r, m);// r�� m�� ��������� ����
	elementDiv(r, r, m.determinant());// r����� m�� ��Ľ� ������ ����
	return r;
}