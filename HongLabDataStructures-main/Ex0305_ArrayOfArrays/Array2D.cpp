﻿#include "Array2D.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Array2D::Array2D(int num_rows, int num_cols)
{
	mNumRow = num_rows;
	mNumCol = num_cols;
	ppArr = new float* [num_rows];

	for (int i = 0; i < num_rows; ++i)
	{
		ppArr[i] = new float[mNumCol];
	}

	for (int i = 0; i < mNumRow; ++i)
	{
		for (int j = 0; j < mNumCol; ++j)
		{
			ppArr[i][j] = 0.0f;
		}
	}
}

// 복사 생성자 (b를 복사)
Array2D::Array2D(const Array2D& b)
{
	//TODO:
	mNumRow = b.mNumRow;
	mNumCol = b.mNumCol;
	ppArr = new float* [mNumRow];

	for (int i = 0; i < mNumRow; ++i)
	{
		ppArr[i] = new float[mNumCol];
	}

	for (int i = 0; i < mNumRow; ++i)
	{
		for (int j = 0; j < mNumCol; ++j)
		{
			ppArr[i][j] = b.ppArr[i][j];
		}
	}
}

Array2D::~Array2D()
{
	if (ppArr == nullptr)	return;
	for (int i = 0; i < mNumRow; ++i)
	{
		delete[] ppArr[i];
	}
	delete[] ppArr;
}

void Array2D::SetValue(int row, int col, float value)
{
	ppArr[row][col] = value;
}

float Array2D::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return ppArr[row][col]; // TODO:
}

Array2D Array2D::Transpose()
{
	Array2D temp(mNumCol, mNumRow); // num_cols_, num_rows_ 순서 주의

	for (int r = 0; r < mNumRow; r++)
		for (int c = 0; c < mNumCol; c++)
			temp.SetValue(c, r, GetValue(r, c));

	return temp;
}

Array2D Array2D::Add(const Array2D& b)
{
	assert(b.mNumCol == mNumCol);
	assert(b.mNumRow == mNumRow);

	Array2D temp(mNumRow, mNumCol);

	for (int r = 0; r < mNumRow; r++)
		for (int c = 0; c < mNumCol; c++)
			temp.SetValue(r, c, GetValue(r, c) + b.GetValue(r, c));

	return temp;
}

void Array2D::Print()
{
	for (int r = 0; r < mNumRow; r++)
	{
		for (int c = 0; c < mNumCol; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
