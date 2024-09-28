#pragma once

namespace ooplinalg {
	class Matrix
	{
	public:
		Matrix();
		Matrix(const Matrix& mat); // copy constructor
		Matrix(int rows, int cols); // 매개변수에 따라 메모리 공간만 할당
		~Matrix();

		float getElement(int row, int col) const; // 해당 인덱스의 요소를 반환
		float** getData() const; // data 배열을 반환
		void setElement(const int row, const int col, float value); // 위치에 요소 삽입
		void setData(const int rows, const int cols, float** data); // data를 통으로 받아 세팅
		int getRows() const; // 행 정보 반환
		int getCols() const; // 열 정보 반환
		void setRows(const int rows); // 행 정보 삽입
		void setCols(const int cols); // 열 정보 삽입

		float determinant(); // 행렬식 계산

	private:
		float** data;
		int rows;
		int cols;
	};
	
	Matrix& add(Matrix& r, Matrix& a, Matrix& b);
	Matrix& sub(Matrix& r, Matrix& a, Matrix& b);
	Matrix& mul(Matrix& r, Matrix& a, Matrix& b); // 행렬끼리 연산

	Matrix& elementAdd(Matrix& r, Matrix& a, float v);
	Matrix& elementSub(Matrix& r, Matrix& a, float v);
	Matrix& elementMul(Matrix& r, Matrix& a, float v);
	Matrix& elementDiv(Matrix& r, Matrix& a, float v); // 행렬과 상수의 연산

	Matrix& transpose(Matrix& r, Matrix& m); // 전치행렬
	Matrix& adjoint(Matrix& r, Matrix& m); // 수반행렬
	Matrix& inverse(Matrix& r, Matrix& m); // 역행렬
}