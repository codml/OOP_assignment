#pragma once

namespace ooplinalg {
	class Matrix
	{
	public:
		Matrix();
		Matrix(const Matrix& mat); // copy constructor
		Matrix(int rows, int cols); // �Ű������� ���� �޸� ������ �Ҵ�
		~Matrix();

		float getElement(int row, int col) const; // �ش� �ε����� ��Ҹ� ��ȯ
		float** getData() const; // data �迭�� ��ȯ
		void setElement(const int row, const int col, float value); // ��ġ�� ��� ����
		void setData(const int rows, const int cols, float** data); // data�� ������ �޾� ����
		int getRows() const; // �� ���� ��ȯ
		int getCols() const; // �� ���� ��ȯ
		void setRows(const int rows); // �� ���� ����
		void setCols(const int cols); // �� ���� ����

		float determinant(); // ��Ľ� ���

	private:
		float** data;
		int rows;
		int cols;
	};
	
	Matrix& add(Matrix& r, Matrix& a, Matrix& b);
	Matrix& sub(Matrix& r, Matrix& a, Matrix& b);
	Matrix& mul(Matrix& r, Matrix& a, Matrix& b); // ��ĳ��� ����

	Matrix& elementAdd(Matrix& r, Matrix& a, float v);
	Matrix& elementSub(Matrix& r, Matrix& a, float v);
	Matrix& elementMul(Matrix& r, Matrix& a, float v);
	Matrix& elementDiv(Matrix& r, Matrix& a, float v); // ��İ� ����� ����

	Matrix& transpose(Matrix& r, Matrix& m); // ��ġ���
	Matrix& adjoint(Matrix& r, Matrix& m); // �������
	Matrix& inverse(Matrix& r, Matrix& m); // �����
}