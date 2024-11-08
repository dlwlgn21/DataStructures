#include "Array2D.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Array2D::Array2D(int num_rows, int num_cols)
{
	mNumRows = num_rows;
	mNumCols = num_cols;
	mppArray = new float* [mNumRows];
	for (int i = 0; i < mNumRows; ++i)
	{
		mppArray[i] = new float[mNumCols];
		for (int j = 0; j < mNumCols; ++j)
			mppArray[i][j] = 0.0f;
	}
}

// 복사 생성자 (b를 복사)
Array2D::Array2D(const Array2D& b)
{
	mNumRows = b.mNumRows;
	mNumCols = b.mNumCols;
	mppArray = new float* [mNumRows];
	for (int i = 0; i < mNumRows; ++i)
	{
		mppArray[i] = new float[mNumCols];
		for (int j = 0; j < mNumCols; ++j)
			mppArray[i][j] = 0.0f;
	}
	for (int i = 0; i < mNumRows; ++i)
	{
		for (int j = 0; j < mNumCols; ++j)
		{
			mppArray[i][j] = b.mppArray[i][j];
		}
	}
}

Array2D::~Array2D()
{
	//TODO:
	for (int i = 0; i < mNumRows; ++i)
	{
		delete[] mppArray[i];
	}
	delete[] mppArray;
}

void Array2D::SetValue(int row, int col, float value)
{
	mppArray[row][col] = value;
}

float Array2D::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return mppArray[row][col];
}

Array2D Array2D::Transpose()
{
	Array2D temp(mNumCols, mNumRows); // num_cols_, num_rows_ 순서 주의

	for (int r = 0; r < mNumRows; r++)
		for (int c = 0; c < mNumCols; c++)
			temp.SetValue(c, r, GetValue(r, c));

	return temp;
}

Array2D Array2D::Add(const Array2D& b)
{
	assert(b.mNumCols == mNumCols);
	assert(b.mNumRows == mNumRows);

	Array2D temp(mNumRows, mNumCols);

	for (int r = 0; r < mNumRows; r++)
		for (int c = 0; c < mNumCols; c++)
			temp.SetValue(r, c, GetValue(r, c) + b.GetValue(r, c));

	return temp;
}

void Array2D::Print()
{
	for (int r = 0; r < mNumRows; r++)
	{
		for (int c = 0; c < mNumCols; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
