#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Matrix::Matrix(int num_rows, int num_cols)
{
	mNumRows = num_rows;
	mNumCols = num_cols;
	mpValues = new float[mNumRows * mNumCols];
	std::fill(&mpValues[0], &mpValues[mNumRows * mNumCols], 0.0f);
}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	mNumRows = b.mNumRows;
	mNumCols = b.mNumCols;
	mpValues = new float[mNumRows * mNumCols];
	std::fill(&mpValues[0], &mpValues[mNumRows * mNumCols], 0.0f);
	for (int i = 0; i < mNumRows * mNumCols; ++i)
		mpValues[i] = b.mpValues[i];
}

Matrix::~Matrix()
{
	if (mpValues != nullptr)
		delete[] mpValues;
}

void Matrix::SetValue(int row, int col, float value)
{
	mpValues[col + mNumCols * row] = value;
}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return mpValues[col + mNumCols * row];
}

Matrix Matrix::Transpose()
{
	Matrix temp(mNumCols, mNumRows); // num_cols_, num_rows_ 순서 주의
	for (int i = 0; i < mNumRows; ++i)
	{
		for (int j = 0; j < mNumCols; ++j)
		{
			temp.SetValue(j, i, mpValues[i * mNumCols + j]);
		}
	}
	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.mNumCols == mNumCols);
	assert(b.mNumRows == mNumRows);

	Matrix temp(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows * mNumCols; ++i)
		temp.mpValues[i] = b.mpValues[i] + mpValues[i];
	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < mNumRows; r++)
	{
		for (int c = 0; c < mNumCols; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
